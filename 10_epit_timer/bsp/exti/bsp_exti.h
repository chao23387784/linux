#ifndef BSP_EXTI_H
#define BSP_EXTI_H
#include "imx6u.h"

void exti_init();
void exti_handler(unsigned int int_id,void* param);

#endif // !BSP_EXTI_H