#include "main.h"
#include "bsp_clk.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_epit.h"
#include "bsp_keytimer.h"

int main(void)
{
	//int flag = 0;

	imx6u_clkinit();
	clk_enable();		/* 使能所有的时钟 			*/
	led_init();			/* 初始化led 			*/
	beep_init();
	key_init();
	int_init();
	keytimer_init(10);
	//init_epit(500);

	while(1)			/* 死循环 				*/
	{	
		delay(500);
	}

	return 0;
}
