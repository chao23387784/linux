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

void setGpioInt(GPIO_Type* gpio,int pin,enum GPIO_INTTYPE type)
{
    volatile unsigned int* icr = 0;
    pin *= 2;
    if(pin > 31)
    {
        pin -= 32;
        icr = &gpio->ICR2;
    }else
    {
        icr = &gpio->ICR1;
    }

    switch(type)
    {
        case GPIO_LOW_LEVEL:
        *icr &= ~(0x03 << pin);
        break;
        case GPIO_HIGH_LEVEL:
        *icr &= ~(0x03 << pin);
        *icr |= (0x01 << pin);
        break;
        case GPIO_RISING_EDGE:
        *icr &= ~(0x03 << pin);
        *icr |= (0x02 << pin);
        break;
        case GPIO_FALLING_EDGE:
        *icr |= (0x03 << pin);
        break;
        case GPIO_EDGE:
        pin /= 2;
        gpio->EDGE_SEL |= (0x01 << pin);
        break;
    }
}

void enableInt(GPIO_Type* gpio,int pin)
{
    gpio->IMR |= (1 << pin);
}

void disableInt(GPIO_Type* gpio,int pin)
{
    gpio->IMR &= ~(1 << pin);
}

void clearIntFlag(GPIO_Type* gpio,int pin)
{
    gpio->ISR |= (1 << pin);
}