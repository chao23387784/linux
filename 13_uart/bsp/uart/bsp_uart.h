#ifndef BSP_UART_H
#define BSP_UART_H
#include "imx6u.h"

void uart_init();
void uart_setbaudrate(UART_Type *base, unsigned int baudrate, unsigned int srcclock_hz);
void putc(unsigned char c);
void puts(unsigned char* s);
unsigned char getc();
void raise(int sig_nr);

#endif // !BSP_UART_H
