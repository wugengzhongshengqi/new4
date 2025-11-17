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
#define DT_PTR 2
#define DT_STRUCT 3
#define DT_ARRAY 4

/* 字段类型枚举 */
#define FIELD_INT 1
#define FIELD_CHAR 2
#define FIELD_PTR 3
#define FIELD_STRUCT 4
#define FIELD_ARRAY 5

/* 数组元素类型枚举 */
#define ELEM_INT 1
#define ELEM_CHAR 2
#define ELEM_PTR 3
#define ELEM_STRUCT 4

/* 作用域常量 */
#define SCOPE_GLOBAL 0
#define SCOPE_LOCAL 1

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
#define TAC_FIELD_READ 28 /* a = b.field */
#define TAC_FIELD_WRITE 29 /* b.field = a */

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

/* 字段元数据结构 */
typedef struct FIELD_META {
    char *name;      /* 字段名 */
    int kind;           /* 字段类型：FIELD_INT/FIELD_CHAR/FIELD_PTR/FIELD_STRUCT/FIELD_ARRAY */
    int offset;         /* 相对结构体起始的偏移（字节） */
    void *etc;          /* 扩展信息：ARR_META* 或 STRUCT_META* */
    struct FIELD_META *next;  /* 链表（用于构建阶段） */
} FIELD_META;
/* 结构体元数据结构 */
typedef struct STRUCT_META {
    char *name;      /* 结构体名 */
    FIELD_META *fields; /* 字段列表 */
    int field_count;    /* 字段数量 */
    int size;           /* 结构体总大小（字节） */
    struct STRUCT_META *next;  /* 链表（结构体符号表） */
} STRUCT_META;
/* 数组元数据结构（扩展版） */
#define MAX_DIM 16
typedef struct ARR_META {
    int ndims;              /* 维度数量 */
    int dims[MAX_DIM];      /* 每个维度的大小 */
    int total_elems;        /* ✅ 总元素数量（改名） */
    int strides[MAX_DIM];   /* ✅ 新增：每个维度的步长 */
    int elem_size;          /* 元素大小（字节） */
    int elem_type;          /* 元素类型 */
    void *elem_meta;        /* 元素元数据（用于嵌套结构） */
} ARR_META;
/* 字段访问链节点 */
typedef struct FIELD_ACCESS {
    int type;               /* 访问类型：0=字段，1=数组索引 */
    char *name;          /* 字段名（type=0） */
    EXP *index;             /* 数组索引表达式（type=1） */
    struct FIELD_ACCESS *next;
} FIELD_ACCESS;
/* 字段访问信息（用于代码生成） */
typedef struct {
    int offset;      /* 字段在结构体中的偏移量 */
    int size;        /* 字段大小（1=char, 4=int/指针） */
    int kind;        /* 字段类型（FIELD_INT, FIELD_CHAR等） */
} FIELD_INFO;

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
extern STRUCT_META *struct_tab;
extern TAC *tac_first, *tac_last;
extern int decl_dtype;
extern STRUCT_META *decl_struct;

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
/* 结构体定义 */
STRUCT_META *finalize_struct(char *name, FIELD_META *fields);
FIELD_META *create_field(char *name, int *dims, int ndims);
FIELD_META *create_field_ptr(char *name);
FIELD_META *append_fields(FIELD_META *list1, FIELD_META *list2);
FIELD_META *append_field_name(FIELD_META *list, char *name, int *dims, int ndims);
FIELD_META *append_field_name_ptr(FIELD_META *list, char *name);
void set_field_type(FIELD_META *fields, int type);
void set_field_struct_type(FIELD_META *fields, char *struct_name);
/* 结构体查找 */
STRUCT_META *lookup_struct(char *name);
FIELD_META *find_field(STRUCT_META *meta, char *name);
/* 结构体变量声明 */
TAC *declare_struct_var(char *name, STRUCT_META *meta);
TAC *declare_struct_array(char *name, STRUCT_META *meta, int *dims, int ndims);
/* 字段访问链构建 */
FIELD_ACCESS *create_field_access(char *var, char *field);
FIELD_ACCESS *create_field_access_array(char *var, EXP *indices, char *field);
FIELD_ACCESS *append_field_access(FIELD_ACCESS *chain, char *field);
FIELD_ACCESS *append_array_access(FIELD_ACCESS *chain, EXP *indices);
/* 字段读写 */
EXP *do_field_read(FIELD_ACCESS *chain);
TAC *do_field_write(FIELD_ACCESS *chain, EXP *val);
EXP *do_field_addr(FIELD_ACCESS *chain);  /* ✅ 新增：字段取址 */
/* ========== ✅ 新增：辅助函数 ========== */
/* 判断符号类型 */
int is_array(SYM *s);
int is_struct(SYM *s);
int is_struct_array(SYM *s);
/* 计算结构体/数组大小 */
int get_type_size(SYM *s);
int get_struct_size(STRUCT_META *meta);
int get_array_size(ARR_META *arr);
/* 反转链表（用于字段访问链和索引列表） */
FIELD_ACCESS *reverse_field_access(FIELD_ACCESS *chain);
EXP *reverse_exp_list(EXP *list);
