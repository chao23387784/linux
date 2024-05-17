#ifndef BSP_BEEP_H
#define BSP_BEEP_H
#include "MCIMX6Y2.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"

void beep_init(void);

/*
 * @description	: 打开LED灯
 * @param 		: 无
 * @return 		: 无
 */
void beep_on(void);

/*
 * @description	: 关闭LED灯
 * @param 		: 无
 * @return 		: 无
 */
void beep_off(void);

#endif // !BSP_BEEP_H