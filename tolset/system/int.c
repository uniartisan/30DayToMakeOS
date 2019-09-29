#include "bootpack.h"
/*
	设定PIC 可编程中断控制器
	从PIC通过IRQ-2连接主PIC
	IMR 是中断屏蔽寄存器, 用来屏蔽IRQ信号
	ICW 1 和ICW 4 声明了主板配线方式
	ICW 3 是主从设定, 表示触发器的哪一位连着从触发器;(一般是IRQ2)
	ICW 2 决定IRQ以哪一个中断号通知CPU, INT 0x0~0x19 不能被使用
*/

void init_pic(void)
{
	io_out8(PIC0_IMR, 0xff);			/*禁止主PIC所有中断*/
	io_out8(PIC0_IMR, 0xff);			/*禁止从PIC所有中断*/

	io_out8(PIC0_ICW1, 0x11);			/* 边缘触发模式（edge trigger mode） */
	io_out8(PIC0_ICW2, 0x20);			/* IRQ0-7由INT20-27接收 */
	io_out8(PIC0_ICW3, 1 << 2);			/* PIC1由IRQ2相连 */
	io_out8(PIC0_ICW4, 0x01);			/* 无缓冲区模式 */

	io_out8(PIC1_ICW1, 0x11);			/* 边缘触发模式（edge trigger mode） */
	io_out8(PIC1_ICW2, 0x28);			/* IRQ8-15由INT28-2f接收 */
	io_out8(PIC1_ICW3, 2);				/* PIC1由IRQ2连接 */
	io_out8(PIC1_ICW4, 0x01);			/* 无缓冲区模式 */

	io_out8(PIC0_IMR, 0xfb);			/* 11111011 PIC1以外全部禁止 */
	io_out8(PIC1_IMR, 0xff);			/* 11111111 禁止所有中断*/

	return;
}

#define PORT_KEYDAT		0x0060

void inthandler27(int* esp)
/* PIC0中断的不完整策略 */
/* 历史遗留问题 */

{
	io_out8(PIC0_OCW2, 0x67);
	return;
}