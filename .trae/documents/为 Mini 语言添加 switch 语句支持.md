## 总览
- 目标：在 Mini 语言中新增 `switch`/`case`/`default`/`break` 语句，语义为按选择表达式与常量匹配分支执行，支持可选 `default`，每个 `case` 默认不落入下一个分支（自动跳到 `switch` 尾部），`break` 映射为跳到 `switch` 尾标签。
- 范围：更新词法/语法（`mini.l`、`mini.y`），在中间代码层新增 `do_switch`（`tac.c`），沿用现有跳转与比较 TAC（无需新增后端指令），用 `testcase/switch.m` 做验证。

## 词法与语法修改
- 词法：在 `mini.l` 为关键字增加 token 输出（参考已有关键字区域 `/mnt/c/程序设计与编译/new4/mini.l:14-32`）
  - `switch`→`SWITCH`
  - `case`→`CASE`
  - `default`→`DEFAULT`
  - `break`→`BREAK`
- 语法：在 `mini.y` 添加 token 声明与语句规则（token 区域约在 `/mnt/c/程序设计与编译/new4/mini.y:20-35`）
  - 声明：`%token SWITCH CASE DEFAULT BREAK`
  - 在 `statement` 并入 `switch_statement`（`/mnt/c/程序设计与编译/new4/mini.y:283-292`）
  - 语法形态：
    - `switch_statement: SWITCH '(' expression ')' '{' case_list default_opt '}'`
    - `case_list: case_clause | case_list case_clause`
    - `case_clause: CASE INT_CONST ':' statement_list`（第一版仅支持整型常量）
    - `default_opt: /* empty */ | DEFAULT ':' statement_list`
  - `break`：在 `statement` 增加 `BREAK ';'`，规约时生成跳转到当前 `switch` 的结束标签（见下节 `do_switch` 的作用域处理）。

## TAC 生成（tac.c）
- 新增控制流构造函数（放在现有 `do_if`/`do_test`/`do_while` 附近，参考 `/mnt/c/程序设计与编译/new4/tac.c:449-491` 的模式）：
  - `do_switch(EXP *sel, CASES *cases, TAC *default_block)`：核心流程
    - 生成统一结束标签 `Lend = mk_label(mk_lstr(next_label++))`
    - 对每个 `case` 常量 `ci`：
      - `t = do_cmp(TAC_EQ, sel, mk_const(ci))`（参考比较生成 `/mnt/c/程序设计与编译/new4/tac.c:288-311`）
      - `IFZ t → Lnext_i`（使用 `TAC_IFZ`）
      - 拼接 `case` 的 `statement_list` TAC
      - `GOTO Lend`（避免落入下一个分支）
      - `Lnext_i:`（`mk_label`）
    - 若有 `default`：直接拼接其 `statement_list`
    - 末尾贴 `Lend`
  - `break` 处理：在进入 `do_switch` 时记录当前 `switch` 的 `Lend` 到线程局部或全局栈（简易可用全局指针），`BREAK` 规约生成 `TAC_GOTO Lend`；离开 `do_switch` 时弹栈。可类比 `do_while` 中标签与跳转的组织（`/mnt/c/程序设计与编译/new4/tac.c:482-491`）。
- 复用基础设施：
  - 标签与临时：`mk_label`、`mk_lstr(next_label++)`、`mk_tmp`（`/mnt/c/程序设计与编译/new4/tac.c:167-205`）
  - 常量与类型：`mk_const`（`/mnt/c/程序设计与编译/new4/tac.c:564+`），选择表达式与比较结果沿用整型 0/1 语义。

## 后端代码生成（obj.c）
- 不新增任何新的 TAC 操作码；使用现有：`TAC_EQ`、`TAC_IFZ`、`TAC_GOTO`、`TAC_LABEL`。
- `asm_code` 已覆盖这些分支（`/mnt/c/程序设计与编译/new4/obj.c:431-476`、`/mnt/c/程序设计与编译/new4/obj.c:390+`），无需改动即可翻译 `switch` 所生成的 TAC。

## 语义规则与限制
- 第一版约束：
  - `case` 值为整型常量；重复值按先匹配先执行。
  - 不支持 C 风格隐式 fallthrough；每个 `case` 在其语句后自动 `GOTO Lend`，除非将来扩展特性。
  - `break` 仅在 `switch` 内生效，生成到当前 `switch` 的 `Lend`；若出现在非 `switch` 上下文可报错或忽略。
- 后续可选扩展：
  - 允许表达式常量或多类型匹配（需明确类型提升规则）。
  - 支持显式 fallthrough（通过省略 `GOTO Lend` 并引入 `fallthrough` 关键字或语义开关）。

## 测试与验证
- 用例：`/mnt/c/程序设计与编译/new4/testcase/switch.m`（6–25 行示例）作为语义对照；补充边界：
  - 单一 `case`、无匹配且有/无 `default`
  - 多 `case`、首/中/末匹配
  - `break` 在分支中途跳出
  - 嵌套 `switch`（可选）与与 `while` 并列场景
- 验证方式：
  - 生成 TAC 文本旁注（`out_tac` 已输出，见 `/mnt/c/程序设计与编译/new4/tac.c:617-689`）检查控制流骨架。
  - 运行编译器对 `switch.m` 产物，观察输出是否符合预期。

## 变更点一览
- `mini.l`：增加 `switch/case/default/break` 关键字到 token 映射。
- `mini.y`：
  - `%token SWITCH CASE DEFAULT BREAK` 声明
  - `statement` 并入 `switch_statement` 与 `BREAK ';'`
  - 定义 `switch_statement`、`case_list`、`case_clause`、`default_opt`
- `tac.c`：新增 `do_switch`；为 `BREAK` 增加到当前 `switch` 的 `TAC_GOTO Lend` 生成；用标签与条件跳转拼接分支。
- `obj.c`：无改动。