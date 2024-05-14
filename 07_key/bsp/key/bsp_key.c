#include "bsp_key.h"
#include "bsp_delay.h"

void key_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18,0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0XF080);
    GPIO1->GDIR &= ~(1<<18);
}

int read_key(void)
{
    if(GPIO1->DR & (1<<18))
    {
        return 1;
    }

    return 0;
}

int get_key_value(void)
{
    static unsigned char release = 1;

    if((release == 1) && (read_key() == 0))
    {
        delay(10);
        release = 0;
        if(read_key() == 0)
        {
            return 1;
        }
    }else if(read_key() == 1)
    {
        release = 1;
    }

    return 0;
}