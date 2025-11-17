/*
 * TAC 符号与指令定义
 * 包含符号类型、数据类型、TAC 操作码以及核心结构体。
 */
/* type of symbol：符号类别 */
#define SYM_UNDEF 0
#define SYM_VAR 1
#define SYM_FUNC 2
#define SYM_TEXT 3
#define SYM_INT 4
#define SYM_LABEL 5

/* 数据类型：基本类型与指针类型 */
#define DT_INT 0
#define DT_CHAR 1
#define DT_PTR_INT 2
#define DT_PTR_CHAR 3

/* TAC 操作码：三地址码的具体操作 */ 
#define TAC_UNDEF 0 /* undefine */
#define TAC_ADD 1 /* a=b+c */
#define TAC_SUB 2 /* a=b-c */
#define TAC_MUL 3 /* a=b*c */
#define TAC_DIV 4 /* a=b/c */
#define TAC_EQ 5 /* a=(b==c) */
#define TAC_NE 6 /* a=(b!=c) */
#define TAC_LT 7 /* a=(b<c) */
#define TAC_LE 8 /* a=(b<=c) */
#define TAC_GT 9 /* a=(b>c) */
#define TAC_GE 10 /* a=(b>=c) */
#define TAC_NEG 11 /* a=-b */
#define TAC_COPY 12 /* a=b */
#define TAC_GOTO 13 /* goto a */
#define TAC_IFZ 14 /* ifz b goto a */
#define TAC_BEGINFUNC 15 /* function begin */
#define TAC_ENDFUNC 16 /* function end */
#define TAC_LABEL 17 /* label a */
#define TAC_VAR 18 /* int a */
#define TAC_FORMAL 19 /* formal a */
#define TAC_ACTUAL 20 /* actual a */
#define TAC_CALL 21 /* a=call b */
#define TAC_RETURN 22 /* return a */
#define TAC_INPUT 23 /* input a */
#define TAC_OUTPUT 24 /* output a */
#define TAC_ADDR 25   /* a = &b */
#define TAC_DEREF_R 26 /* a = *b */
#define TAC_DEREF_W 27 /* *a = b */

/* 符号表项
 * type: 符号类别（变量/函数/文本/整型/标签）
 * scope: 作用域（0=全局，1=局部）
 * dtype: 数据类型（DT_INT/DT_CHAR/DT_PTR_INT/DT_PTR_CHAR）
 * name: 名称或文本内容
 * offset: 在静态区或帧内的偏移（由对象生成阶段分配）
 * value: 整型常量的值
 * label: 文本常量对应的唯一标签编号
 * address: 函数入口地址（生成阶段可填）
 * next: 链表下一结点（符号表）
 */
typedef struct sym
{
	/*	
		type:SYM_VAR name:abc value:98 offset:-1
		type:SYM_VAR name:bcd value:99 offset:4
		type:SYM_LABEL name:L1/max			
		type:SYM_INT value:1			
		type:SYM_FUNC name:max address:1234		
		type:SYM_TEXT name:"hello" label:10
	*/
    int type;
    int scope; /* 0:global, 1:local */
    int dtype;
    char *name;
    int offset;
    int value;
    int label;
    struct tac *address; /* SYM_FUNC */ 
    struct sym *next;
    void *etc;
} SYM;

/* 三地址码结点
 * prev/next: 构建时以 prev 串接，完成后以 next 正向遍历
 * op: 操作码（见上方 TAC_* 宏）
 * a/b/c: 操作数符号（不同 op 含义不同）
 */
typedef struct tac
{
	struct tac  *next;
	struct tac  *prev;
	int op;
	SYM *a;
	SYM *b;
	SYM *c;
	void *etc;
} TAC;

/* 表达式节点（用于语义动作拼接）
 * next: 用于参数列表逆向链接
 * tac: 生成该表达式的 TAC 片段
 * ret: 表达式结果所在的符号（常为临时）
 */
typedef struct exp
{
	struct exp *next; /* for argument list */
	TAC *tac; /* code */
	SYM *ret; /* return value */
	void *etc;
} EXP;

/* 由语法/语义阶段维护的全局变量
 * file_x/file_s: 输出文件句柄（文本/目标）
 * yylineno: 当前词法/语法分析行号
 * scope/next_tmp/next_label: 作用域与编号状态
 * sym_tab_global/sym_tab_local: 全局/局部符号表头
 * tac_first/tac_last: TAC 链首/尾（构建/遍历）
 * decl_dtype: 最近声明使用的数据类型
 */
extern FILE *file_x, *file_s;
extern int yylineno, scope, next_tmp, next_label;
extern SYM *sym_tab_global, *sym_tab_local;
extern TAC *tac_first, *tac_last;
extern int decl_dtype;

/* 接口函数声明：构造/串接/输出/翻译等 */
void tac_init();
void tac_complete();
TAC *join_tac(TAC *c1, TAC *c2);
void out_str(FILE *f, const char *format, ...);
void out_sym(FILE *f, SYM *s);
void out_tac(FILE *f, TAC *i);
SYM *mk_label(char *name);
SYM *mk_tmp(void);
SYM *mk_const(int n);
SYM *mk_text(char *text);
TAC *mk_tac(int op, SYM *a, SYM *b, SYM *c);
EXP *mk_exp(EXP *next, SYM *ret, TAC *code);
char *mk_lstr(int i);
SYM *get_var(char *name); 
SYM *declare_func(char *name);
TAC *declare_var(char *name);
TAC *declare_para(char *name);
TAC *do_func(SYM *name,    TAC *args, TAC *code);
TAC *do_assign(SYM *var, EXP *exp);
TAC *do_output(SYM *var);
TAC *do_input(SYM *var);
TAC *do_call(char *name, EXP *arglist);
TAC *do_if(EXP *exp, TAC *stmt);
TAC *do_test(EXP *exp, TAC *stmt1, TAC *stmt2);
TAC *do_while(EXP *exp, TAC *stmt);
EXP *do_bin( int binop, EXP *exp1, EXP *exp2);
EXP *do_cmp( int binop, EXP *exp1, EXP *exp2);
EXP *do_un( int unop, EXP *exp);
EXP *do_call_ret(char *name, EXP *arglist);
TAC *declare_ptr_var(char *name);
EXP *do_addr(SYM *var);
EXP *do_deref_read(EXP *ptr);
TAC *do_deref_write(SYM *ptr, EXP *val);
TAC *declare_array_var(char *name, int *dims, int ndims);
EXP *do_array_read(SYM *arr, EXP *indices);
TAC *do_array_write(SYM *arr, EXP *indices, EXP *val);
void error(const char *format, ...);