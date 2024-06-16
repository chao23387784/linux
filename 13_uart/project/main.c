#include "main.h"
#include "bsp_clk.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_epit.h"
#include "bsp_keytimer.h"
#include "bsp_uart.h"
#include "stdio.h"

int main(void)
{
	//int flag = 0;
	//unsigned char a = 0;
	int a,b;

	imx6u_clkinit();
	clk_enable();		/* 使能所有的时钟 			*/
	led_init();			/* 初始化led 			*/
	beep_init();
	key_init();
	delay_init();
	int_init();
	//keytimer_init(10);
	//init_epit(500);
	uart_init();

	beep_off();
	while(1)			/* 死循环 				*/
	{	
		/*puts("请输入1个字符:");
		a = getc();
		putc(a);
		puts("\r\n");

		puts("您输入的字符是:");
		putc(a);
		puts("\r\n\r\n");*/
		printf("输入两个整数，使用空格隔开:");
		scanf("%d %d",&a,&b);
		printf("\r\n数据%d + %d = %d\r\n\r\n",a,b,a+b);
		//delay_milliseconds(500);
	}

	return 0;
}
