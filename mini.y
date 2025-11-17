%{
/*
 * 语法分析器（Bison）
 * 定义 Mini 语言的语法、语义值联合体与结合/优先级，
 * 在各产生式动作中构造 TAC 中间代码。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"

int yylex();
void yyerror(char* msg);

%}

/* 语义值联合体：用于在规则间传递字符、字符串、符号、TAC 与表达式 */
%union
{
    char character;
    char *string;
    SYM *sym;
    TAC *tac;
    EXP	*exp;
	struct {
		int dims[16];
		int ndims;
	} arr_dims;
	EXP *exp_list;
	void *meta;
	struct {
		void *chain;
	} field_chain;
	void *case_list;
}

/* 终结符与关键字 */
%token INT CHAR STRUCT DOT EQ NE LT LE GT GE UMINUS UADDR UDEREF IF ELSE WHILE FUNC INPUT OUTPUT RETURN
%token SWITCH CASE DEFAULT BREAK
%token FOR CONTINUE
%token <string> INTEGER IDENTIFIER TEXT
%token <character> CHARACTER

/* 运算符优先级与结合性 */
%left EQ NE LT LE GT GE
%left '+' '-'
%left '*' '/'
%right UMINUS
%right UADDR UDEREF
%left DOT '[' '('

/* 非终结符的语义类型 */
%type <tac> program function_declaration_list function_declaration function parameter_list variable_list statement assignment_statement return_statement if_statement while_statement call_statement block declaration_list declaration statement_list input_statement output_statement
%type <exp> argument_list expression_list expression call_expression
%type <sym> function_head
%type <tac> variable_declaration
%type <arr_dims> array_dimensions
%type <exp_list> index_list
%type <meta> struct_definition       
%type <meta> field_list            
%type <meta> field_declarators     
%type <tac> struct_var_list        
%type <tac> struct_var_declaration   
%type <field_chain> field_access    
%type <tac> switch_statement
%type <case_list> case_list_opt
%type <case_list> case_list
%type <case_list> case_clause
%type <tac> default_opt
%type <tac> for_statement for_init for_iter
%type <exp> for_cond

%%

/* 程序由若干函数/声明组成，完成后反转并得到首指针 */
/* program：整个编译单元的入口，完成 TAC 的链反转以便后续遍历 */
program : function_declaration_list
{
	tac_last=$1;
	tac_complete();
}
;

/* 连接多个函数或声明的 TAC 片段 */
/* function_declaration_list：多个声明/函数的串接，维持顺序 */
function_declaration_list : function_declaration
| function_declaration_list function_declaration
{
	$$=join_tac($1, $2);
}
;

function_declaration : function
    {
        $$ = $1;  /* 返回 TAC* */
    }
| declaration
    {
        $$ = $1;  /* 返回 TAC* */
    }
| struct_definition
    {
        $$ = NULL;  /* 结构体定义不生成 TAC，返回 NULL */
    }
;

struct_definition : STRUCT IDENTIFIER '{' field_list '}' ';'
{
	$$ = finalize_struct($2, $4);
}
;

field_list : INT field_declarators ';'
{
	$$ = $2;
	set_field_type($$, FIELD_INT);
}
| CHAR field_declarators ';'
{
	$$ = $2;
	set_field_type($$, FIELD_CHAR);
}
| STRUCT IDENTIFIER field_declarators ';'
{
	$$ = $3;
	set_field_struct_type($$, $2);
}
| field_list INT field_declarators ';'
{
	$$ = append_fields($1, $3);
	set_field_type($3, FIELD_INT);
}
| field_list CHAR field_declarators ';'
{
	$$ = append_fields($1, $3);
	set_field_type($3, FIELD_CHAR);
}
| field_list STRUCT IDENTIFIER field_declarators ';'
{
	$$ = append_fields($1, $4);
	set_field_struct_type($4, $3);
}
;

field_declarators : IDENTIFIER
{
	$$ = create_field($1, NULL, 0);
}
| '*' IDENTIFIER
{
	$$ = create_field_ptr($2);
}
| IDENTIFIER array_dimensions
{
	$$ = create_field($1, $2.dims, $2.ndims);
}
| field_declarators ',' IDENTIFIER
{
	$$ = append_field_name($1, $3, NULL, 0);
}
| field_declarators ',' '*' IDENTIFIER
{
	$$ = append_field_name_ptr($1, $4);
}
| field_declarators ',' IDENTIFIER array_dimensions
{
	$$ = append_field_name($1, $3, $4.dims, $4.ndims);
}
;

/* 变量/指针声明，影响后续变量 dtype（int/char） */
/* declaration：设置当前声明的数据类型并生成对应变量/指针的 TAC */
declaration : INT { decl_dtype=DT_INT; } variable_list ';'
{
    $$=$3;
}
| CHAR { decl_dtype=DT_CHAR; } variable_list ';'
{
    $$=$3;
}
| STRUCT IDENTIFIER
{
	decl_struct = lookup_struct($2);
	if(!decl_struct) {
		yyerror("Undefined struct");
	}
} 
struct_var_list ';'
{
	$$=$4;
}
;

struct_var_list : struct_var_declaration
| struct_var_list ',' struct_var_declaration
{
	$$=join_tac($1, $3);
}
;

struct_var_declaration : IDENTIFIER
{
	$$=declare_struct_var($1, decl_struct);
}
| IDENTIFIER array_dimensions
{
	$$=declare_struct_array($1, decl_struct, $2.dims, $2.ndims);
}
;

/* variable_list：支持普通变量、指针变量、数组变量 */
variable_list : variable_declaration
| variable_list ',' variable_declaration
{
    $$=join_tac($1, $3);
}
;

/* variable_declaration：单个变量的声明（普通/指针/数组） */
variable_declaration : IDENTIFIER
{
    $$=declare_var($1);
}
| '*' IDENTIFIER
{
    $$=declare_ptr_var($2);
}
| IDENTIFIER array_dimensions
{
    $$=declare_array_var($1, $2.dims, $2.ndims);
}
;

/* array_dimensions：数组维度列表 */
array_dimensions : '[' INTEGER ']'
{
    $$.dims[0] = atoi($2);
    $$.ndims = 1;
}
| array_dimensions '[' INTEGER ']'
{
    if ($1.ndims >= 16) {
        yyerror("Array dimensions exceed maximum (16)");
    }
    $$ = $1;
    $$.dims[$$.ndims++] = atoi($3);
}
;

/* 函数定义：进入局部作用域，参数与块体合并为函数体 */
/* function：函数定义，进入局部作用域，参数与块体拼接为函数体 */
function : function_head '(' parameter_list ')' block
{
	$$=do_func($1, $3, $5);
	scope=0; /* Leave local scope. */
	sym_tab_local=NULL; /* Clear local symbol table. */
}
| error
{
	error("Bad function syntax");
	$$=NULL;
}
;

/* 声明函数名并切入局部符号表 */
/* function_head：声明函数名，切入局部符号表上下文 */
function_head : IDENTIFIER
{
	$$=declare_func($1);
	scope=1; /* Enter local scope. */
	sym_tab_local=NULL; /* Init local symbol table. */
}
;

/* 参数列表，可为空 */
/* parameter_list：形式参数列表，可为空 */
parameter_list : IDENTIFIER
{
	$$=declare_para($1);
}               
| parameter_list ',' IDENTIFIER
{
	$$=join_tac($1, declare_para($3));
}               
|
{
	$$=NULL;
}
;

/* 语句集合：赋值/IO/调用/返回/选择/循环/块 */
/* statement：支持赋值/输入/输出/调用/返回/选择/循环/块 */
statement : assignment_statement ';'
| input_statement ';'
| output_statement ';'
| call_statement ';'
| return_statement ';'
| if_statement
| while_statement
| for_statement
| switch_statement 
| BREAK ';'
{
	$$ = do_break();
}
| CONTINUE ';'
{
	$$ = do_continue();
}
| block
| error
{
	error("Bad statement syntax");
	$$=NULL;
}
;

/* 代码块：先声明再语句，TAC 串接 */
/* block：声明列表与语句列表的串接 */
block : '{' declaration_list statement_list '}'
{
	$$=join_tac($2, $3);
}               
;

/* 声明列表，可为空 */
/* declaration_list：可为空的声明串接 */
declaration_list        :
{
	$$=NULL;
}
| declaration_list declaration
{
	$$=join_tac($1, $2);
}
;

/* 语句列表，可串接 */
/* statement_list：可为空的语句串接 */
statement_list :
{
    $$ = NULL;
}
| statement_list statement
{
	$$=join_tac($1, $2);
}               
;

/* 赋值与指针写 */
/* assignment_statement：普通赋值或指针写（*id = expr） */
assignment_statement : IDENTIFIER '=' expression
{
    $$=do_assign(get_var($1), $3);
}
| '*' IDENTIFIER '=' expression
{
    $$=do_deref_write(get_var($2), $4);
}
| IDENTIFIER index_list '=' expression
{
	$$ = do_array_write(get_var($1),$2,$4);
}
| field_access '=' expression
{
	$$ = do_field_write($1.chain, $3);
}
;

field_access : IDENTIFIER DOT IDENTIFIER
{
	$$.chain = create_field_access($1, $3);
}
| IDENTIFIER index_list DOT IDENTIFIER
{
    $$.chain = create_field_access_array($1, $2, $4);
}
| field_access DOT IDENTIFIER
{
	$$.chain = append_field_access($1.chain, $3);
}
| field_access '[' expression ']'
{
    EXP *single_index = $3;
    single_index->next = NULL;  /* 确保是单元素列表 */
    $$.chain = append_array_access($1.chain, single_index);
}
;

/* 表达式：算术/比较/括号/字面量/取址/解引用/变量/调用 */
/* expression：算术/比较/取负/括号/常量/取址/解引用/变量/调用 */
expression : expression '+' expression
{
	$$=do_bin(TAC_ADD, $1, $3);
}
| expression '-' expression
{
	$$=do_bin(TAC_SUB, $1, $3);
}
| expression '*' expression
{
	$$=do_bin(TAC_MUL, $1, $3);
}
| expression '/' expression
{
	$$=do_bin(TAC_DIV, $1, $3);
}
| '-' expression  %prec UMINUS
{
	$$=do_un(TAC_NEG, $2);
}
| expression EQ expression
{
	$$=do_cmp(TAC_EQ, $1, $3);
}
| expression NE expression
{
	$$=do_cmp(TAC_NE, $1, $3);
}
| expression LT expression
{
	$$=do_cmp(TAC_LT, $1, $3);
}
| expression LE expression
{
	$$=do_cmp(TAC_LE, $1, $3);
}
| expression GT expression
{
	$$=do_cmp(TAC_GT, $1, $3);
}
| expression GE expression
{
	$$=do_cmp(TAC_GE, $1, $3);
}
| '(' expression ')'
{
	$$=$2;
}               
| INTEGER
{
    $$=mk_exp(NULL, mk_const(atoi($1)), NULL);
}
| CHARACTER
{
    $$=mk_exp(NULL, mk_const((int)$1), NULL);
}
| '&' IDENTIFIER %prec UADDR
{
    $$=do_addr(get_var($2));
}
| '&' field_access %prec UADDR
{
    $$=do_field_addr($2.chain);
}
| '*' expression %prec UDEREF
{
    $$=do_deref_read($2);
}
| IDENTIFIER
{
    $$=mk_exp(NULL, get_var($1), NULL);
}
| IDENTIFIER index_list
{
	$$ = do_array_read(get_var($1), $2);
}
| field_access
{
	$$ = do_field_read($1.chain);
}
| call_expression
{
	$$=$1;
}               
| error
{
	error("Bad expression syntax");
	$$=mk_exp(NULL, NULL, NULL);
}
;

/* 参数表达式列表，可为空 */
/* argument_list：调用参数列表，可为空 */
argument_list           :
{
	$$=NULL;
}
| expression_list
;

/* 用逗号分隔的表达式列表，逆向链入 next */
/* expression_list：用 next 逆向链接的逗号表达式列表 */
expression_list : expression
|  expression_list ',' expression
{
	$3->next=$1;
	$$=$3;
}
;

/* 输入：读取到变量（按 dtype 选择输入指令） */
/* input_statement：将输入读入指定变量，根据 dtype 选择输入指令 */
input_statement : INPUT IDENTIFIER
{
	$$=do_input(get_var($2));
}
;

/* 输出：变量或文本 */
/* output_statement：输出变量或文本常量 */
output_statement : OUTPUT IDENTIFIER
{
	$$=do_output(get_var($2));
}
| OUTPUT TEXT
{
	$$=do_output(mk_text($2));
}
;

/* 返回：生成 TAC_RETURN，并将表达式代码前接 */
/* return_statement：生成 TAC_RETURN 并前接表达式代码 */
return_statement : RETURN expression
{
	TAC *t=mk_tac(TAC_RETURN, $2->ret, NULL, NULL);
	t->prev=$2->tac;
	$$=t;
}               
;

/* 条件：if 与 if-else */
/* if_statement：if 或 if-else 结构，使用 IFZ/GOTO/LABEL 组织控制流 */
if_statement : IF '(' expression ')' block
{
	$$=do_if($3, $5);
}
| IF '(' expression ')' block ELSE block
{
	$$=do_test($3, $5, $7);
}
;

/* 循环：while */
/* while_statement：循环结构，以标签和 GOTO 回到循环首 */
while_statement : WHILE '(' expression ')' 
{
    /* 中间动作：在解析 block 之前设置循环上下文 */
    enter_loop_context();
}
block
{
    /* 生成 TAC 并退出上下文 */
    $$ = do_while($3, $6);
    exit_loop_context();
}
;

/* 无返回值调用 */
/* call_statement：无返回值调用，生成 ACTUAL + CALL */
call_statement : IDENTIFIER '(' argument_list ')'
{
	$$=do_call($1, $3);
}
;

/* 有返回值调用 */
/* call_expression：有返回值调用，预分配临时保存返回值 */
call_expression : IDENTIFIER '(' argument_list ')'
{
	$$=do_call_ret($1, $3);
}
;

/* index_list：数组索引列表（逆向链接） */
index_list : '[' expression ']'
{
    $$ = $2;
    $$->next = NULL;
}
| index_list '[' expression ']'
{
    $$ = $3;
    $$->next = $1;  /* 逆向链接，后续需要反转 */
}
;

/* ========== ✅ 最终版本：无冲突的 switch 规则 ========== */

/* switch_statement */
switch_statement : SWITCH '(' expression ')' 
{
    $<sym>$ = enter_switch();
}
'{' case_list_opt default_opt '}'
{
    $$ = exit_switch($3, $7, $8, $<sym>5);
}
;

/* case_list_opt：可选的 case 列表 */
case_list_opt : /* empty */
{
    $$ = NULL;
}
| case_list
{
    $$ = $1;
}
;

/* case_list：一个或多个 case */
case_list : case_clause
{
    $$ = $1;
}
| case_list case_clause
{
    $$ = append_case($1, $2);
}
;

/* case_clause：单个 case */
case_clause : CASE INTEGER ':' statement_list
{
    $$ = mk_case(atoi($2), $4);
}
;

/* default_opt：可选的 default */
default_opt : /* empty */
{
    $$ = NULL;
}
| DEFAULT ':' statement_list
{
    $$ = $3;
}
;

/* for 语句 */
for_statement : FOR '(' for_init ';' for_cond ';' for_iter ')' 
{
    /* 中间动作：在解析 block 之前设置循环上下文 */
    enter_loop_context();
}
block
{
    /* 生成 TAC 并退出上下文 */
    $$ = do_for($3, $5, $7, $10);
    exit_loop_context();
}
;
/* 可选的初始化 */
for_init : /* empty */
{
    $$ = NULL;
}
| IDENTIFIER '=' expression
{
    $$ = do_assign(get_var($1), $3);
}
| expression
{
    $$ = $1->tac;
}
;
/* 可选的条件 */
for_cond : /* empty */
{
    $$ = NULL;
}
| expression
{
    $$ = $1;
}
;
/* 可选的迭代 */
for_iter : /* empty */
{
    $$ = NULL;
}
| IDENTIFIER '=' expression
{
    $$ = do_assign(get_var($1), $3);
}
| expression
{
    $$ = $1->tac;
}
;


%%

/* 语法错误输出：包含行号 */
void yyerror(char* msg) 
{
	fprintf(stderr, "%s: line %d\n", msg, yylineno);
	exit(0);
}
