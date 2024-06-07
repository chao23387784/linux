#include "bsp_epit.h"
#include "bsp_int.h"
#include "bsp_led.h"
#include "bsp_beep.h"

void init_epit(unsigned int milliseconds)
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

    register_interrupt_handler(EPIT1_IRQn,epit_handler,NULL);
    GIC_EnableIRQ(EPIT1_IRQn); //enable clk signal
    EPIT1->CR |= (0x01 << 0); //enable clk slot
}

void epit_handler(unsigned int int_id,void* param)
{
    if(int_id != EPIT1_IRQn)
    {
        return;
    }
    
    static unsigned char state = 1;
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

    EPIT1->SR |= (1 << 0);
}