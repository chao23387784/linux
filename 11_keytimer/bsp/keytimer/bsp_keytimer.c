#include "bsp_keytimer.h"
#include "bsp_int.h"
#include "bsp_gpio.h"
#include "bsp_key.h"
#include "bsp_beep.h"
#include "bsp_led.h"

void keytimer_init(unsigned int milliseconds)
{
    EPIT1->CR = 0; //disable EPIT interrupt
    EPIT1->CR |= (0x01 << 1); //enable set value from RLD
    EPIT1->CR |= (0x01 << 2); //enable compare
    EPIT1->CR |= (0x01 << 3); //set and forget mode
    EPIT1->CR |= (0x01 << 24); //set clk source from Peripheral 66MHz

    unsigned int tickPerMilliSec = 66*1000*1000/1000;
    unsigned int tickPerPeriod = tickPerMilliSec * milliseconds;
    EPIT1->LR = tickPerPeriod; //set load value to tickPerPeriod
    EPIT1->CMPR = 0; //set compare value to 0

    register_interrupt_handler(EPIT1_IRQn,keytimer_handler,NULL);
    GIC_EnableIRQ(EPIT1_IRQn); //enable clk signal
    //EPIT1->CR |= (0x01 << 0); //enable clk slot


    register_interrupt_handler(GPIO1_Combined_16_31_IRQn,keyint_handler,NULL);
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);//enable interrupt signal
    enableInt(GPIO1,18);//enable interrupt slot
}

void keytimer_handler(unsigned int int_id,void* param)
{
    if(int_id == EPIT1_IRQn)
    {
        static unsigned int state = 1;
        stop_timer();
        if(read_key() == 0)
        {
            state = !state;
            if(state)
            {
                led_on();
                beep_on();
            }else
            {
                led_off();
                beep_off();
            }
        }
        EPIT1->SR |= (1 << 0);//clear int flag of epit
    }
}

void keyint_handler(unsigned int int_id,void* param)
{
    if(int_id == GPIO1_Combined_16_31_IRQn)
    {
        //if(read_key() == 0)
        //{
        restart_timer();
        //}
        clearIntFlag(GPIO1,18);
    }
}

void restart_timer()
{
    EPIT1->CR &= ~(0x01 << 0);//disable clk slot
    //EPIT1->CNR = EPIT1->LR;//reset count
    unsigned int tickPerMilliSec = 66*1000*1000/1000;
    unsigned int tickPerPeriod = tickPerMilliSec * 10;
    EPIT1->LR = tickPerPeriod; //set load value to tickPerPeriod
    EPIT1->CR |= (0x01 << 0); //enable clk slot
}

void stop_timer()
{
    EPIT1->CR &= ~(0x01 << 0); //disable clk slot
}