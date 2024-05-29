#include "bsp_int.h"

void int_init(void)
{
    GIC_Init();
    init_inttable();
    __set_VBAR(0x87800000);//set interrupt vector address
}

void default_int_hander(unsigned int gicc_iar,void* param)
{
    while(1){}
}

void init_inttable()
{
    int i = 0;
    for(i=0;i<NUMBER_OF_INT_VECTORS;i++)
    {
        int_table[i].handler = default_int_hander;
        int_table[i].param = NULL;
    }
}

void register_interrupt_handler(IRQn_Type type,int_handler handler,void* param)
{
    if(type < NUMBER_OF_INT_VECTORS)
    {
        int_table[type].handler = handler;
        int_table[type].param = param;
    }
}

void system_irqhandler(unsigned int gicc_iar)
{
    unsigned int interrupt_id =  (gicc_iar & 0x3FF);
    if(interrupt_id < NUMBER_OF_INT_VECTORS)
    {
        int_table[interrupt_id].handler(interrupt_id,int_table[interrupt_id].param);
    }
}