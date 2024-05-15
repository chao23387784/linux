#ifndef BSP_GPIO_H
#define BSP_GPIO_H
#include "MCIMX6Y2.h"
#include "fsl_common.h"
#include "fsl_iomuxc.h"

enum GPIO_IOTYPE{
    GPIO_INPUT,
    GPIO_OUTPUT,
};

void setGpioConfig(GPIO_Type* gpio,int pin,enum GPIO_IOTYPE type,int value);

void writeGpioValue(GPIO_Type* gpio,int pin,int value);

int readGpioValue(GPIO_Type* gpio,int pin);

#endif // !BSP_GPIO_H