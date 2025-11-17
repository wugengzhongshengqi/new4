## 目标
- 让 `testcase/for.m`、`testcase/for-bc.m` 编译并在虚拟机正常运行
- 在语法、语义生成（TAC）层面完整支持：`for(init; cond; iter) stmt`、`continue;`，并使 `break;` 在循环与 switch 内遵循就近作用域

## 词法
- 在 `mini.l` 增加关键字：`"for" -> FOR`、`"continue" -> CONTINUE`（紧邻现有 `while/switch/break` 规则）

## 语法
- 在 `mini.y`：
  - 声明新 token：`%token FOR CONTINUE`（`/mnt/c/程序设计与编译/new4/mini.y:37-41`）
  - 新增无分号赋值产生式，用于 for 头部：
    - `assign_no_semi : IDENTIFIER '=' expression | '*' IDENTIFIER '=' expression | IDENTIFIER index_list '=' expression | field_access '=' expression`
    - 语义动作沿用 `assignment_statement` 的各分支调用（`do_assign/do_deref_write/do_array_write/do_field_write`）
  - 新增 `for_statement` 产生式并接入 `statement`：
    - `for_statement : FOR '(' assign_no_semi ';' expression ';' assign_no_semi ')' block`
    - 语义动作：`$$ = do_for($3, $5, $7, $9);`
    - 在 `statement` 选择集中插入 `| for_statement`（`/mnt/c/程序设计与编译/new4/mini.y:290` 附近）
  - 新增 `continue` 语句：在 `statement` 中加入 `| CONTINUE ';' { $$ = do_continue(); }`

## 语义/TAC
- 在 `tac.h`：
  - 声明循环栈与 API：
    - `void enter_loop(SYM *begin_label, SYM *continue_label, SYM *end_label);`
    - `void exit_loop(void);`
    - `TAC *do_for(TAC *init, EXP *cond, TAC *iter, TAC *body);`
    - `TAC *do_continue(void);`
    - 更新 `do_break` 注释并保留声明（已有：`/mnt/c/程序设计与编译/new4/tac.h:271`）
- 在 `tac.c`：
  - 定义 `LOOP_STACK { SYM *begin_label; SYM *continue_label; SYM *end_label; LOOP_STACK *prev; }` 与静态指针 `loop_stack`。
  - 实现 `enter_loop/exit_loop`：成对压/弹栈。
  - 实现 `do_for`（三地址码降低）：
    - 结构：`init; Lbegin: ifz cond goto Lend; body; Lcont: iter; goto Lbegin; Lend:`
    - 在进入循环前 `enter_loop(Lbegin, Lcont, Lend)`，生成完毕后 `exit_loop()`。
  - 改造 `do_while`（`/mnt/c/程序设计与编译/new4/tac.c:483`）：
    - 不再调用 `do_if` 隐式生成标签；显式构造 `Lbegin/Lend`，并以 `enter_loop(Lbegin, Lbegin, Lend)` 管理 continue 与 break。
    - 结构：`Lbegin: ifz cond goto Lend; body; goto Lbegin; Lend:` 保持现有语义。
  - `do_break`（`/mnt/c/程序设计与编译/new4/tac.c:2570`）：
    - 修改为：若 `switch_stack` 存在，跳转到 `switch_stack->end_label`；否则若 `loop_stack` 存在，跳转到 `loop_stack->end_label`；否则报错“break not within loop/switch”。
  - 新增 `do_continue`：
    - 若 `loop_stack` 存在，生成 `TAC_GOTO` 至 `loop_stack->continue_label`；否则报错“continue not within loop”。

## 代码生成
- `obj.c` 中已支持 `TAC_LABEL/TAC_GOTO/TAC_IFZ`，无需改动（`tac_obj` 按序遍历生成汇编）。

## 测试与验证
- 重新生成并运行：
  - `./mini testcase/for.m && ./asm testcase/for.s && ./machine testcase/for.o`
  - `./mini testcase/for-bc.m && ./asm testcase/for-bc.s && ./machine testcase/for-bc.o`
- 关注点：
  - `for.m`：应从 0 输出到 `j-1`，末尾换行。
  - `for-bc.m`：
    - 第一段：当 `i>10` 打印 "break" 并提前结束该循环；
    - 第二段：当 `i==10` 打印 "continue"，跳过该次 `output i`，其余正常。

## 兼容性与语义细节
- `break` 优先匹配最近的 `switch`（C 语义），其次最近的循环；
- `continue` 始终作用于最近的循环：在 `for` 跳到迭代位置，在 `while` 跳到循环头；
- 目前不支持 `for` 头部的空 `init/cond/iter`；如需要可在语法中为三者添加 `/* empty */` 分支并在 `do_for` 中判空处理。

## 交付
- 按上述步骤更新 `mini.l`、`mini.y`、`tac.h`、`tac.c`；不引入新文件；完成后运行两项测试并给出输出截图与关键 TAC 片段供审阅。