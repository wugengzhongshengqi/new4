/*
 * 对象代码生成常量与接口
 * 定义寄存器编号、栈帧布局、寄存器描述符以及生成入口。
 */
/* register 寄存器编号
 * R_FLAG: 标志寄存器；R_IP: 指令指针；R_BP: 基址指针（帧基）
 * R_JP: 跳转寄存器；R_TP: 临时返回/中转寄存器；
 * R_GEN..R_NUM-1: 通用寄存器区，用于表达式与中间值
 */
#define R_UNDEF -1
#define R_FLAG 0
#define R_IP 1
#define R_BP 2
#define R_JP 3
#define R_TP 4
#define R_GEN 5
#define R_NUM 16

/* frame 栈帧布局偏移（以字节为单位）
 * FORMAL_OFF: 形参起始偏移（向下递减）
 * OBP_OFF: 动态链（旧 BP）位置
 * RET_OFF: 返回地址位置
 * LOCAL_OFF: 局部变量起始偏移（向上递增）
 */
#define FORMAL_OFF -4 	/* first formal parameter */
#define OBP_OFF 0 		/* dynamic chain */
#define RET_OFF 4 		/* ret address */
#define LOCAL_OFF 8 		/* local var */

#define MODIFIED 1
#define UNMODIFIED 0

/* register descriptor 寄存器描述符：
 * var: 当前寄存器绑定的符号（为空表示空闲）
 * mod: 是否已修改（需要在基本块边界或必要时写回）
 */
struct rdesc /* register descriptor */
{
	struct sym *var;
	int mod;
};

/* 代码生成阶段维护的全局状态
 * tos: 静态区已使用大小（为全局变量分配）
 * tof: 当前帧中局部变量分配到的顶部偏移
 * oof: 当前帧中形参的下一个分配偏移
 * oon: 调用过程中参数/返回信息的临时累计偏移
 */
extern int tos; /* top of static */
extern int tof; /* top of frame */
extern int oof; /* offset of formal */
extern int oon; /* offset of next frame */

/* 以当前 TAC 序列生成对象代码 */
void tac_obj();

