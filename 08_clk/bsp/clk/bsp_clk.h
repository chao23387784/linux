#ifndef BSP_CLK_H
#define BSP_CLK_H
#include "MCIMX6Y2.h"

/*
 * @description	: 使能I.MX6U所有外设时钟
 * @param 		: 无
 * @return 		: 无
 */
void clk_enable(void);
void imx6u_clkinit();

#endif // !BSP_CLK_H