#include "bsp_exti.h"
#include "bsp_int.h"

void setGpioInt(GPIO_Type* gpio,int pin,enum GPIO_INTTYPE type)
{
    unsigned int* icr = NULL;
    pin *= 2;
    if(pin > 31)
    {
        pin -= 32;
        icr = gpio->ICR2;
    }else
    {
        icr = gpio->ICR1;
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

void exti_init()
{
    //register_interrupt_handler()
}

void exti_handler(unsigned int int_id,void* param)
{

}