#include "bsp_beep.h"
#include "bsp_gpio.h"

void beep_init(void)
{
    /* 1、初始化IO复用 */
	IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0);		/* 复用为GPIO5_IO01 */

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
	IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01,0X10B0);

    setGpioConfig(GPIO5,1,GPIO_OUTPUT,0);
}

void beep_on(void)
{
    writeGpioValue(GPIO5,1,0);
}

void beep_off(void)
{
    writeGpioValue(GPIO5,1,1);
}