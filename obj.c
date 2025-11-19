/*
 * 对象代码生成器
 * 将三地址码(TAC)翻译为目标机指令文本，维护寄存器分配、
 * 栈帧布局以及调用约定（参数传递、返回、跳转/条件）。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "tac.h"
#include "obj.h"

/* 全局状态（生成阶段） */
int tos; /* top of static */
int tof; /* top of frame */
int oof; /* offset of formal */
int oon; /* offset of next frame */
struct rdesc rdesc[R_NUM];

/* 清空寄存器描述符 */
void rdesc_clear(int r)    
{
	rdesc[r].var = NULL;
	rdesc[r].mod = 0;
}

/* 填充寄存器描述符，确保同一符号不会同时绑定于多寄存器 */
void rdesc_fill(int r, SYM *s, int mod)
{
	int old;
	for(old=R_GEN; old < R_NUM; old++)
	{
		if(rdesc[old].var==s)
		{
			rdesc_clear(old);
		}
	}

	rdesc[r].var=s;
	rdesc[r].mod=mod;
}     

/* 若寄存器中的变量已修改，则回写至其内存位置 */
void asm_write_back(int r)
{
	if((rdesc[r].var!=NULL) && rdesc[r].mod)
	{
		if(rdesc[r].var->scope==1) /* local var */
		{
			out_str(file_s, "	STO (R%u+%u),R%u\n", R_BP, rdesc[r].var->offset, r);
		}
		else /* global var */
		{
			out_str(file_s, "	LOD R%u,STATIC\n", R_TP);
			out_str(file_s, "	STO (R%u+%u),R%u\n", R_TP, rdesc[r].var->offset, r);
		}
		rdesc[r].mod=UNMODIFIED;
	}
}

/* 将符号 s 的值加载到寄存器 r，可能来自常量、局部、全局或文本地址 */
void asm_load(int r, SYM *s) 
{
	/* already in a reg */
	for(int i=R_GEN; i < R_NUM; i++)  
	{
		if(rdesc[i].var==s)
		{
			/* load from the reg */
			out_str(file_s, "	LOD R%u,R%u\n", r, i);

			/* update rdesc */
			// rdesc_fill(r, s, rdesc[i].mod);
			return;
		}
	}
	
	/* not in a reg */
	switch(s->type)
	{
		case SYM_INT:
		out_str(file_s, "	LOD R%u,%u\n", r, s->value);
		break;

		case SYM_VAR:
		if(s->scope==1) /* local var */
		{
			if((s->offset)>=0) out_str(file_s, "	LOD R%u,(R%u+%d)\n", r, R_BP, s->offset);
			else out_str(file_s, "	LOD R%u,(R%u-%d)\n", r, R_BP, -(s->offset));
		}
		else /* global var */
		{
			out_str(file_s, "	LOD R%u,STATIC\n", R_TP);
			out_str(file_s, "	LOD R%u,(R%u+%d)\n", r, R_TP, s->offset);
		}
		break;

		case SYM_TEXT:
		out_str(file_s, "	LOD R%u,L%u\n", r, s->label);
		break;
	}

	// rdesc_fill(r, s, UNMODIFIED);
}   

/* 分配寄存器，exclude 指定不可使用的寄存器 */
int reg_alloc_exclude(SYM *s, int exclude)
{
    int r; 

    /* 1. 已在寄存器中 */
    for(r=R_GEN; r < R_NUM; r++)
    {
        if(rdesc[r].var==s)
		{
			if(rdesc[r].mod) asm_write_back(r);
			return r;
		}
    }

    /* 2. 空寄存器（排除指定寄存器） */
    for(r=R_GEN; r < R_NUM; r++)
    {
        if(r != exclude && rdesc[r].var==NULL)
        {
            asm_load(r, s);
            rdesc_fill(r, s, UNMODIFIED);
            return r;
        }
    }
    
    /* 3. UNMODIFIED 且非临时变量（排除指定寄存器） */
    for(r=R_GEN; r < R_NUM; r++)
    {
        if(r != exclude && !rdesc[r].mod)
        {
            asm_load(r, s);
            rdesc_fill(r, s, UNMODIFIED);
            return r;
        }
    }

    /* 4. MODIFIED 变量（排除指定寄存器） */
    for(r=R_GEN; r < R_NUM; r++)
    {
        if(r != exclude && rdesc[r].var->type == SYM_VAR)
        {
            asm_write_back(r);
            asm_load(r, s);
            rdesc_fill(r, s, UNMODIFIED);
            return r;
        }
    }

    /* 5. 寄存器溢出 */
    error("Register spill");
    return R_GEN;
}

/* 原函数包装 */
int reg_alloc(SYM *s)
{
    return reg_alloc_exclude(s, -1);  // -1 表示无排除
}

/* 生成二元算术指令，结果绑定到 a 所在寄存器并标记为修改 */
void asm_bin(char *op, SYM *a, SYM *b, SYM *c)
{
	int reg_b, reg_c; 
    reg_b = reg_alloc(b); 
    
    // 如果 b 和 c 是同一个符号，直接使用同一个寄存器
    if (b == c) {
        reg_c = reg_b;
    } else {
		reg_c = reg_alloc_exclude(c, reg_b); 
	}
	
	out_str(file_s, "	%s R%u,R%u\n", op, reg_b, reg_c);
	rdesc_fill(reg_b, a, MODIFIED);
}   

/* 关系比较：通过 SUB+TST，再依据标志寄存器合成 0/1 到目标寄存器 */
void asm_cmp(int op, SYM *a, SYM *b, SYM *c)
{
	int reg_b, reg_c; 
	
	reg_b = reg_alloc(b); 
	// 如果 b 和 c 是同一个符号，直接使用同一个寄存器
    if (b == c) {
        reg_c = reg_b;
    } else {
		reg_c = reg_alloc_exclude(c,reg_b); 
	}

	out_str(file_s, "	SUB R%u,R%u\n", reg_b, reg_c);
	out_str(file_s, "	TST R%u\n", reg_b);

	switch(op)
	{		
		case TAC_EQ:
		out_str(file_s, "	LOD R3,R1+40\n");
		out_str(file_s, "	JEZ R3\n");
		out_str(file_s, "	LOD R%u,0\n", reg_b);
		out_str(file_s, "	LOD R3,R1+24\n");
		out_str(file_s, "	JMP R3\n");
		out_str(file_s, "	LOD R%u,1\n", reg_b);
		break;
		
		case TAC_NE:
		out_str(file_s, "	LOD R3,R1+40\n");
		out_str(file_s, "	JEZ R3\n");
		out_str(file_s, "	LOD R%u,1\n", reg_b);
		out_str(file_s, "	LOD R3,R1+24\n");
		out_str(file_s, "	JMP R3\n");
		out_str(file_s, "	LOD R%u,0\n", reg_b);
		break;
		
		case TAC_LT:
		out_str(file_s, "	LOD R3,R1+40\n");
		out_str(file_s, "	JLZ R3\n");
		out_str(file_s, "	LOD R%u,0\n", reg_b);
		out_str(file_s, "	LOD R3,R1+24\n");
		out_str(file_s, "	JMP R3\n");
		out_str(file_s, "	LOD R%u,1\n", reg_b);
		break;
		
		case TAC_LE:
		out_str(file_s, "	LOD R3,R1+40\n");
		out_str(file_s, "	JGZ R3\n");
		out_str(file_s, "	LOD R%u,1\n", reg_b);
		out_str(file_s, "	LOD R3,R1+24\n");
		out_str(file_s, "	JMP R3\n");
		out_str(file_s, "	LOD R%u,0\n", reg_b);
		break;
		
		case TAC_GT:
		out_str(file_s, "	LOD R3,R1+40\n");
		out_str(file_s, "	JGZ R3\n");
		out_str(file_s, "	LOD R%u,0\n", reg_b);
		out_str(file_s, "	LOD R3,R1+24\n");
		out_str(file_s, "	JMP R3\n");
		out_str(file_s, "	LOD R%u,1\n", reg_b);
		break;
		
		case TAC_GE:
		out_str(file_s, "	LOD R3,R1+40\n");
		out_str(file_s, "	JLZ R3\n");
		out_str(file_s, "	LOD R%u,1\n", reg_b);
		out_str(file_s, "	LOD R3,R1+24\n");
		out_str(file_s, "	JMP R3\n");
		out_str(file_s, "	LOD R%u,0\n", reg_b);
		break;
	}

	/* Delete c from the descriptors and insert a */
	rdesc_clear(reg_b);
	rdesc_fill(reg_b, a, MODIFIED);
}   

/* 条件/无条件跳转：必要时测试寄存器，再输出跳转伪指令 */
void asm_cond(char *op, SYM *a,  char *l)
{
	for(int r=R_GEN; r < R_NUM; r++) asm_write_back(r);

	if(a !=NULL)
	{
		int r;

		for(r=R_GEN; r < R_NUM; r++) /* Is it in reg? */
		{
			if(rdesc[r].var==a) break;
		}

		if(r < R_NUM) out_str(file_s, "	TST R%u\n", r);
		else out_str(file_s, "	TST R%u\n", reg_alloc(a)); /* Load into new register */
	}

	out_str(file_s, "	%s %s\n", op, l); 
} 

/* 函数调用：保存旧 BP 与返回地址，切换帧，跳转；处理返回值寄存器 */
void asm_call(SYM *a, SYM *b)
{
	int r;
	for(int r=R_GEN; r < R_NUM; r++) asm_write_back(r);
	for(int r=R_GEN; r < R_NUM; r++) rdesc_clear(r);
	out_str(file_s, "	STO (R2+%d),R2\n", tof+oon);	/* store old bp */
	oon += 4;
	out_str(file_s, "	LOD R4,R1+32\n"); 				/* return addr: 4*8=32 */
	out_str(file_s, "	STO (R2+%d),R4\n", tof+oon);	/* store return addr */
	oon += 4;
	out_str(file_s, "	LOD R2,R2+%d\n", tof+oon-8);	/* load new bp */
	out_str(file_s, "	JMP %s\n", (char *)b);			/* jump to new func */
	if(a != NULL)
	{
		r = reg_alloc(a);
		out_str(file_s, "	LOD R%u,R%u\n", r, R_TP);	
		rdesc[r].mod = MODIFIED;
	}
	oon=0;
}

/* 函数返回：可选返回值装载，恢复 BP 并跳转至返回地址 */
void asm_return(SYM *a)
{
	for(int r=R_GEN; r < R_NUM; r++) asm_write_back(r);
	for(int r=R_GEN; r < R_NUM; r++) rdesc_clear(r);

	if(a!=NULL)	 /* return value */
	{
		asm_load(R_TP, a);
	}

	out_str(file_s, "	LOD R3,(R2+4)\n");	/* return address */
	out_str(file_s, "	LOD R2,(R2)\n");	/* restore bp */
	out_str(file_s, "	JMP R3\n");			/* return */
}   

/* 输出程序头：初始化栈与默认返回地址 */
void asm_head()
{
	char head[]=
	"	# head\n"
	"	LOD R2,STACK\n"
	"	STO (R2),0\n"
	"	LOD R4,EXIT\n"
	"	STO (R2+4),R4\n";

	out_str(file_s, "%s", head);
}

/* 输出程序尾与 EXIT 标签 */
void asm_tail()
{
	char tail[]=
	"\n	# tail\n"
	"EXIT:\n"
	"	END\n";

	out_str(file_s, "%s", tail);
}

/* 输出字符串常量数据区，处理转义字符并以 0 结尾 */
void asm_str(SYM *s)
{
	char *t=s->name; /* The text */
	int i;

	out_str(file_s, "L%u:\n", s->label); /* Label for the string */
	out_str(file_s, "	DBS "); /* Label for the string */

	for(i=1; t[i + 1] !=0; i++)
	{
		if(t[i]=='\\')
		{
			switch(t[++i])
			{
				case 'n':
				out_str(file_s, "%u,", '\n');
				break;

				case '\"':
				out_str(file_s, "%u,", '\"');
				break;
			}
		}
		else out_str(file_s, "%u,", t[i]);
	}

	out_str(file_s, "0\n"); /* End of string */
}

/* 输出静态区与栈入口，先输出所有字符串常量标签 */
void asm_static(void)
{
	int i;

	SYM *sl;

	for(sl=sym_tab_global; sl !=NULL; sl=sl->next)
	{
		if(sl->type==SYM_TEXT) asm_str(sl);
	}

	out_str(file_s, "STATIC:\n");
	out_str(file_s, "	DBN 0,%u\n", tos);				
	out_str(file_s, "STACK:\n");
}

/* 翻译一条 TAC 到目标指令 */
void asm_code(TAC *c)
{
	int r;

	switch(c->op)
	{
		case TAC_UNDEF:
		error("cannot translate TAC_UNDEF");
		return;

		case TAC_ADD:
		asm_bin("ADD", c->a, c->b, c->c);
		return;

		case TAC_SUB:
		asm_bin("SUB", c->a, c->b, c->c);
		return;

		case TAC_MUL:
		asm_bin("MUL", c->a, c->b, c->c);
		return;

		case TAC_DIV:
		asm_bin("DIV", c->a, c->b, c->c);
		return;

		case TAC_NEG:
		asm_bin("SUB", c->a, mk_const(0), c->b);
		return;

		case TAC_EQ:
		case TAC_NE:
		case TAC_LT:
		case TAC_LE:
		case TAC_GT:
		case TAC_GE:
		asm_cmp(c->op, c->a, c->b, c->c);
		return;

		case TAC_COPY:
		r = reg_alloc(c->b);
		rdesc_fill(r, c->a, MODIFIED);
		return;

        case TAC_INPUT:
        r=reg_alloc(c->a);
        if(c->a->dtype==DT_CHAR){
            out_str(file_s, "	ITC\n");
        } else {
            out_str(file_s, "	ITI\n");
        }
        out_str(file_s, "	LOD R%u,R15\n", r);
        rdesc[r].mod = MODIFIED;
        return;

        case TAC_OUTPUT:
        if(c->a->type == SYM_VAR)
        {
            r=reg_alloc(c->a);
            out_str(file_s, "	LOD R15,R%u\n", r);
            if(c->a->dtype==DT_CHAR){
                out_str(file_s, "	OTC\n");
            } else {
                out_str(file_s, "	OTI\n");
            }
        } else if(c->a->type == SYM_TEXT)
        {
            r=reg_alloc(c->a);
            out_str(file_s, "	LOD R15,R%u\n", r);
            out_str(file_s, "	OTS\n");
        }
        return;

		case TAC_GOTO:
		asm_cond("JMP", NULL, c->a->name);
		return;

		case TAC_IFZ:
		asm_cond("JEZ", c->b, c->a->name);
		return;

		case TAC_LABEL:
		for(int r=R_GEN; r < R_NUM; r++) asm_write_back(r);
		for(int r=R_GEN; r < R_NUM; r++) rdesc_clear(r);
		out_str(file_s, "%s:\n", c->a->name);
		return;

		case TAC_ACTUAL:
		r=reg_alloc(c->a);
		out_str(file_s, "	STO (R2+%d),R%u\n", tof+oon, r);
		oon += 4;
		return;

		case TAC_CALL:
		asm_call(c->a, c->b);

		if (c->a != NULL) {  /* 有返回值的调用 */
			int r = reg_alloc(c->a);  /* 分配寄存器给返回值 */
			out_str(file_s, "\tLOD R%u,R%u\n", r, R_TP);  /* R_r = R_TP */
			rdesc_fill(r, c->a, MODIFIED);  /* 更新寄存器描述符 */
		}
		return;

		case TAC_BEGINFUNC:
		/* We reset the top of stack, since it is currently empty apart from the link information. */
		scope=1;
		tof=LOCAL_OFF;
		oof=FORMAL_OFF;
		oon=0;
		return;

		case TAC_FORMAL:
		c->a->scope=1; /* parameter is special local var */
		c->a->offset=oof;
		oof -=4;
		return;

		case TAC_VAR:
		{
			int size = 4; /* 默认大小：普通变量或指针 */

			/* 检查是否为数组 */
			if(c->a->dtype == DT_STRUCT && c->a->etc != NULL)
			{
				STRUCT_META *meta = (STRUCT_META *)(c->a->etc);
				size = meta->size;
			}
			else if(c->a->dtype == DT_ARRAY && c->a->etc != NULL)
			{
				/* 数组元数据结构定义（与 tac.c 中一致） */
				// fprintf(stderr, "GETIN\n");

				ARR_META *meta = (ARR_META *)(c->a->etc);
				size = meta->total_elems * meta->elem_size;

				// fprintf(stderr, "%d %d\n", meta->total_elems, meta->elem_size);
			}

			/* 分配空间 */
			if(scope)
			{
				c->a->scope = 1; /* 局部变量 */
				c->a->offset = tof;
				tof += size;
			}
			else
			{
				c->a->scope = 0; /* 全局变量 */
				c->a->offset = tos;
				tos += size;
			}
			return;
		}


		case TAC_RETURN:
		asm_return(c->a);
		return;

		case TAC_ENDFUNC:
		asm_return(NULL);
		scope=0;
		return;

		case TAC_ADDR:
		{
			int r = reg_alloc(c->a);
			/* compute address of symbol c->b */
			if(c->b->type==SYM_VAR)
			{
				if(c->b->scope==1)
				{
					out_str(file_s, "\tLOD R%u,R%u\n", r, R_BP);
					if((c->b->offset)>=0) out_str(file_s, "\tADD R%u,%d\n", r, c->b->offset);
					else out_str(file_s, "\tADD R%u,%d\n", r, -(c->b->offset));
				}
				else
				{
					out_str(file_s, "\tLOD R%u,STATIC\n", r);
					out_str(file_s, "\tADD R%u,%d\n", r, c->b->offset);
				}
			}
			rdesc_fill(r, c->a, MODIFIED);
			return;
		}

		case TAC_DEREF_R:
		{
			int rp = reg_alloc(c->b);
			int rd = reg_alloc_exclude(c->a, rp);
			/* choose byte or word load by pointer dtype */
			out_str(file_s, "\tLOD R%u,(R%u)\n", rd, rp);
			rdesc_fill(rd, c->a, MODIFIED);
			return;
		}

		case TAC_DEREF_W:
		{
			for(int r=R_GEN; r < R_NUM; r++) {
        		asm_write_back(r);
    		}

			int rp = reg_alloc(c->a);
			int rv = reg_alloc_exclude(c->b, rp);
			out_str(file_s, "\tSTO (R%u),R%u\n", rp, rv);

			for(int r=R_GEN; r < R_NUM; r++) {
				if(rdesc[r].var && rdesc[r].var->type == SYM_VAR) {
					rdesc_clear(r);
				}
			}
			return;
		}

		case TAC_FIELD_READ:
		{
			/* 结构体字段读取：dest = base.field */
			FIELD_INFO *info = (FIELD_INFO *)c->c;  /* 字段信息 */
			int r_base = reg_alloc(c->b);            /* 基地址 */
			int r_dest = reg_alloc_exclude(c->a, r_base); /* 目标寄存器 */
			
			/* 计算字段地址：base + offset */
			out_str(file_s, "\tLOD R%u,R%u\n", r_dest, r_base);
			if(info->offset > 0) {
				out_str(file_s, "\tADD R%u,%d\n", r_dest, info->offset);
			}
			
			out_str(file_s, "\tLOD R%u,(R%u)\n", r_dest, r_dest);
			
			rdesc_fill(r_dest, c->a, MODIFIED);
			return;
		}
		case TAC_FIELD_WRITE:
		{
			for(int r=R_GEN; r < R_NUM; r++) {
				asm_write_back(r);
			}
			/* 结构体字段写入：base.field = src */
			FIELD_INFO *info = (FIELD_INFO *)c->c;  /* 字段信息 */
			int r_base = reg_alloc(c->a);            /* 基地址 */
			int r_src = reg_alloc_exclude(c->b, r_base); /* 源值 */
			int r_addr = reg_alloc_exclude(mk_tmp(), r_base); /* 临时地址 */
			
			/* 计算字段地址：base + offset */
			out_str(file_s, "\tLOD R%u,R%u\n", r_addr, r_base);
			if(info->offset > 0) {
				out_str(file_s, "\tADD R%u,%d\n", r_addr, info->offset);
			}
			
			out_str(file_s, "\tSTO (R%u),R%u\n", r_addr, r_src);

			for(int r=R_GEN; r < R_NUM; r++) {
				if(rdesc[r].var && rdesc[r].var->type == SYM_VAR) {
					rdesc_clear(r);
				}
			}
			
			return;
		}

		default:
		/* Don't know what this one is */
		error("unknown TAC opcode to translate");
		return;
	}
}

/* 主入口：遍历 TAC 链表，边注释边生成目标代码，最后输出尾与静态区 */
void tac_obj()
{
	tof=LOCAL_OFF; /* TOS allows space for link info */
	oof=FORMAL_OFF;
	oon=0;

	for(int r=0; r < R_NUM; r++) rdesc[r].var=NULL;
	
	asm_head();

	TAC * cur;
	for(cur=tac_first; cur!=NULL; cur=cur->next)
	{
		out_str(file_s, "\n	# ");
		out_tac(file_s, cur);
		out_str(file_s, "\n");
		asm_code(cur);
	}
	asm_tail();
	asm_static();
}

