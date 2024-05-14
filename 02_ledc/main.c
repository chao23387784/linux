#include "main.h"

void init_clock()
{
    CCM_CCGR0 = 0xffffffff;
    CCM_CCGR1 = 0xffffffff;
    CCM_CCGR2 = 0xffffffff;
    CCM_CCGR3 = 0xffffffff;
    CCM_CCGR4 = 0xffffffff;
    CCM_CCGR5 = 0xffffffff;
    CCM_CCGR6 = 0xffffffff;
}

void init_gpio()
{
    SW_MUX_GPIO1_IO03 = 0x05;
    SW_PAD_GPIO1_IO03 = 0x10B0;

    GPIO1_GDIR = 0x08;
    GPIO1_DR = 0X00;
}

void led_on()
{
    GPIO1_DR &= ~(0x01<<3);
}

void led_off()
{
    GPIO1_DR |= (0x01<<3);
}

void delay_short(volatile unsigned int n)
{
    while(n--){}
}

void delay(volatile unsigned int n)
{
    while(n--)
    {
        delay_short(0x7ff);
    }
}

int main(void)
{
    init_clock();
    init_gpio();

    while(1)
    {
        led_off();
        delay(500);

        led_on();
        delay(500);
    }

    return 0;
}