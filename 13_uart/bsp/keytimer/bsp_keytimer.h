#ifndef BSP_KEYTIMER_H
#define BSP_KEYTIMER_H
#include "imx6u.h"

void keytimer_init(unsigned int milliseconds);
void keytimer_handler(unsigned int int_id,void* param);
void keyint_handler(unsigned int int_id,void* param);
void restart_timer();
void stop_timer();

#endif // !BSP_KEYTIMER_H
