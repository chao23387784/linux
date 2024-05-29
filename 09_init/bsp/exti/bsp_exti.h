#ifndef BSP_EXTI_H
#define BSP_EXTI_H
#include "imx6u.h"

enum GPIO_INTTYPE{
    GPIO_LOW_LEVEL,
    GPIO_HIGH_LEVEL,
    GPIO_RISING_EDGE,
    GPIO_FALLING_EDGE,
    GPIO_EDGE
};

void setGpioInt(GPIO_Type* gpio,int pin,enum GPIO_INTTYPE type);
void exti_init();
void exti_handler(unsigned int int_id,void* param);

#endif // !BSP_EXTI_H