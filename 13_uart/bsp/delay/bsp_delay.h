#ifndef BSP_DELAY_H
#define BSP_DELAY_H
#include "imx6u.h"

void delay_init();
void delay_milliseconds(unsigned int milliseconds);
void delay_microseconds(unsigned int microseconds);
//void gpt_handler(unsigned int int_id,void* param);
void delay_short(volatile unsigned int n);
void delay(volatile unsigned int n);

#endif // !BSP_DELAY_H
