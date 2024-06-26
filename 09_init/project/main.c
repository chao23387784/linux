#include "main.h"
#include "bsp_clk.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_key.h"

int main(void)
{
	int flag = 0;

	imx6u_clkinit();
	clk_enable();		/* 使能所有的时钟 			*/
	led_init();			/* 初始化led 			*/
	beep_init();
	key_init();

	while(1)			/* 死循环 				*/
	{	
		if(get_key_value())
		{
			if(flag)
			{
				led_off();		/* 关闭LED 			*/
				beep_off();
			}else{
				led_on();		/* 打开LED 			*/
				beep_on();
			}
			flag = !flag;
		}
	}

	return 0;
}
