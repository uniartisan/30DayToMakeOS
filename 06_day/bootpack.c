#include <stdio.h>										//引入sprintf函数
#include "bootpack.h"


void HariMain(void)
{
	struct BOOTINFO* binfo = (struct BOOTINFO*) 0x0ff0;
	char s[40], mcursor[256];
	int mx, my;
	/*组件剥离*/
	init_gdtidt();
	init_pic();
	io_sti(); 
	/* IDT/PIC的初始化已经完成，于是开放CPU的中断 */


	init_palette();												/* 设定调色板 */
	init_screen(binfo->vram, binfo->scrnx, binfo->scrny);		//定义桌面背景
	mx = (binfo->scrnx - 16) / 2; /* 计算画面的中心坐标*/
	my = (binfo->scrny - 28 - 16) / 2;
	init_mouse_cursor8(mcursor, COL8_008484);
	putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
	sprintf(s, "(%d, %d)", mx, my);
	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);		//函数值调试输出 
	putfonts8_asc(binfo->vram, binfo->scrnx, 31, 31, COL8_000000, "HarmonicOS.");
	putfonts8_asc(binfo->vram, binfo->scrnx, 30, 30, COL8_FFFFFF, "HarmonicOS.");

	io_out8(PIC0_IMR, 0xf9); /* 开放PIC1和键盘中断(11111001) */
	io_out8(PIC1_IMR, 0xef); /* 开放鼠标中断(11101111) */

	for (;;) {
		io_hlt();
	}
}

