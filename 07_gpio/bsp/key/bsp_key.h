#ifndef BSP_KEY_H
#define BSP_KEY_H

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

/*
 * @description	: 初始化LED对应的GPIO
 * @param 		: 无
 * @return 		: 无
 */
void key_init(void);

/*
 * @description	: 打开LED灯
 * @param 		: 无
 * @return 		: 无
 */
int read_key(void);

/*
 * @description	: 关闭LED灯
 * @param 		: 无
 * @return 		: 无
 */
int get_key_value(void);

#endif // !BSP_KEY_H