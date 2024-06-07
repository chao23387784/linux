#include "bsp_led.h"
#include "bsp_gpio.h"

void led_init(void)
{
	/* 1、初始化IO复用 */
	IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);		/* 复用为GPIO1_IO0 */

	/* 2、、配置GPIO1_IO03的IO属性	
	 *bit 16:0 HYS关闭
	 *bit [15:14]: 00 默认下拉
     *bit [13]: 0 kepper功能
     *bit [12]: 1 pull/keeper使能
     *bit [11]: 0 关闭开路输出
     *bit [7:6]: 10 速度100Mhz
     *bit [5:3]: 110 R0/6驱动能力
     *bit [0]: 0 低转换率
     */
	IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0X10B0);

	/* 3、初始化GPIO,设置GPIO1_IO03设置为输出  */
	/* 4、设置GPIO1_IO03输出低电平，打开LED0 */
	setGpioConfig(GPIO1,3,GPIO_OUTPUT,0);		
}

void led_on(void)
{
	/* 将GPIO1_DR的bit3清零 	*/
	writeGpioValue(GPIO1,3,0);
}

void led_off(void)
{
	/* 将GPIO1_DR的bit3置1 */
	writeGpioValue(GPIO1,3,1);
}