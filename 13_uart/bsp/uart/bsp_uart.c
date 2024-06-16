#include "bsp_uart.h"
#include "imx6u.h"

void uart_init()
{
    IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX,0);//iomuxc uart1_tx_data to uart1_tx
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX,0);//iomuxc uart1_rx_data to uart1_rx
    IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX,0X10B0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX,0X10B0);

    UART1->UCR1 = 0;//claer uart1 state and disbale it

    UART1->UCR2 &= ~(0x01 << 0);//reset uart1
    while(!(UART1->UCR2 & 0x01));//wait for uart1 reset complete

    UART1->UCR2 |= (1 << 1);//enable rx
    UART1->UCR2 |= (1 << 2);//enable tx
    UART1->UCR2 |= (1 << 5);//set 8bit data
    UART1->UCR2 &= ~(1 << 6);//set 1bit stop
    UART1->UCR2 &= ~(1 << 8);//disable parity check
    UART1->UCR2 |= (1 << 14);//ignore RTS ??

    UART1->UCR3 |= (1 << 2);

    UART1->UFCR |= (5 << 7);//freq set devide by 1
    //set baudrate
    //UART1->UBIR = 73;
    //UART1->UBMR = 3124;
    uart_setbaudrate(UART1,115200,80000000);

    //init uart clk
    CCM->CSCDR1 &= ~(1 << 6);//select uart clk from 80MHz
    CCM->CSCDR1 &= ~(1 << 0);//set clk device by 1

    UART1->UCR1 |= (1 << 0);//enable uart1 
}

void uart_setbaudrate(UART_Type *base, unsigned int baudrate, unsigned int srcclock_hz)
{
    uint32_t numerator = 0u;		//分子
    uint32_t denominator = 0U;		//分母
    uint32_t divisor = 0U;
    uint32_t refFreqDiv = 0U;
    uint32_t divider = 1U;
    uint64_t baudDiff = 0U;
    uint64_t tempNumerator = 0U;
    uint32_t tempDenominator = 0u;

    /* get the approximately maximum divisor */
    numerator = srcclock_hz;
    denominator = baudrate << 4;
    divisor = 1;

    while (denominator != 0)
    {
        divisor = denominator;
        denominator = numerator % denominator;
        numerator = divisor;
    }

    numerator = srcclock_hz / divisor;
    denominator = (baudrate << 4) / divisor;

    /* numerator ranges from 1 ~ 7 * 64k */
    /* denominator ranges from 1 ~ 64k */
    if ((numerator > (UART_UBIR_INC_MASK * 7)) || (denominator > UART_UBIR_INC_MASK))
    {
        uint32_t m = (numerator - 1) / (UART_UBIR_INC_MASK * 7) + 1;
        uint32_t n = (denominator - 1) / UART_UBIR_INC_MASK + 1;
        uint32_t max = m > n ? m : n;
        numerator /= max;
        denominator /= max;
        if (0 == numerator)
        {
            numerator = 1;
        }
        if (0 == denominator)
        {
            denominator = 1;
        }
    }
    divider = (numerator - 1) / UART_UBIR_INC_MASK + 1;

    switch (divider)
    {
        case 1:
            refFreqDiv = 0x05;
            break;
        case 2:
            refFreqDiv = 0x04;
            break;
        case 3:
            refFreqDiv = 0x03;
            break;
        case 4:
            refFreqDiv = 0x02;
            break;
        case 5:
            refFreqDiv = 0x01;
            break;
        case 6:
            refFreqDiv = 0x00;
            break;
        case 7:
            refFreqDiv = 0x06;
            break;
        default:
            refFreqDiv = 0x05;
            break;
    }
    /* Compare the difference between baudRate_Bps and calculated baud rate.
     * Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1)).
     * baudDiff = (srcClock_Hz/divider)/( 16 * ((numerator / divider)/ denominator).
     */
    tempNumerator = srcclock_hz;
    tempDenominator = (numerator << 4);
    divisor = 1;
    /* get the approximately maximum divisor */
    while (tempDenominator != 0)
    {
        divisor = tempDenominator;
        tempDenominator = tempNumerator % tempDenominator;
        tempNumerator = divisor;
    }
    tempNumerator = srcclock_hz / divisor;
    tempDenominator = (numerator << 4) / divisor;
    baudDiff = (tempNumerator * denominator) / tempDenominator;
    baudDiff = (baudDiff >= baudrate) ? (baudDiff - baudrate) : (baudrate - baudDiff);

    if (baudDiff < (baudrate / 100) * 3)
    {
        base->UFCR &= ~UART_UFCR_RFDIV_MASK;
        base->UFCR |= UART_UFCR_RFDIV(refFreqDiv);
        base->UBIR = UART_UBIR_INC(denominator - 1); //要先写UBIR寄存器，然后在写UBMR寄存器，3592页 
        base->UBMR = UART_UBMR_MOD(numerator / divider - 1);
    }
}

void putc(unsigned char c)
{
    while(!(UART1->USR2 & 0x08));//wait for transmit complete
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
    while(!(UART1->USR2 & 0x01));//wait for received ready
    c = (UART1->URXD & 0xff);
    return c;
}

void raise(int sig_nr)
{

}