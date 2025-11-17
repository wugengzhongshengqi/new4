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

/* 数组元数据结构：存储维度信息与步幅 */
typedef struct {
    int dims[16];      // 各维度大小
    int ndims;         // 维度数量
    int strides[16];   // 各维度步幅（元素数量）
    int elem_size;     // 元素大小（字节）
    int total_elems;   // 总元素数量
} ARR_META;

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

/* while (exp) stmt ：先创建循环入口 label，再利用 if+goto 实现循环 */
TAC *do_while(EXP *exp, TAC *stmt) 
{
    TAC *label=mk_tac(TAC_LABEL, mk_label(mk_lstr(next_label++)), NULL, NULL);
    TAC *code=mk_tac(TAC_GOTO, label->a, NULL, NULL);

    /* Lbegin: ifz ret goto Lend; stmt; goto Lbegin; Lend: */
    code->prev=stmt; /* 语句后接回到循环首的 goto */

    return join_tac(label, do_if(exp, code));
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
        if(i->a->etc != NULL) {
            ARR_META *meta = (ARR_META *)i->a->etc;
            fprintf(f, "var %s[", to_str(i->a, sa));
            for(int j=0; j<meta->ndims; j++) {
                fprintf(f, "%d%s", meta->dims[j], (j<meta->ndims-1)?"][":"]");
            }
        } else {
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
    sym->dtype=(decl_dtype==DT_CHAR)?DT_PTR_CHAR:DT_PTR_INT; /* 根据当前声明基本类型决定指针的目标类型 */

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
    sym->dtype=decl_dtype;  // 元素基本类型（DT_INT/DT_CHAR）

    /* 3) 分配并填充数组元数据 */
    meta=(ARR_META *)malloc(sizeof(ARR_META));
    meta->ndims=ndims;
    meta->elem_size=4;
    
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
    if(var->dtype==DT_CHAR) temp->a->dtype=DT_PTR_CHAR; else temp->a->dtype=DT_PTR_INT;
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
    if(ptr->ret->dtype==DT_PTR_CHAR) temp->a->dtype=DT_CHAR; else temp->a->dtype=DT_INT;
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
