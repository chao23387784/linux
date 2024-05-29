#ifndef BSP_INT_H
#define BSP_INT_H
#include "imx6u.h"

typedef void(*int_handler)(unsigned int int_id,void* param);
typedef struct
{
    int_handler handler;
    void* param;
}int_info;

int_info int_table[NUMBER_OF_INT_VECTORS];

void int_init(void);
void default_int_hander(unsigned int gicc_iar,void* param);
void init_inttable();
void register_interrupt_handler(IRQn_Type type,int_handler handler,void* param);
void system_irqhandler(unsigned int gicc_iar);

#endif // !BSP_INT_H