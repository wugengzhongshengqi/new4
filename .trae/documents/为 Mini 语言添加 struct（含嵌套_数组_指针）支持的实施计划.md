## 总览
- 目标：为当前 Mini 语言编译器加入 `struct` 类型，支持任意层级嵌套、结构体数组与结构体中指针字段；支持通过字段访问链与数组索引组合进行读写。
- 范围：词法、语法（Bison/Flex）、类型系统与中间代码（TAC）、目标代码生成（obj.c），并完善测试用例驱动验证。

## 现状与差距
- 词法（mini.l）：仅有 `int/char` 与基本操作符，不识别 `struct`、`.`（字段访问）与 `->`（可选）。
- 语法（mini.y）：支持变量、指针、数组、表达式与调用，不支持结构体定义、结构体变量声明及字段访问。
- 中间代码（tac.c/h）：已有数组与指针的 TAC 生成与地址计算，缺少结构体类型表与字段偏移的地址计算；`SYM::etc` 已用于数组元数据，可复用保存结构体元数据。
- 目标生成（obj.c）：`TAC_VAR` 能按数组大小分配空间，但对结构体变量默认按 4 字节，需扩展为按结构体大小分配；`TAC_DEREF_R/W` 的字节/字读写选择目前仅基于指针类型，需要在结构体字段存取中按字段基本大小选择。

## 设计与数据结构
- 新增 `STRUCT_META` 类型表：记录结构体名称、字段列表、每个字段的类型描述与字节大小、偏移（含对齐，先以 4 字节对齐为准），以及总大小。
- 新增 `FIELD_META`：包含 `name`、`kind`（基本 `int/char`、指针 `int*/char*`、数组、嵌套 struct）、`size`、`offset`，若为数组则携带维度与步幅，若为嵌套 struct 则指向对应 `STRUCT_META`。
- `SYM::dtype` 扩展：加入 `DT_STRUCT` 与（可选）`DT_PTR_STRUCT`；`SYM::etc`：变量为结构体时挂 `STRUCT_META*`；数组元素为结构体时，数组元数据的 `elem_size` 为结构体大小。

## 词法/语法改动
- 词法（mini.l）：
  - 增加关键字 `struct` 返回 `STRUCT`。
  - 增加符号 `.` 返回 `DOT`；可选增加 `->` 返回 `ARROW`（如需要）。
- 语法（mini.y）：
  - token 扩展：`%token STRUCT DOT ARROW`（ARROW 可选）。
  - 新增结构体定义：`struct_definition : STRUCT IDENTIFIER '{' struct_field_list '}' ';'`，将字段写入类型表并计算偏移与总大小。
  - 字段列表：允许 `int`/`char`、指针（`*`）、数组维度（沿用 `array_dimensions`）、嵌套 `STRUCT IDENTIFIER` 字段。
  - 声明扩展：
    - `declaration : INT ... | CHAR ... | STRUCT IDENTIFIER struct_var_list ';'`
    - `struct_var_list` 支持普通变量与结构体数组：`IDENTIFIER` | `IDENTIFIER array_dimensions`
  - 左值/右值字段访问：
    - 在 `expression` 与 `assignment_statement` 引入字段访问链：
      - `postfix : IDENTIFIER chain` 与 `IDENTIFIER index_list chain`
      - `chain : /* 空 */ | chain '.' IDENTIFIER | chain '[' expression ']' | （可选）chain '->' IDENTIFIER`
    - 对于赋值左值：新增 `field_lhs` 产生式，生成写地址并写入；与现有 `*IDENTIFIER`、数组写共同复用。

## TAC 生成（tac.c/h）
- 类型管理：
  - 新增接口：`STRUCT_META *declare_struct_type(name, fields)`、`FIELD_META *append_field(...)`、`finalize_struct(STRUCT_META*)`。
  - 变量声明：
    - `TAC *declare_struct_var(char *name, STRUCT_META *meta)`：设置 `SYM::dtype=DT_STRUCT` 与 `etc=meta` 并生成 `TAC_VAR`。
    - `TAC *declare_struct_array_var(char *name, STRUCT_META *meta, int *dims, int ndims)`：`ARR_META.elem_size = meta->size`。
- 字段地址与读写：
  - 地址计算通用化：在现有数组地址计算基础上，
    - `EXP *do_struct_field_read(base, field_chain)`：累加字段常量偏移；若 `base` 是变量则 `&base + off`；若是数组元素则在其元素地址上累加；若是指向结构体指针则直接在指针值上累加。
      - 最后根据字段基本类型（`char`→字节，`int`/指针→字）设置 `final_addr->dtype = DT_PTR_CHAR/DT_PTR_INT`，生成 `TAC_DEREF_R`。
    - `TAC *do_struct_field_write(base, field_chain, val)`：同样生成最终地址并按字段基本类型选择 `TAC_DEREF_W`，为保证字节/字写正确，令 `final_addr->dtype` 映射为字段基本类型（`char`→`DT_CHAR`，其他→`DT_INT`）。
  - 嵌套/数组字段：`field_chain` 每步维护当前“元素类型描述”，遇到数组维度用 `ARR_META` 步幅计算线性偏移，遇到字段用 `FIELD_META.offset` 累加；支持任意层级。

## 目标代码生成（obj.c）
- `TAC_VAR`：
  - 若 `c->a->etc` 是 `ARR_META`，维持现状；
  - 若是 `STRUCT_META`，将 `size = meta->size` 并按作用域分配偏移；
  - 普通/指针变量仍为 4 字节（与现状一致）。
- `TAC_DEREF_R/W`：
  - 读取：基于指针的“元素类型”选择 `LDC`（字节）或 `LOD`（字）。当来自结构体字段时，我们保证 `c->b->dtype` 被设置为 `DT_PTR_CHAR` 或 `DT_PTR_INT` 以驱动正确指令。
  - 写入：基于目标元素类型（通过我们给 `c->a->dtype` 的映射）选择 `STC` 或 `STO`。对于写入指针值到结构体字段，强制使用 `STO`（通过设置 `c->a->dtype=DT_INT`）。

## 测试与验证
- 使用现有用例：
  - `testcase/struct.m`、`testcase/struct-arr.m`、`testcase/struct-ptr.m` 与 `case/advanced/*` 作为回归。
- 新增边界测试：
  - 多层嵌套字段与数组索引混合（如 `a.b[2].c[1][3].d`），读/写均覆盖。
  - 指针字段读写与指向的解引用组合（如 `(*p).f`、`p->f` 如启用）。
  - 零维/维度不匹配与未定义结构体、未定义字段的错误信息。
- 验证方法：
  - 编译生成 `.s/.x`，检查 `#` 注释中的 TAC 文本是否与预期一致（obj.c:618-623 输出）。
  - 运行示例程序，验证输出与内存布局正确性。

## 变更位置（带关键行）
- 词法：`mini.l`（识别 `STRUCT` 与 `DOT`）。
- 语法：`mini.y`（新增 `struct_definition`、`struct_var_list`、字段访问链；当前数组相关：400-411；声明：76-109）。
- TAC 接口：`tac.h`（新增 `DT_STRUCT/DT_PTR_STRUCT` 与声明接口）；`tac.c`（数组地址计算 866-983/986-1092 可复用；新增结构体类型表与字段地址计算）。
- 目标生成：`obj.c`（`TAC_VAR` 按 `STRUCT_META` 分配大小，510-537；`TAC_DEREF_R/W` 指令选择，572-594）。

## 实施步骤
1. 扩展 `mini.l`，加入 `STRUCT` 与 `DOT`（可选 `ARROW`）。
2. 扩展 `mini.y`，加入结构体定义、结构体变量声明与字段访问链（读/写），语义动作调用新的 TAC 接口。
3. 在 `tac.h/c` 实现 `STRUCT_META/FIELD_META` 与类型表管理，完成 `declare_struct_*` 与 `do_struct_field_{read,write}`；保证数组/字段链的地址计算覆盖嵌套。
4. 修改 `obj.c`：在 `TAC_VAR` 中识别结构体大小；在 `TAC_DEREF_R/W` 依据我们设置的 dtype 做字节/字选择，保证指针字段写为字写。
5. 运行现有用例与新增边界测试，逐一修正问题。

## 交付物
- 更新后的 `mini.l/mini.y/tac.h/tac.c/obj.c`。
- 通过 `struct.m/struct-arr.m/struct-ptr.m` 等用例的编译与运行结果。
- 简要变更说明与关键实现点注释（仅代码内必要注释）。