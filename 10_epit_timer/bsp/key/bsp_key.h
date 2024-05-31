#ifndef BSP_KEY_H
#define BSP_KEY_H
#include "imx6u.h"

void key_init(void);
int read_key(void);
int get_key_value(void);

#endif // !BSP_KEY_H