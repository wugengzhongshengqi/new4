## 目标
- 支持以 `int`/`char` 声明的函数返回类型与参数类型（形如 `int max(int x, int y)`、`char max(char x, char y)`）。
- 现有无类型写法 `main()` 继续保留兼容。
- 保证 `func-int.m`、`func-char.m` 两个用例能够编译并运行正确（返回值可被调用方获取，参数传递正确）。

## 语法扩展
- 在 `mini.y` 中扩展函数头与参数列表以携带类型：
  - 新增 `type_spec`：`INT { decl_dtype = DT_INT; } | CHAR { decl_dtype = DT_CHAR; }`（用于在语义动作中设置当前声明类型）。
  - 修改 `function` 产生式为带类型的函数头：
    - `function : type_spec IDENTIFIER '(' parameter_list_typed ')' block { $$ = do_func(declare_func($2), $4, $6); scope=0; sym_tab_local=NULL; }`
    - 保留原有无类型头的形式：`function : IDENTIFIER '(' parameter_list_typed ')' block { ... }` 以兼容 `main()`。
  - 将参数列表改为带类型的写法：
    - `parameter_list_typed : /* empty */ | type_spec IDENTIFIER { $$ = declare_para($2); } | parameter_list_typed ',' type_spec IDENTIFIER { $$ = join_tac($1, declare_para($4)); }`
- 代码参考：
  - 令牌与原函数规则位置：`/mnt/c/程序设计与编译/new4/mini.y:252`（函数规则）与 `:275-285`（参数列表规则）。
  - `INT/CHAR` 令牌已存在：`/mnt/c/程序设计与编译/new4/mini.y:38`。

## 语义与符号表
- 在 `declare_func` 中记录返回类型：将函数符号的 `dtype` 设置为当前 `decl_dtype`。
  - 变更位置：`/mnt/c/程序设计与编译/new4/tac.c:230-263`。
- 形式参数沿用现有 `declare_para`/`mk_var` 逻辑：其 `dtype` 取决于进入 `declare_para` 前被 `type_spec` 设置的 `decl_dtype`。
  - `mk_var` 使用 `decl_dtype` 已就绪：`/mnt/c/程序设计与编译/new4/tac.c:123-131`。

## 返回值传递修复
- 目前 `TAC_CALL` 的对象翻译未将被调函数在 `R_TP` 中的返回值写入调用方的结果临时变量，导致有返回值调用无法获得结果。
- 在对象翻译中为 `TAC_CALL`（`a != NULL` 有返回值）追加将 `R_TP` 载入到 `a` 的寄存器并更新寄存器描述符：
  - 伪代码：
    - `asm_call(c->a, c->b);`
    - `if(c->a != NULL) { r = reg_alloc(c->a); out_str(file_s, "\tLOD R%u,R%u\n", r, R_TP); rdesc_fill(r, c->a, MODIFIED); }`
  - 变更位置：`/mnt/c/程序设计与编译/new4/obj.c:486-489`（`case TAC_CALL`）。
- 被调函数返回路径已将返回值装载至 `R_TP`：`/mnt/c/程序设计与编译/new4/obj.c:305-319`。

## 兼容性与约定
- 参数按 4 字节槽位传递（现有帧布局）：`FORMAL_OFF` 递减步长为 4（`/mnt/c/程序设计与编译/new4/obj.h:25-28`），`char` 参数占用一个 4 字节槽（低字节有效），与当前代码生成一致。
- 局部/全局变量大小已依据 `dtype` 计算：`int=4`、`char=1`（`/mnt/c/程序设计与编译/new4/tac.c:2374-2380`）。
- 保留无类型函数头（如 `main()`）的旧写法，函数 `dtype` 默认不设置或由调用处不关心返回类型（返回传递通过 `R_TP` 完成）。

## 验证
- 构建并运行：`make`，随后针对以下用例编译、生成并执行：
  - `testcase/func-int.m`：`/mnt/c/程序设计与编译/new4/testcase/func-int.m:1-27`
  - `testcase/func-char.m`：`/mnt/c/程序设计与编译/new4/testcase/func-char.m:1-27`
- 期望：
  - 函数 `max` 的返回值在调用点被正确写入到临时变量（随后被赋值/输出）。
  - `char` 版本能正确比较、返回并输出字符。

## 实施变更清单
- 修改 `mini.y`：新增 `type_spec`，调整 `function` 与 `parameter_list`。
- 修改 `tac.c`：在 `declare_func` 中设置 `sym->dtype = decl_dtype`。
- 修改 `obj.c`：`case TAC_CALL` 为有返回值的调用追加 `R_TP -> a` 映射/载入。

## 备注
- 若后续需要更精细的 `char` 访存（字节级的形参/返回），可按指令集的字节访存扩展，但当前需求仅要求通过测试 `func-int`/`func-char`，上述实现即可满足。