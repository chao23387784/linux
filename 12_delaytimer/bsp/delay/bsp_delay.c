#include "bsp_delay.h"
#include "bsp_int.h"

void delay_init()
{
	GPT1->CR &= ~(0x01 << 0); //disable gpt clk

	GPT1->CR |= (0x01 << 15); //reset clk
	while(GPT1->CR >> 15 & 0x01); //wait reset complete

	GPT1->CR |= (0x01 << 0); //set counter to zero
	GPT1->CR |= (0x01 << 6); //set source clk
	GPT1->CR &= ~(0x01 << 9); //enable reset mode

	GPT1->PR &= ~(65 << 0); //divide by 66 (1 microsecond/tick)
	GPT1->IR |= (0x01 << 0); //enable compare 1

	GPT1->OCR[0] = 0xffffffff; //set compare 1 to max 

#if 0
	GIC_EnableIRQ(GPT1_IRQn);
	register_interrupt_handler(GPT1_IRQn,gpt_handler,NULL);
#endif
	GPT1->CR |= (0x01 << 0); //enable gpt clk
}

void delay_milliseconds(unsigned int milliseconds)
{
	unsigned int i = 0;
	for(i=0;i<milliseconds;i++)
	{
		delay_microseconds(1000);
	}
}

void delay_microseconds(unsigned int microseconds)
{
	unsigned int tick1 = GPT1->CNT;
	while(1)
	{
		unsigned int tick2 = GPT1->CNT;
		unsigned int tick = 0;
		if(tick2 > tick1)
		{
			tick = tick2 - tick1;
		}else
		{
			tick = 0xffffffff - tick1 + tick2;
		}

		if(tick >= microseconds)
		{
			break;
		}
	}
}

#if 0
void gpt_handler(unsigned int int_id,void* param)
{
	if(int_id == GPT1_IRQn)
	{
		tick++;
		GPT1->SR |= (0x01 << 0); //clear compare1 flag
	}
}
#endif

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