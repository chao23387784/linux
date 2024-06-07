#include "bsp_uart.h"

void uart_init()
{
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX,0);//iomuxc uart1_tx_data to uart1_tx
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX,0);//iomuxc uart1_rx_data to uart1_rx
    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX,0X10B0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX,0X10B0);

    UART1->UCR1 = 0;//claer uart1 state and disbale it

    UART1->UCR2 |= (1 << 1);//enable rx
    UART1->UCR2 |= (1 << 2);//enable tx
    UART1->UCR2 |= (1 << 5);//set 8bit data
    UART1->UCR2 &= ~(1 << 6);//set 1bit stop
    UART1->UCR2 &= ~(1 << 8);//disable parity check

    UART1->UFCR |= (5 << 7);//freq set devide by 1
    //set baudrate

    //init uart clk
    CCM->CSCDR1 &= ~(1 << 6);//select uart clk from 80MHz
    CCM->CSCDR1 &= ~(1 << 0);//set clk device by 1

    UART1->UCR1 |= (1 << 0);//enable uart1 
}

void putc(unsigned char c)
{
    UART1->UTXD = c;
}

void puts(unsigned char* s)
{
    unsigned char* p = s;
    while(*p != 0)
    {
        putc(*p);
        p++;
    }
}

unsigned char getc()
{
    unsigned char c = 0;
    while(!(UART1->URXD & (1 << 15)));
    c = (UART1->URXD & 0xff);
    return c;
}