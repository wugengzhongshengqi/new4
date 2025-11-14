## 背景与目标
- 为源语言添加指针声明、取地址`&`、解引用`*`（右值与左值），通过测试：`testcase/ptr-int.m`、`testcase/ptr-char.m`、`testcase/ptr-char-int.m`。
- 保持现有算术、比较、I/O行为不变；不实现指针算术、数组/结构交互、二级指针。

## 影响面
- 需修改：`mini.y`（语法）、`tac.h`（类型与TAC枚举）、`tac.c`（TAC构造与声明）、`obj.c`（目标码生成）、`tac.c out_tac`（打印新TAC）。
- 不改动：`mini.l`（默认字符规则已能返回`&`、`*`）、`asm.y`、`machine.c`（已有指令族`LOD/LDC/STO/STC`满足按地址读写）。

## 语法扩展（mini.y）
- 指针声明：在`variable_list`新增分支支持`*标识符`与逗号分隔组合（如`int a,*pa,b; char a,*pa,b;`）。
- 取地址表达式：新增`& IDENTIFIER`，返回其地址值。
- 解引用右值：新增`* expression`（一元`*`，使用`%prec`区分乘法与解引用）。
- 解引用左值赋值：新增`* IDENTIFIER '=' expression`，对指针指向位置写入。
- 新增一元优先级符号（如`UDEREF/ UADDR`）以设定解析优先级，仿照`UMINUS`。

## 类型系统（tac.h）
- 数据类型新增：`DT_PTR_INT`、`DT_PTR_CHAR` 用于区分指针指向的基础类型；现有`SYM.dtype`沿用。
- 语义约束：
  - 指针声明类型由当前`decl_dtype`派生（`int`→`DT_PTR_INT`，`char`→`DT_PTR_CHAR`）。
  - `&a` 返回的表达式类型为对应指针类型；`*p`返回其指向基础类型。
  - 赋值与I/O不做强类型检查，按当前工程风格最小化约束。

## TAC 扩展（tac.h / tac.c）
- 新增TAC枚举：`TAC_ADDR`（`a = &b`）、`TAC_DEREF_R`（`a = *b`）、`TAC_DEREF_W`（`*a = b`）。
- 新增API：
  - `declare_ptr_var(char *name)`：根据`decl_dtype`声明指针变量并设置`dtype`为`DT_PTR_INT/DT_PTR_CHAR`。
  - `EXP *do_addr(SYM *var)`：生成临时承载地址，TAC：`TAC_ADDR(tmp, var)`。
  - `EXP *do_deref_read(EXP *ptr)`：生成临时承载解引用结果，TAC：`TAC_DEREF_R(tmp, ptr->ret)`。
  - `TAC *do_deref_write(SYM *ptr, EXP *val)`：TAC：`TAC_DEREF_W(ptr, val->ret)`。
- `out_tac`打印格式：
  - `a = &b`、`a = *b`、`*a = b`，便于调试。

## 目标码生成（obj.c）
- `TAC_ADDR`：计算符号地址并放入结果寄存器：
  - 局部：`LOD Rd,BP` → `ADD Rd,<offset>`；全局：`LOD Rd,STATIC` → `ADD Rd,<offset>`。
  - 使用寄存器描述符将`Rd`映射到目标`SYM`并标记`MODIFIED`。
- `TAC_DEREF_R`：按指针指向类型选择读指令：
  - `DT_PTR_CHAR`→`LDC Rd,(Rp)`；否则→`LOD Rd,(Rp)`。
- `TAC_DEREF_W`：按指针指向类型选择写指令：
  - `DT_PTR_CHAR`→`STC (Rp),Rv`；否则→`STO (Rp),Rv`。
- 将三者接入`asm_code`分派；复用现有寄存器分配/写回逻辑。

## 测试与验证
- 用例：
  - `testcase/ptr-int.m`：`pa=&a; *pa=111; ptr=pa; *ptr=222;` 输出应体现对`a`的两次更新。
  - `testcase/ptr-char.m`：`*pa='A'; *ptr='B'` 后字符输出应为`A`、`B`（走`OTC`）。
  - `testcase/ptr-char-int.m`：`b=*pa; j=*pi;` 分别为字节/字读取，输出正确。
- 回归：`testcase/char-int.m`、`int.m`、`func-*.m`正常；生成的`.x`与`.s`含有新TAC与对应汇编指令。

## 非目标与边界
- 不支持：指针算术（`p+1`等）、多级指针、数组/结构交互、复杂左值如`*(p+1)`。
- 按字节/字大小读取的边界由`dtype`决定；无显式类型转换。

## 实施步骤
1. 修改`tac.h`：新增`DT_PTR_INT/DT_PTR_CHAR`与`TAC_ADDR/TAC_DEREF_R/TAC_DEREF_W`。
2. 修改`tac.c`：实现`declare_ptr_var`、`do_addr/ do_deref_read/ do_deref_write`与`out_tac`分支。
3. 修改`mini.y`：扩展`variable_list`、`expression`与`assignment_statement`的产生式与调用。
4. 修改`obj.c`：在`asm_code`实现三类新TAC的目标码输出；按`dtype`选`LOD/LDC`与`STO/STC`。
5. 编译并运行三个指针测试与若干回归用例，核对输出。

## 交付物
- 已修改源文件与通过的测试输出；更新的`.x`（TAC列表）与`.s`（汇编）可用于审阅与调试。

请确认该实施计划；确认后我将开始修改并验证通过上述三个测试。