#include "bootpack.h"
/*
	�趨PIC �ɱ���жϿ�����
	��PICͨ��IRQ-2������PIC
	IMR ���ж����μĴ���, ��������IRQ�ź�
	ICW 1 ��ICW 4 �������������߷�ʽ
	ICW 3 �������趨, ��ʾ����������һλ���ŴӴ�����;(һ����IRQ2)
	ICW 2 ����IRQ����һ���жϺ�֪ͨCPU, INT 0x0~0x19 ���ܱ�ʹ��
*/

void init_pic(void)
{
	io_out8(PIC0_IMR, 0xff);			/*��ֹ��PIC�����ж�*/
	io_out8(PIC0_IMR, 0xff);			/*��ֹ��PIC�����ж�*/

	io_out8(PIC0_ICW1, 0x11);			/* ��Ե����ģʽ��edge trigger mode�� */
	io_out8(PIC0_ICW2, 0x20);			/* IRQ0-7��INT20-27���� */
	io_out8(PIC0_ICW3, 1 << 2);			/* PIC1��IRQ2���� */
	io_out8(PIC0_ICW4, 0x01);			/* �޻�����ģʽ */

	io_out8(PIC1_ICW1, 0x11);			/* ��Ե����ģʽ��edge trigger mode�� */
	io_out8(PIC1_ICW2, 0x28);			/* IRQ8-15��INT28-2f���� */
	io_out8(PIC1_ICW3, 2);				/* PIC1��IRQ2���� */
	io_out8(PIC1_ICW4, 0x01);			/* �޻�����ģʽ */

	io_out8(PIC0_IMR, 0xfb);			/* 11111011 PIC1����ȫ����ֹ */
	io_out8(PIC1_IMR, 0xff);			/* 11111111 ��ֹ�����ж�*/

	return;
}


void inthandler21(int* esp)
/* ����PS/2���̵��ж� */
{
	struct BOOTINFO* binfo = (struct BOOTINFO*) ADR_BOOTINFO;
	boxfill8(binfo->vram, binfo->scrnx, COL8_000000, 0, 0, 32 * 8 - 1, 15);
	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, "INT 21 (IRQ-1) : PS/2 keyboard");
	for (;;) {
		io_hlt();
	}
}

void inthandler2c(int* esp)
/* ����PS/2�����ж� */
{
	struct BOOTINFO* binfo = (struct BOOTINFO*) ADR_BOOTINFO;
	boxfill8(binfo->vram, binfo->scrnx, COL8_000000, 0, 0, 32 * 8 - 1, 15);
	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, "INT 2C (IRQ-12) : PS/2 mouse");
	for (;;) {
		io_hlt();
	}
}

void inthandler27(int* esp)
/* PIC0�жϵĲ��������� */
/* ��ʷ�������� */

{
	io_out8(PIC0_OCW2, 0x67); 
	return;
}
