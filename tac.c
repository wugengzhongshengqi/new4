/*
 * TAC 中间代码生成模块
 * 负责符号表管理、三地址码(TAC)的构造与串接、
 * 以及表达式/语句/函数等语法动作的中间表示。
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "tac.h"

/* 全局状态
 * scope: 当前作用域标记，0=全局，1=局部（函数体内）
 * next_tmp: 下一个临时变量编号（mk_tmp 生成 tN）
 * next_label: 下一个标签编号（mk_lstr/mk_label 生成 LN）
 * sym_tab_global: 全局符号表头指针（文件级）
 * sym_tab_local: 局部符号表头指针（当前函数级）
 * tac_first: 反转完成后的 TAC 正向链表首结点（用于遍历生成对象代码）
 * tac_last: 构建阶段得到的尾结点（通过 prev 串接，最终由 tac_complete 反转）
 * decl_dtype: 最近一次声明语句使用的基本数据类型（DT_INT/DT_CHAR），影响变量/指针声明
 */
int scope, next_tmp, next_label;
SYM *sym_tab_global, *sym_tab_local;
TAC *tac_first, *tac_last;
int decl_dtype;
static SYM *current_switch_end = NULL;
static LOOP_CTX *loop_stack = NULL;
static BREAK_CTX *break_stack = NULL;

typedef struct loop_parse_ctx {
    SYM *begin_label;
    SYM *continue_label;
    SYM *end_label;
    struct loop_parse_ctx *prev;
} LOOP_PARSE_CTX;
static LOOP_PARSE_CTX *loop_parse_stack = NULL;

static LOOP_PARSE_CTX *get_current_loop_labels(void)
{
    return loop_parse_stack;
}

/* 初始化 TAC 构造所需的全局变量 */
void tac_init()
{
    scope=0;
    sym_tab_global=NULL;
    sym_tab_local=NULL;
    next_tmp=0;
    next_label=1;
    decl_dtype=DT_INT;
}

/* 将以双向链表形式构建的 TAC 反转为正向链表，得到首指针 */
void tac_complete()
{
    /* 反转以 prev 连接的双向链表：
     * 从构建阶段尾结点 tac_last 起，逐个将前驱的 next 指向当前，
     * 最后得到正向可遍历的首结点 tac_first 用于后续目标代码生成。
     */
    TAC *cur=NULL; 		/* 当前正向链的尾（累积为首） */
    TAC *prev=tac_last; 	/* 反向遍历的指针（原 prev 链） */

	while(prev !=NULL)
	{
		prev->next=cur;
		cur=prev;
		prev=prev->prev;
	}

	tac_first = cur;
}

/* 在给定符号表中查找名称为 name 的符号，未找到返回 NULL */
SYM *lookup_sym(SYM *symtab, char *name)
{
    SYM *t=symtab;

	while(t !=NULL)
	{
		if(strcmp(t->name, name)==0) break; 
		else t=t->next;
	}
	
	return t; /* NULL if not found */
}

/* 将符号插入到符号表表头 */
void insert_sym(SYM **symtab, SYM *sym)
{
    /* 采用头插法维持简单链表结构 */
    sym->next=*symtab; /* 插入到表头 */
    *symtab=sym;
}

/* 创建一个空符号节点 */
SYM *mk_sym(void)
{
    SYM *t;
    t=(SYM *)malloc(sizeof(SYM));
    return t;
}

/* 声明变量并插入到当前作用域的符号表中 */
SYM *mk_var(char *name)
{
    SYM *sym=NULL;

    /* 1) 在当前作用域查重 */
    if(scope)  
        sym=lookup_sym(sym_tab_local,name);
    else
        sym=lookup_sym(sym_tab_global,name);

    /* 2) 若已声明则报错 */
    if(sym!=NULL)
    {
        error("variable already declared");
        return NULL;
    }

    /* 3) 创建符号结点并设置类型/数据类型/偏移（未分配） */
    sym=mk_sym();
    sym->type=SYM_VAR;
    sym->name=name;
    sym->offset=-1; /* Unset address */
    sym->dtype=decl_dtype;

    /* 4) 插入到对应作用域的符号表 */
    if(scope)  
        insert_sym(&sym_tab_local,sym);
    else
        insert_sym(&sym_tab_global,sym);

	return sym;
}

/* 将两段 TAC 按构建时的 prev 指针进行链接，返回尾段 */
TAC *join_tac(TAC *c1, TAC *c2)
{
    TAC *t;

    if(c1==NULL) return c2;
    if(c2==NULL) return c1;

    /* 将 c1 接到 c2 的开头（prev 链表的起点），形成以 c2 作为尾部的拼接结果 */
    t=c2;
    while(t->prev !=NULL) 
        t=t->prev;

    t->prev=c1;
    return c2;
}

/* 声明普通变量，生成 TAC_VAR 指令 */
TAC *declare_var(char *name)
{
    /* 声明变量并生成一条 TAC_VAR 指令，变量地址在后续目标生成时分配 */
    return mk_tac(TAC_VAR,mk_var(name),NULL,NULL);
}

/* 构造一个 TAC 结点 */
TAC *mk_tac(int op, SYM *a, SYM *b, SYM *c)
{
    TAC *t=(TAC *)malloc(sizeof(TAC));

    t->next=NULL; /* Set these for safety */
    t->prev=NULL;
    t->op=op;
    t->a=a;
    t->b=b;
    t->c=c;

    return t;
}  

/* 构造一个标签符号 */
SYM *mk_label(char *name)
{
    SYM *t=mk_sym();

    t->type=SYM_LABEL;
    t->name=strdup(name);

    return t;
}  

/* 组合函数的标签、BEGIN、ENDFUNC 与参数/函数体代码 */
TAC *do_func(SYM *func, TAC *args, TAC *code)
{
    TAC *tlist; /* The backpatch list */

    TAC *tlab; /* Label at start of function */
    TAC *tbegin; /* BEGINFUNC marker */
    TAC *tend; /* ENDFUNC marker */

    tlab=mk_tac(TAC_LABEL, mk_label(func->name), NULL, NULL);
    tbegin=mk_tac(TAC_BEGINFUNC, NULL, NULL, NULL);
    tend=mk_tac(TAC_ENDFUNC,   NULL, NULL, NULL);

    /* 组织函数的入口标签、BEGIN、参数与主体、结束标记的串接顺序：
     * label -> begin -> (args + code) -> end
     */
    tbegin->prev=tlab;             /* begin 前接入口标签 */
    code=join_tac(args, code);     /* 参数声明拼接到函数体前面 */
    tend->prev=join_tac(tbegin, code); /* 结束标记接到 begin+代码 的末尾 */

    return tend;
}

/* 生成一个临时变量符号 tN，用于保存中间结果 */
SYM *mk_tmp(void)
{
    SYM *sym;
    char *name;

    name=malloc(12);
    sprintf(name, "t%d", next_tmp++); /* 生成临时名 tN 并推进编号 */
    return mk_var(name);
}

/* 声明形式参数，生成 TAC_FORMAL 指令 */
TAC *declare_para(char *name)
{
    /* 声明形式参数（视为局部变量的一种），由后续目标生成分配偏移 */
    return mk_tac(TAC_FORMAL,mk_var(name),NULL,NULL);
}

/* 声明函数名，插入到全局符号表中 */
SYM *declare_func(char *name)
{
    SYM *sym=NULL;

    sym=lookup_sym(sym_tab_global,name);

    /* 处理重复声明与命名冲突：若已存在同名符号 */
    if(sym!=NULL)
    {
        if(sym->type==SYM_FUNC)
        {
            error("func already declared");
            return NULL;
        }

        if(sym->type !=SYM_UNDEF)
        {
            error("func name already used");
            return NULL;
        }

        return sym;
    }
	
	
    sym=mk_sym();
    sym->type=SYM_FUNC;
    sym->name=name;
    sym->address=NULL;

    sym->dtype=decl_dtype;
    insert_sym(&sym_tab_global,sym);
    return sym;
}

/* 赋值语句：var = exp */
TAC *do_assign(SYM *var, EXP *exp)
{
    TAC *code;

    if(var->type !=SYM_VAR) error("assignment to non-variable");

    /* 先执行表达式 TAC，再将结果复制到目标变量 */
    code=mk_tac(TAC_COPY, var, exp->ret, NULL);
    code->prev=exp->tac;

    return code;
}

/* 输入语句：读取到变量 */
TAC *do_input(SYM *var)
{
    TAC *code;

    if(var->type !=SYM_VAR) error("input to non-variable");

    /* 输入到变量（字符或整型由 dtype 决定） */
    code=mk_tac(TAC_INPUT, var, NULL, NULL);

    return code;
}

/* 输出语句：输出变量或文本/常量 */
TAC *do_output(SYM *s)
{
    TAC *code;

    /* 输出变量或文本/常量 */
    code=mk_tac(TAC_OUTPUT, s, NULL, NULL);

    return code;
}

/* 二元表达式：exp1 op exp2，结果写入新临时 */
EXP *do_bin( int binop, EXP *exp1, EXP *exp2)
{
    TAC *temp; /* TAC code for temp symbol */
    TAC *ret; /* TAC code for result */

	/*
	if((exp1->ret->type==SYM_INT) && (exp2->ret->type==SYM_INT))
	{
		int newval;

		switch(binop)
		{
			case TAC_ADD:
			newval=exp1->ret->value + exp2->ret->value;
			break;

			case TAC_SUB:
			newval=exp1->ret->value - exp2->ret->value;
			break;

			case TAC_MUL:
			newval=exp1->ret->value * exp2->ret->value;
			break;

			case TAC_DIV:
			newval=exp1->ret->value / exp2->ret->value;
			break;
		}

		exp1->ret=mk_const(newval);

		return exp1;
	}
	*/

    /* 1) 为结果分配临时变量作为左值 */
    temp=mk_tac(TAC_VAR, mk_tmp(), NULL, NULL);
    /* 2) 串接两个操作数的生成代码 */
    temp->prev=join_tac(exp1->tac, exp2->tac);
    /* 3) 生成二元操作 TAC：temp = op(exp1, exp2) */
    ret=mk_tac(binop, temp->a, exp1->ret, exp2->ret);
    ret->prev=temp;

    /* 4) 将返回值替换为新临时，并返回合成后的表达式 */
    exp1->ret=temp->a;
    exp1->tac=ret;

    return exp1;  
}   

/* 比较表达式：生成关系运算 TAC，结果为 0/1 */
EXP *do_cmp( int binop, EXP *exp1, EXP *exp2)
{
    TAC *temp; /* TAC code for temp symbol */
    TAC *ret; /* TAC code for result */

    /* 1) 为比较结果分配临时，按 0/1 表示布尔 */
    temp=mk_tac(TAC_VAR, mk_tmp(), NULL, NULL);
    /* 2) 串接两个操作数生成代码 */
    temp->prev=join_tac(exp1->tac, exp2->tac);
    /* 3) 生成比较 TAC：temp = (exp1 ?op? exp2) */
    ret=mk_tac(binop, temp->a, exp1->ret, exp2->ret);
    ret->prev=temp;

	exp1->ret=temp->a;
	exp1->tac=ret;

	return exp1;  
}   

/* 一元表达式：如负号，结果写入新临时 */
EXP *do_un( int unop, EXP *exp) 
{
    TAC *temp; /* TAC code for temp symbol */
    TAC *ret; /* TAC code for result */

    /* 1) 为结果分配临时 */
    temp=mk_tac(TAC_VAR, mk_tmp(), NULL, NULL);
    /* 2) 执行子表达式代码 */
    temp->prev=exp->tac;
    /* 3) 生成一元操作 TAC：temp = unop(exp) */
    ret=mk_tac(unop, temp->a, exp->ret, NULL);
    ret->prev=temp;

	exp->ret=temp->a;
	exp->tac=ret;

	return exp;   
}

/* 无返回值的函数调用：依次生成 ACTUAL，最后 CALL */
TAC *do_call(char *name, EXP *arglist)
{
    EXP  *alt; /* For counting args */
    TAC *code; /* Resulting code */
    TAC *temp; /* Temporary for building code */

	code=NULL;
    /* 1) 先串接所有实参表达式代码（注意链表 next 指向前一个） */
    for(alt=arglist; alt !=NULL; alt=alt->next) code=join_tac(code, alt->tac);

    while(arglist !=NULL) /* 2) 依次生成 ACTUAL 指令，按调用约定入栈 */
	{
		temp=mk_tac(TAC_ACTUAL, arglist->ret, NULL, NULL);
		temp->prev=code;
		code=temp;

		alt=arglist->next;
		arglist=alt;
	};

    /* 3) 生成 CALL，无返回值情形 a==NULL */
    temp=mk_tac(TAC_CALL, NULL, (SYM *)strdup(name), NULL);
	temp->prev=code;
	code=temp;

	return code;
}

/* 有返回值的函数调用：先分配临时保存返回值，再生成 CALL */
EXP *do_call_ret(char *name, EXP *arglist)
{
    EXP  *alt; /* For counting args */
    SYM *ret; /* Where function result will go */
    TAC *code; /* Resulting code */
    TAC *temp; /* Temporary for building code */

    /* 1) 预分配临时保存返回值，并声明该临时变量 */
    ret=mk_tmp(); /* For the result */
    code=mk_tac(TAC_VAR, ret, NULL, NULL);

    /* 2) 串接所有实参表达式代码 */
    for(alt=arglist; alt !=NULL; alt=alt->next) code=join_tac(code, alt->tac);

    while(arglist !=NULL) /* 3) 生成 ACTUAL 指令按序入栈 */
	{
		temp=mk_tac(TAC_ACTUAL, arglist->ret, NULL, NULL);
		temp->prev=code;
		code=temp;

		alt=arglist->next;
		arglist=alt;
	};

    /* 4) 生成带返回值的 CALL，将结果存入 ret */
    temp=mk_tac(TAC_CALL, ret, (SYM *)strdup(name), NULL);
	temp->prev=code;
	code=temp;

	return mk_exp(NULL, ret, code);
}

/* 将标签序号转为字符串 L{i} */
char *mk_lstr(int i)
{
    char lstr[10]="L";
    sprintf(lstr,"L%d",i);
    return(strdup(lstr)); 	
}

/* if (exp) stmt ：exp 为 0 则跳到 label，执行 stmt 后接上 label */
TAC *do_if(EXP *exp, TAC *stmt)
{
    TAC *label=mk_tac(TAC_LABEL, mk_label(mk_lstr(next_label++)), NULL, NULL);
    TAC *code=mk_tac(TAC_IFZ, label->a, exp->ret, NULL);

    /* ifz ret goto Lx; stmt; Lx: */
    code->prev=exp->tac;   /* 先执行条件表达式 */
    code=join_tac(code, stmt); /* 条件为真则执行语句 */
    label->prev=code;      /* 最后贴上跳转目标标签 */

    return label;
}

/* if-else：根据 exp 在两个块之间跳转，组织两个 label */
TAC *do_test(EXP *exp, TAC *stmt1, TAC *stmt2)
{
    TAC *label1=mk_tac(TAC_LABEL, mk_label(mk_lstr(next_label++)), NULL, NULL);
    TAC *label2=mk_tac(TAC_LABEL, mk_label(mk_lstr(next_label++)), NULL, NULL);
    TAC *code1=mk_tac(TAC_IFZ, label1->a, exp->ret, NULL);
    TAC *code2=mk_tac(TAC_GOTO, label2->a, NULL, NULL);

    /* ifz ret goto Lelse; stmt1; goto Lend; Lelse: stmt2; Lend: */
    code1->prev=exp->tac; /* 条件 */
    code1=join_tac(code1, stmt1); /* 真分支 */
    code2->prev=code1; /* 跳过假分支到结束 */
    label1->prev=code2; /* else 标签 */
    label1=join_tac(label1, stmt2); /* 假分支 */
    label2->prev=label1; /* 结束标签 */

    return label2;
}

/* 在当前作用域及全局查找变量名称并进行类型校验 */
SYM *get_var(char *name)
{
    SYM *sym=NULL; /* Pointer to looked up symbol */

	if(scope) sym=lookup_sym(sym_tab_local,name);

	if(sym==NULL) sym=lookup_sym(sym_tab_global,name);

    if(sym==NULL)
    {
        error("name not declared as local/global variable");
        return NULL;
    }

	if(sym->type!=SYM_VAR)
	{
		error("not a variable");
		return NULL;
	}

	return sym;
} 

/* 构造一个表达式节点，包含返回值符号及其生成的 TAC */
EXP *mk_exp(EXP *next, SYM *ret, TAC *code)
{
    EXP *exp=(EXP *)malloc(sizeof(EXP));

	exp->next=next;
	exp->ret=ret;
	exp->tac=code;

	return exp;
}

/* 声明或复用字符串常量，分配唯一标签 */
SYM *mk_text(char *text)
{
    SYM *sym=NULL; /* Pointer to looked up symbol */

	sym=lookup_sym(sym_tab_global,text);

	/* text already used */
	if(sym!=NULL)
	{
		return sym;
	}

	/* text unseen before */
    sym=mk_sym();
    sym->type=SYM_TEXT;
    sym->name=text;
    sym->label=next_label++;

	insert_sym(&sym_tab_global,sym);
	return sym;
}

/* 声明或复用整型常量，按值缓存 */
SYM *mk_const(int n)
{
    SYM *sym=NULL;

	char name[10];
	sprintf(name, "%d", n);

    sym=lookup_sym(sym_tab_global, name); /* 以文本值缓存常量，避免重复符号 */
    if(sym!=NULL)
    {
        return sym;
    }

	sym=mk_sym();
	sym->type=SYM_INT;
	sym->value=n;
	sym->name=strdup(name);
	insert_sym(&sym_tab_global,sym);

	return sym;
}     

/* 将符号转为输出字符串：变量/函数返回名称，文本返回标签，整型返回数值 */
char *to_str(SYM *s, char *str) 
{
    if(s==NULL)	return "NULL";

	switch(s->type)
	{
		case SYM_FUNC:
		case SYM_VAR:
		/* Just return the name */
		return s->name;

		case SYM_TEXT:
		/* Put the address of the text */
		sprintf(str, "L%d", s->label);
		return str;

		case SYM_INT:
		/* Convert the number to string */
		sprintf(str, "%d", s->value);
		return str;

        case SYM_LABEL:
        /* Put the label */
        sprintf(str, "L%d", s->label);
        return str;

		default:
		/* Unknown arg type */
		error("unknown TAC arg type");
		return "?";
	}
} 

/* 文件格式化输出（封装 vfprintf） */
void out_str(FILE *f, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(f, format, args);
    va_end(args);
}

/* 调试输出：符号指针与名称 */
void out_sym(FILE *f, SYM *s)
{
	out_str(f, "%p\t%s", s, s->name);
}

/* 将一条 TAC 指令格式化为可读文本（用于注释或调试输出） */
void out_tac(FILE *f, TAC *i)
{
    char sa[12]; /* For text of TAC args */
    char sb[12];
    char sc[12];

	switch(i->op)
	{
		case TAC_UNDEF:
		fprintf(f, "undef");
		break;

		case TAC_ADD:
		fprintf(f, "%s = %s + %s", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_SUB:
		fprintf(f, "%s = %s - %s", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_MUL:
		fprintf(f, "%s = %s * %s", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_DIV:
		fprintf(f, "%s = %s / %s", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_EQ:
		fprintf(f, "%s = (%s == %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_NE:
		fprintf(f, "%s = (%s != %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_LT:
		fprintf(f, "%s = (%s < %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_LE:
		fprintf(f, "%s = (%s <= %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_GT:
		fprintf(f, "%s = (%s > %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_GE:
		fprintf(f, "%s = (%s >= %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_NEG:
		fprintf(f, "%s = - %s", to_str(i->a, sa), to_str(i->b, sb));
		break;

		case TAC_COPY:
		fprintf(f, "%s = %s", to_str(i->a, sa), to_str(i->b, sb));
		break;

		case TAC_GOTO:
		fprintf(f, "goto %s", i->a->name);
		break;

		case TAC_IFZ:
		fprintf(f, "ifz %s goto %s", to_str(i->b, sb), i->a->name);
		break;

		case TAC_ACTUAL:
		fprintf(f, "actual %s", to_str(i->a, sa));
		break;

		case TAC_FORMAL:
		fprintf(f, "formal %s", to_str(i->a, sa));
		break;

		case TAC_CALL:
		if(i->a==NULL) fprintf(f, "call %s", (char *)i->b);
		else fprintf(f, "%s = call %s", to_str(i->a, sa), (char *)i->b);
		break;

		case TAC_INPUT:
		fprintf(f, "input %s", to_str(i->a, sa));
		break;

        case TAC_OUTPUT:
        fprintf(f, "output %s", to_str(i->a, sa));
        break;

        case TAC_RETURN:
        fprintf(f, "return %s", to_str(i->a, sa));
        break;

        case TAC_LABEL:
        fprintf(f, "label %s", i->a->name);
        break;

        case TAC_VAR:
        if (i->a->etc != NULL) {
            /* ✅ 首先检查是否真的是数组类型 */
            if (i->a->dtype == DT_ARRAY) {
                ARR_META *meta = (ARR_META *)i->a->etc;
                
                /* ✅ 检查元数据的有效性 */
                if (!meta) {
                    fprintf(f, "var %s /* 错误: meta is NULL */", to_str(i->a, sa));
                    break;
                }
                
                if (!meta->dims) {
                    fprintf(f, "var %s /* 错误: dims is NULL */", to_str(i->a, sa));
                    break;
                }
                
                if (meta->ndims <= 0 || meta->ndims > 10) {
                    fprintf(f, "var %s /* 错误: ndims=%d 无效 */", 
                            to_str(i->a, sa), meta->ndims);
                    break;
                }
                
                /* ✅ 现在可以安全打印了 */
                fprintf(f, "var %s[", to_str(i->a, sa));
                for (int j = 0; j < meta->ndims; j++) {
                    fprintf(f, "%d%s", meta->dims[j], 
                            (j < meta->ndims - 1) ? "][" : "]");
                }
                
            } else if (i->a->dtype == DT_STRUCT) {
                /* ✅ 结构体变量 */
                STRUCT_META *smeta = (STRUCT_META *)i->a->etc;
                if (smeta && smeta->name) {
                    fprintf(f, "var %s /* struct %s */", to_str(i->a, sa), smeta->name);
                } else {
                    fprintf(f, "var %s /* struct */", to_str(i->a, sa));
                }
                
            } else {
                /* ✅ 其他有 etc 但非数组/结构体的情况 */
                fprintf(f, "var %s /* etc 非空但类型未知 */", to_str(i->a, sa));
            }
        } else {
            /* ✅ 普通变量（无元数据） */
            fprintf(f, "var %s", to_str(i->a, sa));
        }
        break;


        case TAC_BEGINFUNC:
        fprintf(f, "begin");
        break;

        case TAC_ENDFUNC:
        fprintf(f, "end");
        break;
        case TAC_ADDR:
        fprintf(f, "%s = &%s", to_str(i->a, sa), to_str(i->b, sb));
        break;
        case TAC_DEREF_R:
        fprintf(f, "%s = *%s", to_str(i->a, sa), to_str(i->b, sb));
        break;
        case TAC_DEREF_W:
        fprintf(f, "*%s = %s", to_str(i->a, sa), to_str(i->b, sb));
        break;
        case TAC_FIELD_READ:
            fprintf(f, "%s = %s.field_%d", 
                    to_str(i->a, sa), 
                    to_str(i->b, sb), 
                    ((FIELD_INFO *)i->c)->offset);
            break;
        case TAC_FIELD_WRITE:
            fprintf(f, "%s.field_%d = %s", 
                    to_str(i->a, sa), 
                    ((FIELD_INFO *)i->c)->offset,
                    to_str(i->b, sb));
            break;

		default:
		error("unknown TAC opcode");
		break;
	}
}
/* 声明指针变量：根据当前声明基本类型推断指针类型 */
TAC *declare_ptr_var(char *name)
{
    SYM *sym=NULL;

    if(scope)
        sym=lookup_sym(sym_tab_local,name);
    else
        sym=lookup_sym(sym_tab_global,name);

    if(sym!=NULL)
    {
        error("variable already declared");
        return NULL;
    }

    sym=mk_sym();
    sym->type=SYM_VAR;
    sym->name=name;
    sym->offset=-1;
    sym->dtype=DT_PTR; /* 根据当前声明基本类型决定指针的目标类型 */

    if(scope)
        insert_sym(&sym_tab_local,sym);
    else
        insert_sym(&sym_tab_global,sym);

    return mk_tac(TAC_VAR,sym,NULL,NULL);
}

/* 声明数组变量：分配元数据并计算步幅与总大小 */
TAC *declare_array_var(char *name, int *dims, int ndims)
{
    SYM *sym=NULL;
    ARR_META *meta;
    int i;

    /* 1) 检查重复声明 */
    if(scope)
        sym=lookup_sym(sym_tab_local, name);
    else
        sym=lookup_sym(sym_tab_global, name);

    if(sym!=NULL)
    {
        error("variable already declared");
        return NULL;
    }

    /* 2) 创建符号并设置基本信息 */
    sym=mk_sym();
    sym->type=SYM_VAR;
    sym->name=name;
    sym->offset=-1;
    sym->dtype=DT_ARRAY;  // 元素基本类型（DT_INT/DT_CHAR）

    /* 3) 分配并填充数组元数据 */
    meta=(ARR_META *)malloc(sizeof(ARR_META));
    meta->ndims=ndims;
    
    if (decl_dtype == DT_INT) {
        meta->elem_size = 4;
        meta->elem_type = ELEM_INT;
    } else if (decl_dtype == DT_CHAR) {
        meta->elem_size = 4;
        meta->elem_type = ELEM_CHAR;
    } else {
        meta->elem_size = 4;  // 默认
        meta->elem_type = ELEM_INT;
    }
    
    /* 4) 计算步幅与总元素数 */
    meta->total_elems=1;
    for(i=0; i<ndims; i++)
    {
        meta->dims[i]=dims[i];
        meta->total_elems *= dims[i];
    }

    /* 步幅计算：stride[i] = product(dims[i+1..ndims-1]) */
    meta->strides[ndims-1]=1;
    for(i=ndims-2; i>=0; i--)
    {
        meta->strides[i]=meta->strides[i+1] * dims[i+1];
    }

    /* 5) 将元数据附加到符号的 etc 字段 */
    sym->etc=(void *)meta;

    /* 6) 插入符号表 */
    if(scope)
        insert_sym(&sym_tab_local, sym);
    else
        insert_sym(&sym_tab_global, sym);

    return mk_tac(TAC_VAR, sym, NULL, NULL);
}

/* 反转索引表达式链表（因为 Yacc 中逆向构建） */
static EXP *reverse_index_list(EXP *list)
{
    EXP *prev=NULL;
    EXP *curr=list;
    EXP *next;

    while(curr!=NULL)
    {
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }

    return prev;
}

/* 数组读取：arr[i][j]... 生成线性偏移并读取元素 */
EXP *do_array_read(SYM *arr, EXP *indices)
{
    ARR_META *meta;
    EXP *idx;
    TAC *offset_code=NULL;
    SYM *offset_sym=NULL;
    SYM *addr_sym;
    SYM *result_sym;
    TAC *temp, *ret;
    int count=0;

    /* 1) 检查是否为数组 */
    if(arr->etc==NULL)
    {
        error("not an array variable");
        return mk_exp(NULL, NULL, NULL);
    }

    meta=(ARR_META *)arr->etc;

    /* 2) 反转索引列表 */
    indices=reverse_index_list(indices);

    /* 3) 检查维度数量匹配 */
    for(idx=indices; idx!=NULL; idx=idx->next) count++;
    if(count!=meta->ndims)
    {
        error("array dimension mismatch");
        return mk_exp(NULL, NULL, NULL);
    }

    /* 4) 计算线性偏移：offset = idx[0]*stride[0] + idx[1]*stride[1] + ... */
    idx=indices;
    for(int i=0; i<meta->ndims; i++, idx=idx->next)
    {
        SYM *stride_sym=mk_const(meta->strides[i]);
        SYM *term_sym=mk_tmp();
        
        /* term = idx[i] * stride[i] */
        temp=mk_tac(TAC_VAR, term_sym, NULL, NULL);
        temp->prev=offset_code;
        offset_code=temp;
        
        ret=mk_tac(TAC_MUL, term_sym, idx->ret, stride_sym);
        ret->prev=join_tac(idx->tac, offset_code);
        offset_code=ret;

        /* offset += term */
        if(offset_sym==NULL)
        {
            offset_sym=term_sym;
        }
        else
        {
            SYM *new_offset=mk_tmp();
            temp=mk_tac(TAC_VAR, new_offset, NULL, NULL);
            temp->prev=offset_code;
            offset_code=temp;
            
            ret=mk_tac(TAC_ADD, new_offset, offset_sym, term_sym);
            ret->prev=offset_code;
            offset_code=ret;
            offset_sym=new_offset;
        }
    }

    /* 5) offset *= elem_size */
    if(meta->elem_size > 1)
    {
        SYM *size_sym=mk_const(meta->elem_size);
        SYM *byte_offset=mk_tmp();
        
        temp=mk_tac(TAC_VAR, byte_offset, NULL, NULL);
        temp->prev=offset_code;
        offset_code=temp;
        
        ret=mk_tac(TAC_MUL, byte_offset, offset_sym, size_sym);
        ret->prev=offset_code;
        offset_code=ret;
        offset_sym=byte_offset;
    }

    /* 6) 计算元素地址：addr = &arr + offset */
    addr_sym=mk_tmp();
    addr_sym->dtype=arr->dtype;
    
    temp=mk_tac(TAC_VAR, addr_sym, NULL, NULL);
    temp->prev=offset_code;
    offset_code=temp;
    
    ret=mk_tac(TAC_ADDR, addr_sym, arr, NULL);
    ret->prev=offset_code;
    offset_code=ret;

    SYM *final_addr=mk_tmp();
    final_addr->dtype=addr_sym->dtype;
    temp=mk_tac(TAC_VAR, final_addr, NULL, NULL);
    temp->prev=offset_code;
    offset_code=temp;
    
    ret=mk_tac(TAC_ADD, final_addr, addr_sym, offset_sym);
    ret->prev=offset_code;
    offset_code=ret;

    /* 7) 读取元素：result = *final_addr */
    result_sym=mk_tmp();
    result_sym->dtype=(meta->elem_size==1) ? DT_CHAR : DT_INT;
    
    temp=mk_tac(TAC_VAR, result_sym, NULL, NULL);
    temp->prev=offset_code;
    offset_code=temp;
    
    ret=mk_tac(TAC_DEREF_R, result_sym, final_addr, NULL);
    ret->prev=offset_code;

    return mk_exp(NULL, result_sym, ret);
}

/* 数组写入：arr[i][j]... = val 生成线性偏移并写入元素 */
TAC *do_array_write(SYM *arr, EXP *indices, EXP *val)
{
    ARR_META *meta;
    EXP *idx;
    TAC *offset_code=NULL;
    SYM *offset_sym=NULL;
    SYM *addr_sym;
    TAC *temp, *ret;
    int count=0;

    /* 1) 检查是否为数组 */
    if(arr->etc==NULL)
    {
        error("not an array variable");
        return NULL;
    }

    meta=(ARR_META *)arr->etc;

    /* 2) 反转索引列表 */
    indices=reverse_index_list(indices);

    /* 3) 检查维度数量匹配 */
    for(idx=indices; idx!=NULL; idx=idx->next) count++;
    if(count!=meta->ndims)
    {
        error("array dimension mismatch");
        return NULL;
    }

    /* 4) 计算线性偏移（与读取相同） */
    idx=indices;
    for(int i=0; i<meta->ndims; i++, idx=idx->next)
    {
        SYM *stride_sym=mk_const(meta->strides[i]);
        SYM *term_sym=mk_tmp();
        
        temp=mk_tac(TAC_VAR, term_sym, NULL, NULL);
        temp->prev=offset_code;
        offset_code=temp;
        
        ret=mk_tac(TAC_MUL, term_sym, idx->ret, stride_sym);
        ret->prev=join_tac(idx->tac, offset_code);
        offset_code=ret;

        if(offset_sym==NULL)
        {
            offset_sym=term_sym;
        }
        else
        {
            SYM *new_offset=mk_tmp();
            temp=mk_tac(TAC_VAR, new_offset, NULL, NULL);
            temp->prev=offset_code;
            offset_code=temp;
            
            ret=mk_tac(TAC_ADD, new_offset, offset_sym, term_sym);
            ret->prev=offset_code;
            offset_code=ret;
            offset_sym=new_offset;
        }
    }

    /* 5) offset *= elem_size */
    if(meta->elem_size > 1)
    {
        SYM *size_sym=mk_const(meta->elem_size);
        SYM *byte_offset=mk_tmp();
        
        temp=mk_tac(TAC_VAR, byte_offset, NULL, NULL);
        temp->prev=offset_code;
        offset_code=temp;
        
        ret=mk_tac(TAC_MUL, byte_offset, offset_sym, size_sym);
        ret->prev=offset_code;
        offset_code=ret;
        offset_sym=byte_offset;
    }

    /* 6) 计算元素地址：addr = &arr + offset */
    addr_sym=mk_tmp();
    addr_sym->dtype=arr->dtype;
    
    temp=mk_tac(TAC_VAR, addr_sym, NULL, NULL);
    temp->prev=offset_code;
    offset_code=temp;
    
    ret=mk_tac(TAC_ADDR, addr_sym, arr, NULL);
    ret->prev=offset_code;
    offset_code=ret;

    SYM *final_addr=mk_tmp();
    final_addr->dtype=addr_sym->dtype;
    temp=mk_tac(TAC_VAR, final_addr, NULL, NULL);
    temp->prev=offset_code;
    offset_code=temp;
    
    ret=mk_tac(TAC_ADD, final_addr, addr_sym, offset_sym);
    ret->prev=offset_code;
    offset_code=ret;

    /* 7) 写入元素：*final_addr = val */
    TAC *write=mk_tac(TAC_DEREF_W, final_addr, val->ret, NULL);
    write->prev=join_tac(offset_code, val->tac);

    return write;
}


/* 取地址运算 &var ：生成临时指针并计算地址 */
EXP *do_addr(SYM *var)
{
    TAC *temp;
    TAC *ret;

    temp=mk_tac(TAC_VAR, mk_tmp(), NULL, NULL);
    temp->prev=NULL;
    /* 根据 var 的基本类型设置结果临时的指针类型 */
    temp->a->dtype=DT_PTR;
    ret=mk_tac(TAC_ADDR, temp->a, var, NULL);
    ret->prev=temp;

    return mk_exp(NULL, temp->a, ret);
}

/* 指针读 *ptr ：根据指针类型选择字节/字读，结果写入新临时 */
EXP *do_deref_read(EXP *ptr)
{
    TAC *temp;
    TAC *ret;

    temp=mk_tac(TAC_VAR, mk_tmp(), NULL, NULL);
    temp->prev=ptr->tac;
    /* 根据指针类型设置读取结果的基本类型（字节/整型） */
    temp->a->dtype=DT_PTR;
    ret=mk_tac(TAC_DEREF_R, temp->a, ptr->ret, NULL);
    ret->prev=temp;

    ptr->ret=temp->a;
    ptr->tac=ret;
    return ptr;
}

/* 指针写 *ptr = val ：根据指针基本类型选择字节/字写 */
TAC *do_deref_write(SYM *ptr, EXP *val)
{
    TAC *code=mk_tac(TAC_DEREF_W, ptr, val->ret, NULL);
    code->prev=val->tac;
    return code;
}

/* ========================================
 * 全局变量定义（结构体相关）
 * ======================================== */
STRUCT_META *struct_tab = NULL;      /* 全局结构体定义表 */
STRUCT_META *decl_struct = NULL;     /* 当前正在声明的结构体类型 */

/* ========================================
 * 结构体相关函数实现
 * ======================================== */

/**
 * 创建并注册结构体定义
 */
STRUCT_META *finalize_struct(char *name, FIELD_META *fields)
{
    STRUCT_META *meta = (STRUCT_META *)malloc(sizeof(STRUCT_META));
    if (!meta) {
        fprintf(stderr, "ERROR: malloc failed for STRUCT_META\n");
        exit(1);
    }
    
    meta->name = strdup(name);
    if (!meta->name) {
        fprintf(stderr, "ERROR: strdup failed for struct name '%s'\n", name);
        free(meta);
        exit(1);
    }
    
    meta->fields = fields;
    meta->field_count = 0;
    meta->size = 0;
    
    /* 计算字段数量和总大小，并设置每个字段的偏移量 */
    FIELD_META *f = fields;
    while (f) {
        meta->field_count++;
        f->offset = meta->size;  /* 当前字段的偏移量 */
        
        /* 计算字段大小 */
        int field_size = 0;
        switch (f->kind) {
            case FIELD_INT:
                field_size = 4;
                break;
            case FIELD_CHAR:
                field_size = 4;
                break;
            case FIELD_PTR:
                field_size = 4;
                break;
            case FIELD_STRUCT:
                if (f->etc) {
                    STRUCT_META *sm = (STRUCT_META *)f->etc;
                    field_size = sm->size;
                }
                break;
            case FIELD_ARRAY:
                if (f->etc) {
                    ARR_META *am = (ARR_META *)f->etc;
                    field_size = am->total_elems * am->elem_size;
                }
                break;
        }
        
        meta->size += field_size;
        f = f->next;
    }
    
    /* 添加到全局结构体符号表 */
    meta->next = struct_tab;
    struct_tab = meta;
    
    return meta;
}

/**
 * 创建字段（支持数组）
 */
FIELD_META *create_field(char *name, int *dims, int ndims)
{
    FIELD_META *field = (FIELD_META *)malloc(sizeof(FIELD_META));
    if (!field) {
        fprintf(stderr, "ERROR: malloc failed for FIELD_META\n");
        exit(1);
    }
    
    // ✅ 修复：为 name 分配内存
    field->name = strdup(name);
    if (!field->name) {
        fprintf(stderr, "ERROR: strdup failed for field name '%s'\n", name);
        free(field);
        exit(1);
    }

    field->kind = 0;  /* 待设置 */
    field->offset = 0;
    field->next = NULL;
    
    if (ndims > 0) {
        /* 这是数组字段 */
        field->kind = FIELD_ARRAY;
        ARR_META *arr = (ARR_META *)malloc(sizeof(ARR_META));
        arr->ndims = ndims;
        arr->total_elems = 1;
        
        for (int i = 0; i < ndims; i++) {
            arr->dims[i] = dims[i];
            arr->total_elems *= dims[i];
        }
        
        /* 计算 strides */
        arr->strides[ndims - 1] = 1;
        for (int i = ndims - 2; i >= 0; i--) {
            arr->strides[i] = arr->strides[i + 1] * dims[i + 1];
        }
        
        arr->elem_size = 4;  /* 默认 int，待更新 */
        arr->elem_type = ELEM_INT;
        arr->elem_meta = NULL;
        
        field->etc = arr;
    } else {
        field->etc = NULL;
    }
    
    return field;
}

/**
 * 创建指针字段
 */
FIELD_META *create_field_ptr(char *name)
{
    FIELD_META *field = (FIELD_META *)malloc(sizeof(FIELD_META));
    field->name = strdup(name);
    field->kind = FIELD_PTR;
    field->offset = 0;
    field->etc = NULL;
    field->next = NULL;
    return field;
}

/**
 * 合并两个字段列表
 */
FIELD_META *append_fields(FIELD_META *list1, FIELD_META *list2)
{
    if (!list1) return list2;
    if (!list2) return list1;
    
    FIELD_META *tail = list1;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = list2;
    return list1;
}

/**
 * 向列表追加字段（支持数组）
 */
FIELD_META *append_field_name(FIELD_META *list, char *name, int *dims, int ndims)
{
    FIELD_META *new_field = create_field(name, dims, ndims);
    return append_fields(list, new_field);
}

/**
 * 向列表追加指针字段
 */
FIELD_META *append_field_name_ptr(FIELD_META *list, char *name)
{
    FIELD_META *new_field = create_field_ptr(name);
    return append_fields(list, new_field);
}

/**
 * 设置字段类型（int/char）
 */
void set_field_type(FIELD_META *fields, int type)
{
    while (fields) {
        if (fields->kind == FIELD_ARRAY) {
            /* 更新数组元素类型 */
            ARR_META *arr = (ARR_META *)fields->etc;
            if (type == DT_INT) {
                arr->elem_type = ELEM_INT;
                arr->elem_size = 4;
            } else if (type == DT_CHAR) {
                arr->elem_type = ELEM_CHAR;
                arr->elem_size = 1;
            }
        } else if (fields->kind == 0) {
            /* 设置普通字段类型 */
            if (type == DT_INT) {
                fields->kind = FIELD_INT;
            } else if (type == DT_CHAR) {
                fields->kind = FIELD_CHAR;
            }
        }
        fields = fields->next;
    }
}

/**
 * 设置字段为结构体类型
 */
void set_field_struct_type(FIELD_META *fields, char *struct_name)
{
    STRUCT_META *meta = lookup_struct(struct_name);
    if (!meta) {
        error("未定义的结构体类型: %s", struct_name);
        return;
    }
    
    while (fields) {
        if (fields->kind == FIELD_ARRAY) {
            /* 结构体数组 */
            ARR_META *arr = (ARR_META *)fields->etc;
            arr->elem_type = ELEM_STRUCT;
            arr->elem_size = meta->size;
            arr->elem_meta = meta;
        } else if (fields->kind == 0) {
            /* 普通结构体字段 */
            fields->kind = FIELD_STRUCT;
            fields->etc = meta;
        }
        fields = fields->next;
    }
}

/**
 * 查找结构体定义
 */
STRUCT_META *lookup_struct(char *name)
{
    STRUCT_META *meta = struct_tab;
    while (meta) {
        if (strcmp(meta->name, name) == 0) {
            return meta;
        }
        meta = meta->next;
    }
    return NULL;
}

/**
 * 查找结构体字段
 */
FIELD_META *find_field(STRUCT_META *meta, char *name)
{
    FIELD_META *f = meta->fields;
    while (f) {
        if (strcmp(f->name, name) == 0) {
            return f;
        }
        f = f->next;
    }
    return NULL;
}

/**
 * 声明结构体变量
 */
TAC *declare_struct_var(char *name, STRUCT_META *meta)
{
    SYM *var = (SYM *)malloc(sizeof(SYM));
    var->type = SYM_VAR;
    var->scope = scope;
    var->dtype = DT_STRUCT;
    var->name = strdup(name);
    var->etc = meta;  /* 保存结构体元数据 */
    
    if (scope == SCOPE_GLOBAL) {
        var->offset = 0;
        var->next = sym_tab_global;
        sym_tab_global = var;
        return mk_tac(TAC_VAR, var, NULL, NULL);
    } else {
        var->offset = -(next_tmp++);
        var->next = sym_tab_local;
        sym_tab_local = var;
        return mk_tac(TAC_VAR, var, NULL, NULL);
    }
}

/**
 * 声明结构体数组
 */
TAC *declare_struct_array(char *name, STRUCT_META *meta, int *dims, int ndims)
{
    SYM *var = (SYM *)malloc(sizeof(SYM));
    var->type = SYM_VAR;
    var->scope = scope;
    var->dtype = DT_ARRAY;
    var->name = strdup(name);
    
    /* 创建数组元数据 */
    ARR_META *arr = (ARR_META *)malloc(sizeof(ARR_META));
    arr->ndims = ndims;
    arr->total_elems = 1;
    
    for (int i = 0; i < ndims; i++) {
        arr->dims[i] = dims[i];
        arr->total_elems *= dims[i];
    }
    
    /* 计算 strides */
    arr->strides[ndims - 1] = 1;
    for (int i = ndims - 2; i >= 0; i--) {
        arr->strides[i] = arr->strides[i + 1] * dims[i + 1];
    }
    
    arr->elem_type = ELEM_STRUCT;
    arr->elem_size = meta->size;
    arr->elem_meta = meta;
    
    var->etc = arr;
    
    if (scope == SCOPE_GLOBAL) {
        var->offset = 0;
        var->next = sym_tab_global;
        sym_tab_global = var;
    } else {
        var->offset = -(next_tmp++);
        var->next = sym_tab_local;
        sym_tab_local = var;
    }
    
    return mk_tac(TAC_VAR, var, NULL, NULL);
}

/* ========================================
 * 字段访问相关函数
 * ======================================== */

/**
 * 创建字段访问链：var.field
 */
FIELD_ACCESS *create_field_access(char *var, char *field)
{
    FIELD_ACCESS *chain = (FIELD_ACCESS *)malloc(sizeof(FIELD_ACCESS));
    chain->name = strdup(var);
    chain->type = 0;  /* 变量名 */
    chain->index = NULL;
    chain->next = NULL;
    
    FIELD_ACCESS *access = (FIELD_ACCESS *)malloc(sizeof(FIELD_ACCESS));
    access->name = strdup(field);
    access->type = 0;  /* 字段访问 */
    access->index = NULL;
    access->next = NULL;
    
    chain->next = access;
    return chain;
}

/**
 * 创建字段访问链：var[idx].field
 */
FIELD_ACCESS *create_field_access_array(char *var, EXP *indices, char *field)
{
    FIELD_ACCESS *chain = (FIELD_ACCESS *)malloc(sizeof(FIELD_ACCESS));
    chain->name = strdup(var);
    chain->type = 0;
    chain->index = NULL;
    chain->next = NULL;
    
    FIELD_ACCESS *arr_access = (FIELD_ACCESS *)malloc(sizeof(FIELD_ACCESS));
    arr_access->name = NULL;
    arr_access->type = 1;  /* 数组索引 */
    arr_access->index = indices;
    arr_access->next = NULL;
    
    FIELD_ACCESS *field_access = (FIELD_ACCESS *)malloc(sizeof(FIELD_ACCESS));
    field_access->name = strdup(field);
    field_access->type = 0;
    field_access->index = NULL;
    field_access->next = NULL;
    
    chain->next = arr_access;
    arr_access->next = field_access;
    
    return chain;
}

/**
 * 追加字段访问：chain.field
 */
FIELD_ACCESS *append_field_access(FIELD_ACCESS *chain, char *field)
{
    FIELD_ACCESS *access = (FIELD_ACCESS *)malloc(sizeof(FIELD_ACCESS));
    access->name = strdup(field);
    access->type = 0;
    access->index = NULL;
    access->next = NULL;
    
    FIELD_ACCESS *tail = chain;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = access;
    
    return chain;
}

/**
 * 追加数组访问：chain[idx]
 */
FIELD_ACCESS *append_array_access(FIELD_ACCESS *chain, EXP *indices)
{
    FIELD_ACCESS *access = (FIELD_ACCESS *)malloc(sizeof(FIELD_ACCESS));
    access->name = NULL;
    access->type = 1;
    access->index = indices;
    access->next = NULL;
    
    FIELD_ACCESS *tail = chain;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = access;
    
    return chain;
}

/**
 * 读取字段值：支持多层嵌套访问
 * 例如：student.score、arr[i].name、nested.inner.value 等
 */
EXP *do_field_read(FIELD_ACCESS *chain)
{
    if (!chain) {
        error("empty field access chain");
        return mk_exp(NULL, NULL, NULL);
    }
    
    /* 1. 查找基础变量 */
    SYM *base_var = get_var(chain->name);
    if (!base_var) {
        error("变量 '%s' 未定义", chain->name);
        return mk_exp(NULL, NULL, NULL);
    }
    
    TAC *code = NULL;
    SYM *current_addr = NULL;
    STRUCT_META *current_struct = NULL;
    void *current_meta = base_var->etc;  /* ARR_META 或 STRUCT_META */
    int current_dtype = base_var->dtype;

    if (current_dtype == DT_STRUCT) {
        if (!current_meta) {
            error("结构体变量 '%s' 的元数据为空", chain->name);
            return mk_exp(NULL, NULL, NULL);
        }
        current_struct = (STRUCT_META *)current_meta;
    }
    
    /* 2. 获取基础变量地址 */
    current_addr = mk_tmp();
    current_addr->dtype = DT_PTR;
    
    TAC *temp = mk_tac(TAC_VAR, current_addr, NULL, NULL);
    code = temp;
    
    TAC *addr = mk_tac(TAC_ADDR, current_addr, base_var, NULL);
    addr->prev = code;
    code = addr;
    
    /* 3. 遍历访问链 */
    FIELD_ACCESS *access = chain->next;
    
    while (access) {
        if (access->type == 1) {
            /* ========== 数组索引访问 ========== */
            if (current_dtype != DT_ARRAY && current_dtype != DT_STRUCT) {
                error("对非数组类型进行索引访问");
                return mk_exp(NULL, NULL, NULL);
            }
            
            ARR_META *arr_meta = NULL;
            
            if (current_dtype == DT_ARRAY) {
                arr_meta = (ARR_META *)current_meta;
            } else if (current_dtype == DT_STRUCT) {
                /* 上一步应该已经处理为数组字段 */
                error("结构体字段访问后不应直接索引");
                return mk_exp(NULL, NULL, NULL);
            }
            
            if (!arr_meta) {
                error("数组元数据为空");
                return mk_exp(NULL, NULL, NULL);
            }
            
            /* 反转索引列表 */
            EXP *indices = reverse_exp_list(access->index);
            
            /* 检查维度数量 */
            int count = 0;
            for (EXP *idx = indices; idx; idx = idx->next) count++;
            
            if (count != arr_meta->ndims) {
                error("数组维度不匹配：需要 %d 维，提供了 %d 维", 
                      arr_meta->ndims, count);
                return mk_exp(NULL, NULL, NULL);
            }
            
            /* 计算线性偏移 */
            SYM *offset_sym = NULL;
            EXP *idx = indices;
            
            for (int i = 0; i < arr_meta->ndims; i++, idx = idx->next) {
                /* 串接索引表达式代码 */
                code = join_tac(code, idx->tac);
                
                /* term = idx[i] * stride[i] */
                SYM *stride_sym = mk_const(arr_meta->strides[i]);
                SYM *term_sym = mk_tmp();
                
                temp = mk_tac(TAC_VAR, term_sym, NULL, NULL);
                temp->prev = code;
                code = temp;
                
                TAC *mul = mk_tac(TAC_MUL, term_sym, idx->ret, stride_sym);
                mul->prev = code;
                code = mul;
                
                /* 累加到总偏移 */
                if (offset_sym == NULL) {
                    offset_sym = term_sym;
                } else {
                    SYM *new_offset = mk_tmp();
                    temp = mk_tac(TAC_VAR, new_offset, NULL, NULL);
                    temp->prev = code;
                    code = temp;
                    
                    TAC *add = mk_tac(TAC_ADD, new_offset, offset_sym, term_sym);
                    add->prev = code;
                    code = add;
                    offset_sym = new_offset;
                }
            }
            
            /* 乘以元素大小 */
            if (arr_meta->elem_size > 1) {
                SYM *size_sym = mk_const(arr_meta->elem_size);
                SYM *byte_offset = mk_tmp();
                
                temp = mk_tac(TAC_VAR, byte_offset, NULL, NULL);
                temp->prev = code;
                code = temp;
                
                TAC *mul = mk_tac(TAC_MUL, byte_offset, offset_sym, size_sym);
                mul->prev = code;
                code = mul;
                offset_sym = byte_offset;
            }
            
            /* 更新当前地址：current_addr += offset */
            SYM *new_addr = mk_tmp();
            new_addr->dtype = DT_PTR;
            
            temp = mk_tac(TAC_VAR, new_addr, NULL, NULL);
            temp->prev = code;
            code = temp;
            
            TAC *add = mk_tac(TAC_ADD, new_addr, current_addr, offset_sym);
            add->prev = code;
            code = add;
            current_addr = new_addr;
            
            /* 更新当前类型和元数据 */
            if (arr_meta->elem_type == ELEM_STRUCT) {
                current_dtype = DT_STRUCT;
                current_meta = arr_meta->elem_meta;
                current_struct = (STRUCT_META *)current_meta;
            } else {
                current_dtype = (arr_meta->elem_type == ELEM_INT) ? DT_INT : DT_CHAR;
                current_meta = NULL;
                current_struct = NULL;
            }
            
        } else {
            /* ========== 字段访问 ========== */
            if (current_dtype != DT_STRUCT) {
                error("对非结构体类型访问字段 '%s'", access->name);
                return mk_exp(NULL, NULL, NULL);
            }
            
            if (!current_struct) {
                error("结构体元数据为空");
                return mk_exp(NULL, NULL, NULL);
            }
            
            /* 查找字段 */
            FIELD_META *field = find_field(current_struct, access->name);
            if (!field) {
                error("结构体 '%s' 中未找到字段 '%s'", 
                      current_struct->name, access->name);
                return mk_exp(NULL, NULL, NULL);
            }
            
            /* 计算字段地址：current_addr + field->offset */
            if (field->offset > 0) {
                SYM *offset_sym = mk_const(field->offset);
                SYM *new_addr = mk_tmp();
                new_addr->dtype = DT_PTR;
                
                temp = mk_tac(TAC_VAR, new_addr, NULL, NULL);
                temp->prev = code;
                code = temp;
                
                TAC *add = mk_tac(TAC_ADD, new_addr, current_addr, offset_sym);
                add->prev = code;
                code = add;
                current_addr = new_addr;
            }
            
            /* 更新当前类型和元数据 */
            switch (field->kind) {
                case FIELD_INT:
                    current_dtype = DT_INT;
                    current_meta = NULL;
                    current_struct = NULL;
                    break;
                    
                case FIELD_CHAR:
                    current_dtype = DT_CHAR;
                    current_meta = NULL;
                    current_struct = NULL;
                    break;
                    
                case FIELD_PTR:
                    current_dtype = DT_PTR;
                    current_meta = NULL;
                    current_struct = NULL;
                    break;
                    
                case FIELD_STRUCT:
                    current_dtype = DT_STRUCT;
                    current_meta = field->etc;
                    current_struct = (STRUCT_META *)current_meta;
                    break;
                    
                case FIELD_ARRAY:
                    current_dtype = DT_ARRAY;
                    current_meta = field->etc;
                    current_struct = NULL;
                    break;
                    
                default:
                    error("未知字段类型");
                    return mk_exp(NULL, NULL, NULL);
            }
        }
        
        access = access->next;
    }
    
    /* 4. 读取最终值 */
    SYM *result = mk_tmp();
    result->dtype = current_dtype;
    
    temp = mk_tac(TAC_VAR, result, NULL, NULL);
    temp->prev = code;
    code = temp;
    
    TAC *read = mk_tac(TAC_DEREF_R, result, current_addr, NULL);
    read->prev = code;
    code = read;
    
    return mk_exp(NULL, result, code);
}

/**
 * 写入字段值：支持多层嵌套访问
 * 例如：student.score = 90、arr[i].name = "Tom" 等
 */
TAC *do_field_write(FIELD_ACCESS *chain, EXP *val)
{
    if (!chain) {
        error("empty field access chain");
        return NULL;
    }
    
    /* 1. 查找基础变量 */
    SYM *base_var = get_var(chain->name);
    if (!base_var) {
        error("变量 '%s' 未定义", chain->name);
        return NULL;
    }
    
    TAC *code = NULL;
    SYM *current_addr = NULL;
    STRUCT_META *current_struct = NULL;
    void *current_meta = base_var->etc;
    int current_dtype = base_var->dtype;

    if (current_dtype == DT_STRUCT) {
        if (!current_meta) {
            error("结构体变量 '%s' 的元数据为空", chain->name);
            return NULL;
        }
        current_struct = (STRUCT_META *)current_meta;
    }
    
    /* 2. 获取基础变量地址 */
    current_addr = mk_tmp();
    current_addr->dtype = DT_PTR;
    
    TAC *temp = mk_tac(TAC_VAR, current_addr, NULL, NULL);
    code = temp;
    
    TAC *addr = mk_tac(TAC_ADDR, current_addr, base_var, NULL);
    addr->prev = code;
    code = addr;
    
    /* 3. 遍历访问链（与 read 相同的逻辑） */
    FIELD_ACCESS *access = chain->next;
    
    while (access) {
        if (access->type == 1) {
            /* ========== 数组索引访问 ========== */
            if (current_dtype != DT_ARRAY && current_dtype != DT_STRUCT) {
                error("对非数组类型进行索引访问");
                return NULL;
            }
            
            ARR_META *arr_meta = (ARR_META *)current_meta;
            if (!arr_meta) {
                error("数组元数据为空");
                return NULL;
            }
            
            /* 反转索引列表 */
            EXP *indices = reverse_exp_list(access->index);
            
            /* 检查维度 */
            int count = 0;
            for (EXP *idx = indices; idx; idx = idx->next) count++;
            
            if (count != arr_meta->ndims) {
                error("数组维度不匹配");
                return NULL;
            }
            
            /* 计算线性偏移 */
            SYM *offset_sym = NULL;
            EXP *idx = indices;
            
            for (int i = 0; i < arr_meta->ndims; i++, idx = idx->next) {
                code = join_tac(code, idx->tac);
                
                SYM *stride_sym = mk_const(arr_meta->strides[i]);
                SYM *term_sym = mk_tmp();
                
                temp = mk_tac(TAC_VAR, term_sym, NULL, NULL);
                temp->prev = code;
                code = temp;
                
                TAC *mul = mk_tac(TAC_MUL, term_sym, idx->ret, stride_sym);
                mul->prev = code;
                code = mul;
                
                if (offset_sym == NULL) {
                    offset_sym = term_sym;
                } else {
                    SYM *new_offset = mk_tmp();
                    temp = mk_tac(TAC_VAR, new_offset, NULL, NULL);
                    temp->prev = code;
                    code = temp;
                    
                    TAC *add = mk_tac(TAC_ADD, new_offset, offset_sym, term_sym);
                    add->prev = code;
                    code = add;
                    offset_sym = new_offset;
                }
            }
            
            /* 乘以元素大小 */
            if (arr_meta->elem_size > 1) {
                SYM *size_sym = mk_const(arr_meta->elem_size);
                SYM *byte_offset = mk_tmp();
                
                temp = mk_tac(TAC_VAR, byte_offset, NULL, NULL);
                temp->prev = code;
                code = temp;
                
                TAC *mul = mk_tac(TAC_MUL, byte_offset, offset_sym, size_sym);
                mul->prev = code;
                code = mul;
                offset_sym = byte_offset;
            }
            
            /* 更新地址 */
            SYM *new_addr = mk_tmp();
            new_addr->dtype = DT_PTR;
            
            temp = mk_tac(TAC_VAR, new_addr, NULL, NULL);
            temp->prev = code;
            code = temp;
            
            TAC *add = mk_tac(TAC_ADD, new_addr, current_addr, offset_sym);
            add->prev = code;
            code = add;
            current_addr = new_addr;
            
            /* 更新类型 */
            if (arr_meta->elem_type == ELEM_STRUCT) {
                current_dtype = DT_STRUCT;
                current_meta = arr_meta->elem_meta;
                current_struct = (STRUCT_META *)current_meta;
            } else {
                current_dtype = (arr_meta->elem_type == ELEM_INT) ? DT_INT : DT_CHAR;
                current_meta = NULL;
                current_struct = NULL;
            }
            
        } else {
            /* ========== 字段访问 ========== */
            if (current_dtype != DT_STRUCT) {
                error("对非结构体类型访问字段 '%s'", access->name);
                return NULL;
            }
            
            if (!current_struct) {
                error("结构体元数据为空");
                return NULL;
            }
            
            FIELD_META *field = find_field(current_struct, access->name);
            if (!field) {
                error("结构体中未找到字段 '%s'", access->name);
                return NULL;
            }
            
            /* 计算字段偏移 */
            if (field->offset > 0) {
                SYM *offset_sym = mk_const(field->offset);
                SYM *new_addr = mk_tmp();
                new_addr->dtype = DT_PTR;
                
                temp = mk_tac(TAC_VAR, new_addr, NULL, NULL);
                temp->prev = code;
                code = temp;
                
                TAC *add = mk_tac(TAC_ADD, new_addr, current_addr, offset_sym);
                add->prev = code;
                code = add;
                current_addr = new_addr;
            }
            
            /* 更新类型 */
            switch (field->kind) {
                case FIELD_INT:
                    current_dtype = DT_INT;
                    current_meta = NULL;
                    current_struct = NULL;
                    break;
                case FIELD_CHAR:
                    current_dtype = DT_CHAR;
                    current_meta = NULL;
                    current_struct = NULL;
                    break;
                case FIELD_PTR:
                    current_dtype = DT_PTR;
                    current_meta = NULL;
                    current_struct = NULL;
                    break;
                case FIELD_STRUCT:
                    current_dtype = DT_STRUCT;
                    current_meta = field->etc;
                    current_struct = (STRUCT_META *)current_meta;
                    break;
                case FIELD_ARRAY:
                    current_dtype = DT_ARRAY;
                    current_meta = field->etc;
                    current_struct = NULL;
                    break;
                default:
                    error("未知字段类型");
                    return NULL;
            }
        }
        
        access = access->next;
    }
    
    /* 4. 写入值 */
    code = join_tac(code, val->tac);
    
    TAC *write = mk_tac(TAC_DEREF_W, current_addr, val->ret, NULL);
    write->prev = code;
    
    return write;
}

/**
 * 对字段访问进行取址操作
 * 例如：&c1.num 或 &c1.grp[2].stu[3].ptr
 * 
 * @param chain 字段访问链
 * @return 表达式（包含地址计算的 TAC 和结果符号）
 */
EXP *do_field_addr(FIELD_ACCESS *chain)
{
    if (!chain) {
        error("do_field_addr: 空的字段访问链");
        return mk_exp(NULL, NULL, NULL);
    }
    
    /* 1. 查找基础变量 */
    SYM *base_var = get_var(chain->name);
    if (!base_var) {
        error("变量 '%s' 未定义", chain->name);
        return mk_exp(NULL, NULL, NULL);
    }
    
    TAC *code = NULL;
    SYM *current_addr = NULL;
    STRUCT_META *current_struct = NULL;
    void *current_meta = base_var->etc;
    int current_dtype = base_var->dtype;

    if (current_dtype == DT_STRUCT) {
        if (!current_meta) {
            error("结构体变量 '%s' 的元数据为空", chain->name);
            return mk_exp(NULL, NULL, NULL);
        }
        current_struct = (STRUCT_META *)current_meta;
    }
    
    /* 2. 获取基础变量地址 */
    current_addr = mk_tmp();
    current_addr->dtype = DT_PTR;
    
    TAC *temp = mk_tac(TAC_VAR, current_addr, NULL, NULL);
    code = temp;
    
    TAC *addr = mk_tac(TAC_ADDR, current_addr, base_var, NULL);
    addr->prev = code;
    code = addr;
    
    /* 3. 遍历访问链（与 do_field_read 相同的逻辑，但不读取值） */
    FIELD_ACCESS *access = chain->next;
    
    while (access) {
        if (access->type == 1) {
            /* ========== 数组索引访问 ========== */
            if (current_dtype != DT_ARRAY && current_dtype != DT_STRUCT) {
                error("对非数组类型进行索引访问");
                return mk_exp(NULL, NULL, NULL);
            }
            
            ARR_META *arr_meta = NULL;
            
            if (current_dtype == DT_ARRAY) {
                arr_meta = (ARR_META *)current_meta;
            } else {
                error("结构体字段访问后不应直接索引");
                return mk_exp(NULL, NULL, NULL);
            }
            
            if (!arr_meta) {
                error("数组元数据为空");
                return mk_exp(NULL, NULL, NULL);
            }
            
            /* 反转索引列表 */
            EXP *indices = reverse_exp_list(access->index);
            
            /* 检查维度数量 */
            int count = 0;
            for (EXP *idx = indices; idx; idx = idx->next) count++;
            
            if (count != arr_meta->ndims) {
                error("数组维度不匹配：需要 %d 维，提供了 %d 维", 
                      arr_meta->ndims, count);
                return mk_exp(NULL, NULL, NULL);
            }
            
            /* 计算线性偏移 */
            SYM *offset_sym = NULL;
            EXP *idx = indices;
            
            for (int i = 0; i < arr_meta->ndims; i++, idx = idx->next) {
                /* 串接索引表达式代码 */
                code = join_tac(code, idx->tac);
                
                /* term = idx[i] * stride[i] */
                SYM *stride_sym = mk_const(arr_meta->strides[i]);
                SYM *term_sym = mk_tmp();
                
                temp = mk_tac(TAC_VAR, term_sym, NULL, NULL);
                temp->prev = code;
                code = temp;
                
                TAC *mul = mk_tac(TAC_MUL, term_sym, idx->ret, stride_sym);
                mul->prev = code;
                code = mul;
                
                /* 累加到总偏移 */
                if (offset_sym == NULL) {
                    offset_sym = term_sym;
                } else {
                    SYM *new_offset = mk_tmp();
                    temp = mk_tac(TAC_VAR, new_offset, NULL, NULL);
                    temp->prev = code;
                    code = temp;
                    
                    TAC *add = mk_tac(TAC_ADD, new_offset, offset_sym, term_sym);
                    add->prev = code;
                    code = add;
                    offset_sym = new_offset;
                }
            }
            
            /* 乘以元素大小 */
            if (arr_meta->elem_size > 1) {
                SYM *size_sym = mk_const(arr_meta->elem_size);
                SYM *byte_offset = mk_tmp();
                
                temp = mk_tac(TAC_VAR, byte_offset, NULL, NULL);
                temp->prev = code;
                code = temp;
                
                TAC *mul = mk_tac(TAC_MUL, byte_offset, offset_sym, size_sym);
                mul->prev = code;
                code = mul;
                offset_sym = byte_offset;
            }
            
            /* 更新当前地址：current_addr += offset */
            SYM *new_addr = mk_tmp();
            new_addr->dtype = DT_PTR;
            
            temp = mk_tac(TAC_VAR, new_addr, NULL, NULL);
            temp->prev = code;
            code = temp;
            
            TAC *add = mk_tac(TAC_ADD, new_addr, current_addr, offset_sym);
            add->prev = code;
            code = add;
            current_addr = new_addr;
            
            /* 更新当前类型和元数据 */
            if (arr_meta->elem_type == ELEM_STRUCT) {
                current_dtype = DT_STRUCT;
                current_meta = arr_meta->elem_meta;
                current_struct = (STRUCT_META *)current_meta;
            } else {
                current_dtype = (arr_meta->elem_type == ELEM_INT) ? DT_INT : DT_CHAR;
                current_meta = NULL;
                current_struct = NULL;
            }
            
        } else {
            /* ========== 字段访问 ========== */
            if (current_dtype != DT_STRUCT) {
                error("对非结构体类型访问字段 '%s'", access->name);
                return mk_exp(NULL, NULL, NULL);
            }
            
            if (!current_struct) {
                error("结构体元数据为空");
                return mk_exp(NULL, NULL, NULL);
            }
            
            /* 查找字段 */
            FIELD_META *field = find_field(current_struct, access->name);
            if (!field) {
                error("结构体 '%s' 中未找到字段 '%s'", 
                      current_struct->name, access->name);
                return mk_exp(NULL, NULL, NULL);
            }
            
            /* 计算字段地址：current_addr + field->offset */
            if (field->offset > 0) {
                SYM *offset_sym = mk_const(field->offset);
                SYM *new_addr = mk_tmp();
                new_addr->dtype = DT_PTR;
                
                temp = mk_tac(TAC_VAR, new_addr, NULL, NULL);
                temp->prev = code;
                code = temp;
                
                TAC *add = mk_tac(TAC_ADD, new_addr, current_addr, offset_sym);
                add->prev = code;
                code = add;
                current_addr = new_addr;
            }
            
            /* 更新当前类型和元数据 */
            switch (field->kind) {
                case FIELD_INT:
                    current_dtype = DT_INT;
                    current_meta = NULL;
                    current_struct = NULL;
                    break;
                    
                case FIELD_CHAR:
                    current_dtype = DT_CHAR;
                    current_meta = NULL;
                    current_struct = NULL;
                    break;
                    
                case FIELD_PTR:
                    current_dtype = DT_PTR;
                    current_meta = NULL;
                    current_struct = NULL;
                    break;
                    
                case FIELD_STRUCT:
                    current_dtype = DT_STRUCT;
                    current_meta = field->etc;
                    current_struct = (STRUCT_META *)current_meta;
                    break;
                    
                case FIELD_ARRAY:
                    current_dtype = DT_ARRAY;
                    current_meta = field->etc;
                    current_struct = NULL;
                    break;
                    
                default:
                    error("未知字段类型");
                    return mk_exp(NULL, NULL, NULL);
            }
        }
        
        access = access->next;
    }
    
    /* 4. 返回最终地址（不读取值，与 do_field_read 的区别） */
    /* current_addr 现在指向目标字段的地址 */
    
    /* 为返回值创建临时变量 */
    SYM *result = mk_tmp();
    result->dtype = DT_PTR;
    
    /* 直接返回地址（不需要额外的 TAC，因为 current_addr 已经是地址） */
    return mk_exp(NULL, current_addr, code);
}

/* ========================================
 * 辅助函数
 * ======================================== */

/**
 * 判断是否为数组
 */
int is_array(SYM *s)
{
    return s && s->dtype == DT_ARRAY;
}

/**
 * 判断是否为结构体
 */
int is_struct(SYM *s)
{
    return s && s->dtype == DT_STRUCT;
}

/**
 * 判断是否为结构体数组
 */
int is_struct_array(SYM *s)
{
    if (!is_array(s)) return 0;
    ARR_META *arr = (ARR_META *)s->etc;
    return arr && arr->elem_type == ELEM_STRUCT;
}

/**
 * 获取类型大小
 */
int get_type_size(SYM *s)
{
    switch (s->dtype) {
        case DT_INT: return 4;
        case DT_CHAR: return 1;
        case DT_PTR: return 4;
        case DT_STRUCT:
            if (s->etc) {
                return get_struct_size((STRUCT_META *)s->etc);
            }
            return 0;
        case DT_ARRAY:
            if (s->etc) {
                return get_array_size((ARR_META *)s->etc);
            }
            return 0;
        default: return 0;
    }
}

/**
 * 获取结构体大小
 */
int get_struct_size(STRUCT_META *meta)
{
    return meta ? meta->size : 0;
}

/**
 * 获取数组大小
 */
int get_array_size(ARR_META *arr)
{
    return arr ? arr->total_elems * arr->elem_size : 0;
}

/**
 * 反转字段访问链
 */
FIELD_ACCESS *reverse_field_access(FIELD_ACCESS *chain)
{
    FIELD_ACCESS *prev = NULL;
    FIELD_ACCESS *current = chain;
    FIELD_ACCESS *next = NULL;
    
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    return prev;
}

/**
 * 反转表达式列表
 */
EXP *reverse_exp_list(EXP *list)
{
    EXP *prev = NULL;
    EXP *current = list;
    EXP *next = NULL;
    
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    return prev;
}

/* ========================================
 * Switch 语句相关函数实现（修复版）
 * ======================================== */

/* ✅ 全局变量：switch 标签栈（支持嵌套） */
typedef struct switch_stack {
    SYM *end_label;
    struct switch_stack *prev;
} SWITCH_STACK;

static SWITCH_STACK *switch_stack = NULL;

/**
 * 进入 switch：预分配结束标签并压栈
 * @return 结束标签（需保存到语法规则中）
 */
SYM *enter_switch(void)
{
    /* 1. 分配新的结束标签 */
    SYM *end_label = mk_label(mk_lstr(next_label++));
    
    /* 2. 压栈（支持嵌套） */
    SWITCH_STACK *new_frame = (SWITCH_STACK *)malloc(sizeof(SWITCH_STACK));
    if (!new_frame) {
        error("malloc failed for SWITCH_STACK");
        exit(1);
    }
    new_frame->end_label = end_label;
    new_frame->prev = switch_stack;
    switch_stack = new_frame;

     enter_break_context(end_label);
    
    return end_label;
}

/**
 * 创建一个 case 节点
 */
CASE_NODE *mk_case(int value, TAC *code)
{
    CASE_NODE *c = (CASE_NODE *)malloc(sizeof(CASE_NODE));
    if (!c) {
        error("malloc failed for CASE_NODE");
        exit(1);
    }
    
    c->value = value;
    c->code = code;
    c->next = NULL;
    
    return c;
}

/**
 * 将新 case 追加到 case 列表末尾
 */
CASE_NODE *append_case(CASE_NODE *list, CASE_NODE *new_case)
{
    if (!list) return new_case;
    if (!new_case) return list;
    
    CASE_NODE *tail = list;
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = new_case;
    
    return list;
}

/* 进入循环 */
void enter_loop(SYM *begin_label, SYM *continue_label, SYM *end_label)
{
    LOOP_CTX *ctx = malloc(sizeof(LOOP_CTX));
    ctx->begin_label = begin_label;
    ctx->continue_label = continue_label;
    ctx->end_label = end_label;
    ctx->prev = loop_stack;
    loop_stack = ctx;
}
/* 退出循环 */
void exit_loop(void)
{
    if (!loop_stack) {
        error("Internal: loop context underflow");
        return;
    }
    LOOP_CTX *old = loop_stack;
    loop_stack = old->prev;
    free(old);
}
/* 进入 break 上下文 */
void enter_break_context(SYM *end_label)
{
    BREAK_CTX *ctx = malloc(sizeof(BREAK_CTX));
    ctx->end_label = end_label;
    ctx->prev = break_stack;
    break_stack = ctx;
}
/* 退出 break 上下文 */
void exit_break_context(void)
{
    if (!break_stack) {
        error("Internal: break context underflow");
        return;
    }
    BREAK_CTX *old = break_stack;
    break_stack = old->prev;
    free(old);
}
/**
 * 生成 for 循环的 TAC（使用语法分析阶段预分配的标签）
 */
TAC *do_for(TAC *init, EXP *cond, TAC *iter, TAC *body)
{
    /* 1. 从解析栈获取标签 */
    LOOP_PARSE_CTX *ctx = get_current_loop_labels();
    if (!ctx) {
        error("Internal: for loop context not found");
        return NULL;
    }
    
    SYM *Lbegin = ctx->begin_label;
    SYM *Lcont = ctx->continue_label;
    SYM *Lend = ctx->end_label;
    
    /* 2. 生成 TAC（不再设置上下文,因为已经设置过了） */
    TAC *code = init;
    
    /* Lbegin: */
    code = join_tac(code, mk_tac(TAC_LABEL, Lbegin, NULL, NULL));
    
    /* 条件判断 */
    if (cond) {
        code = join_tac(code, cond->tac);
        code = join_tac(code, mk_tac(TAC_IFZ, Lend, cond->ret, NULL));
    }
    
    /* 循环体 */
    code = join_tac(code, body);
    
    /* Lcont: */
    code = join_tac(code, mk_tac(TAC_LABEL, Lcont, NULL, NULL));
    
    /* 迭代 */
    if (iter) {
        code = join_tac(code, iter);
    }
    
    /* goto Lbegin */
    code = join_tac(code, mk_tac(TAC_GOTO, Lbegin, NULL, NULL));
    
    /* Lend: */
    code = join_tac(code, mk_tac(TAC_LABEL, Lend, NULL, NULL));
    
    return code;
}

/* 改造 do_while */
/**
 * 生成 while 循环的 TAC（使用语法分析阶段预分配的标签）
 */
TAC *do_while(EXP *cond, TAC *body)
{
    /* 1. 从解析栈获取标签 */
    LOOP_PARSE_CTX *ctx = get_current_loop_labels();
    if (!ctx) {
        error("Internal: while loop context not found");
        return NULL;
    }
    
    SYM *Lbegin = ctx->begin_label;
    SYM *Lend = ctx->end_label;
    
    /* 2. 生成 TAC */
    TAC *code = NULL;
    
    /* Lbegin: */
    code = join_tac(code, mk_tac(TAC_LABEL, Lbegin, NULL, NULL));
    
    /* 条件判断 */
    code = join_tac(code, cond->tac);
    code = join_tac(code, mk_tac(TAC_IFZ, Lend, cond->ret, NULL));
    
    /* 循环体 */
    code = join_tac(code, body);
    
    /* goto Lbegin */
    code = join_tac(code, mk_tac(TAC_GOTO, Lbegin, NULL, NULL));
    
    /* Lend: */
    code = join_tac(code, mk_tac(TAC_LABEL, Lend, NULL, NULL));
    
    return code;
}

/* break */
TAC *do_break(void)
{
    if (!break_stack) {
        error("break not within loop/switch"); 
        return NULL;
    }
    return mk_tac(TAC_GOTO, break_stack->end_label, NULL, NULL);
}
/* continue */
TAC *do_continue(void)
{
    if (!loop_stack) {
        error("continue not within loop"); 
        return NULL;
    }
    return mk_tac(TAC_GOTO, loop_stack->continue_label, NULL, NULL);
}
/* 改造 exit_switch */
TAC *exit_switch(EXP *sel, CASE_NODE *cases, TAC *default_block, SYM *end_label)
{
    TAC *code = NULL;
    
    /* 1. 检查栈状态 */
    if (!switch_stack) {
        error("exit_switch: switch stack underflow");
        return NULL;
    }
    
    /* 2. 验证标签一致性 */
    if (switch_stack->end_label != end_label) {
        error("exit_switch: label mismatch");
    }
    
    /* 4. 生成选择表达式的 TAC */
    code = sel->tac;
    
    /* 5. 检查重复的 case 值 */
    for (CASE_NODE *c1 = cases; c1; c1 = c1->next) {
        for (CASE_NODE *c2 = c1->next; c2; c2 = c2->next) {
            if (c1->value == c2->value) {
                error("duplicate case value: %d", c1->value);
            }
        }
    }
    
    /* 6. 为每个 case 生成比较和跳转 */
    CASE_NODE *c = cases;
    while (c) {
        /* 6.1 比较：t = (sel == case_value) */
        SYM *tmp = mk_tmp();
        TAC *var_tac = mk_tac(TAC_VAR, tmp, NULL, NULL);
        var_tac->prev = code;
        code = var_tac;
        
        TAC *cmp_tac = mk_tac(TAC_EQ, tmp, sel->ret, mk_const(c->value));
        cmp_tac->prev = code;
        code = cmp_tac;
        
        /* 6.2 生成下一个 case 的标签 */
        SYM *next_label_sym = mk_label(mk_lstr(next_label++));
        
        /* 6.3 ifz t goto next_label */
        TAC *ifz_tac = mk_tac(TAC_IFZ, next_label_sym, tmp, NULL);
        ifz_tac->prev = code;
        code = ifz_tac;
        
        /* 6.4 case 体代码（在此期间可能遇到 break，会跳到 end_label） */
        if (c->code) {
            code = join_tac(code, c->code);
        }
        
        /* 6.5 goto end_label（自动 break，避免 fallthrough） */
        TAC *goto_end = mk_tac(TAC_GOTO, end_label, NULL, NULL);
        goto_end->prev = code;
        code = goto_end;
        
        /* 6.6 next_label: */
        TAC *next_lab = mk_tac(TAC_LABEL, next_label_sym, NULL, NULL);
        next_lab->prev = code;
        code = next_lab;
        
        c = c->next;
    }
    
    /* 7. default 分支（如果有） */
    if (default_block) {
        code = join_tac(code, default_block);
    }
    
    /* 8. end_label: */
    TAC *end_lab = mk_tac(TAC_LABEL, end_label, NULL, NULL);
    end_lab->prev = code;
    code = end_lab;
    
    /* ✅ 9. 退出 break 上下文（在弹出 switch 栈之前） */
    exit_break_context();
    
    /* 10. 出栈 */
    SWITCH_STACK *old_frame = switch_stack;
    switch_stack = switch_stack->prev;
    free(old_frame);
    
    return code;    
}

void enter_loop_context(void)
{
    /* 1. 分配标签 */
    SYM *begin_label = mk_label(mk_lstr(next_label++));
    SYM *cont_label = mk_label(mk_lstr(next_label++));
    SYM *end_label = mk_label(mk_lstr(next_label++));
    
    /* 2. 压栈保存标签 */
    LOOP_PARSE_CTX *ctx = (LOOP_PARSE_CTX *)malloc(sizeof(LOOP_PARSE_CTX));
    if (!ctx) {
        error("malloc failed for LOOP_PARSE_CTX");
        exit(1);
    }
    ctx->begin_label = begin_label;
    ctx->continue_label = cont_label;
    ctx->end_label = end_label;
    ctx->prev = loop_parse_stack;
    loop_parse_stack = ctx;
    
    /* 3. 设置运行时上下文（供 break/continue 使用） */
    enter_loop(begin_label, cont_label, end_label);
    enter_break_context(end_label);
}
/**
 * 退出循环上下文（在语法分析阶段调用）
 */
void exit_loop_context(void)
{
    /* 1. 退出运行时上下文 */
    exit_break_context();
    exit_loop();
    
    /* 2. 弹出解析栈 */
    if (!loop_parse_stack) {
        error("Internal: loop_parse_stack underflow");
        return;
    }
    
    LOOP_PARSE_CTX *old = loop_parse_stack;
    loop_parse_stack = old->prev;
    free(old);
}