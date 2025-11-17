## 目标

* 在保留现有整数与字符串能力的前提下，新增 `char` 类型，按 4 字节布局（与 `int` 同宽）。

* 语法可声明 `char` 变量；表达式支持字符字面量；I/O 根据变量的类型选择字符或整数指令。

* 不引入复杂的类型检查；算术/比较仍按整数语义。仅对声明与 I/O 区分 `int`/`char`。

## 词法

* 文件：`mini.l`

* 新增关键字：`"char" { return CHAR; }`（参照 `mini.l:10` 的 `int` 规则放置）

* 新增字符字面量规则：识别单引号字符（如 `a`, `b`），设置 `yylval.character` 并返回 `CHARACTER`（放置在数字与字符串规则附近，参考 `mini.l:29-37`）。

## 语法

* 文件：`mini.y`

* Token 声明：在 `mini.y:21` 增加 `CHAR`；在 `%token` 中增加 `<character> CHARACTER`。

* 声明产生式：在 `mini.y:53` 附近新增 `declaration : CHAR { set_decl_dtype(DTYPE_CHAR); } variable_list ';'`；原有 `INT` 声明改为在规约时调用 `set_decl_dtype(DTYPE_INT)`。

* 表达式：在 `mini.y:196-205` 附近增加一条 `| CHARACTER { $$=mk_exp(NULL, mk_const((int)$1), NULL); }`，使字符字面量可参与赋值与运算（按整数语义）。

## 符号/IR

* 文件：`tac.h`, `tac.c`

* 结构体：在 `tac.h:46-55` 的 `SYM` 中新增 `int dtype;`（数据类型，区分 `int`/`char`），并在头部增加 `#define DTYPE_INT 0`、`#define DTYPE_CHAR 1`。

* 声明上下文：在 `tac.c:9` 附近引入全局 `int decl_dtype=DTYPE_INT;` 及 `void set_decl_dtype(int)`；默认 `DTYPE_INT`。

* 变量构造：在 `tac.c:63` 的 `mk_var` 中给 `sym->dtype=decl_dtype;`（参数与局部默认仍为 `DTYPE_INT`，除非处于 `CHAR` 声明上下文）。

* 常量：`mk_const(int)` 保持返回 `SYM_INT`，不区分 `char` 与 `int` 常量（算术/比较继续按整数）。

## 代码生成

* 文件：`obj.c`

* 输入（`TAC_INPUT`）：在 `obj.c:400-405` 将 `ITI` 改为按变量类型分支：`sym->dtype==DTYPE_CHAR ? ITC : ITI`，并同样写回 `R15` 到目标寄存器。

* 输出（`TAC_OUTPUT`）：在 `obj.c:407-419` 的变量分支内，根据 `sym->dtype` 选择 `OTC`（char）或 `OTI`（int）；字符串仍用 `OTS`。

* 内存布局：保持现有 `obj.h:12-15` 以 4 字节步进为局部/全局偏移（满足“char 也设计为 4 字节”）。

## 汇编/虚机联动

* 现状：`ITC/OTC` 已在汇编与虚机实现（见 `asm.y:494,498`、`inst.h:4,7`、`machine.c:76,88`）。

* 仅需前端按类型发出相应指令，无需调整汇编器/虚机。

## 测试

* 示例 1：字符 I/O

  * 源码：`char c; input c; output c;`

  * 期望：读取单字符并输出同字符（前端生成 `ITC/OTC`）。

* 示例 2：字符赋值与整数运算

  * 源码：`char c; int x; c='A'; x=c+1; output x;`

  * 期望：输出 `66`（算术按整数语义）；`c` 用 `OTC` 输出时显示 `A`。

* 构建与运行：保持现有 `make` 流程，验证 `.s` 中是否出现 `ITC/OTC`，并用虚机运行观测输出。

## 兼容性与限制

* 仅为 I/O 与声明区分 `char`/`int`；表达式统一按整数处理，不做隐式类型提升或静态检查。

* 实参/形参暂按 `int` 处理（`parameter_list` 未带类型）；如需为参数带类型，可后续扩展类似声明上下文机制。

## 变更概览（按文件）

* `mini.l`：增加 `char` 关键字与字符字面量规则。

* `mini.y`：新增 `CHAR/CHARACTER` token；扩展声明与表达式。

* `tac.h/tac.c`：在符号上增加 `dtype` 字段与声明上下文；`mk_var` 记录类型。

* `obj.c`：`TAC_INPUT/TAC_OUTPUT` 按 `dtype` 选择 `ITC/OTC` 或 `ITI/OTI`；内存偏移逻辑不变。

