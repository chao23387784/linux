#include "bsp_exti.h"
#include "bsp_int.h"
#include "bsp_gpio.h"

void exti_init()
{
    register_interrupt_handler(GPIO1_Combined_16_31_IRQn,exti_handler,0);
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);//enable interrupt signal
    enableInt(GPIO1,18);//enable interrupt slot
}

void exti_handler(unsigned int int_id,void* param)
{
    if(GPIO1_Combined_16_31_IRQn == int_id)
    {
        //finish int process
        clearIntFlag(GPIO1,18);
    }
}