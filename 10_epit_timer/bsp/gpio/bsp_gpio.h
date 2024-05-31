#ifndef BSP_GPIO_H
#define BSP_GPIO_H
#include "imx6u.h"

enum GPIO_IOTYPE{
    GPIO_INPUT,
    GPIO_OUTPUT,
};

enum GPIO_INTTYPE{
    GPIO_LOW_LEVEL,
    GPIO_HIGH_LEVEL,
    GPIO_RISING_EDGE,
    GPIO_FALLING_EDGE,
    GPIO_EDGE
};

void setGpioConfig(GPIO_Type* gpio,int pin,enum GPIO_IOTYPE type,int value);

void writeGpioValue(GPIO_Type* gpio,int pin,int value);

int readGpioValue(GPIO_Type* gpio,int pin);

void setGpioInt(GPIO_Type* gpio,int pin,enum GPIO_INTTYPE type);

void enableInt(GPIO_Type* gpio,int pin);

void disableInt(GPIO_Type* gpio,int pin);

void clearIntFlag(GPIO_Type* gpio,int pin);

#endif // !BSP_GPIO_H