#include "bsp_gpio.h"

void setGpioConfig(GPIO_Type* gpio,int pin,enum GPIO_IOTYPE type,int value)
{
    if(gpio)
    {
        switch(type)
        {
            case GPIO_INPUT:
            {
                gpio->GDIR &= ~(1<<pin);
            }
            break;
            case GPIO_OUTPUT:
            {
                gpio->GDIR |= (1<<pin);
                writeGpioValue(gpio,pin,value);
            }
            break;
        }
    }
}

void writeGpioValue(GPIO_Type* gpio,int pin,int value)
{
    if(gpio && (gpio->GDIR & (1<<pin)))
    {
        if(value)
        {
            gpio->DR |= (1<<pin);
        }else
        {
            gpio->DR &= ~(1<<pin);
        }
    }
}

int readGpioValue(GPIO_Type* gpio,int pin)
{
    return (gpio->DR >> pin & 0x01);
}