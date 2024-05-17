#ifndef BSP_LED_H
#define BSP_LED_H
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

/*
 * @description	: 初始化LED对应的GPIO
 * @param 		: 无
 * @return 		: 无
 */
void led_init(void);

/*
 * @description	: 打开LED灯
 * @param 		: 无
 * @return 		: 无
 */
void led_on(void);

/*
 * @description	: 关闭LED灯
 * @param 		: 无
 * @return 		: 无
 */
void led_off(void);

#endif // !BSP_LED_H
