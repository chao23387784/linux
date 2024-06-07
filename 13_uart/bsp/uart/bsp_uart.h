#ifndef BSP_UART_H
#define BSP_UART_H
#include "imx6u.h"

void uart_init();
void putc(unsigned char c);
void puts(unsigned char* s);
unsigned char getc();

#endif // !BSP_UART_H
