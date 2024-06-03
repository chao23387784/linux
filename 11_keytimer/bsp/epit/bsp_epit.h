#ifndef BSP_EPIT_H
#define BSP_EPIT_H
#include "imx6u.h"

void init_epit(unsigned int milliseconds);
void epit_handler(unsigned int int_id,void* param);

#endif // BEP_EPIT_H