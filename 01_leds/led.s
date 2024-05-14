.global _start /*global entry*/

_start:
/* enable all clock */
    ldr r0, = 0x020c4068 //CCGR0
    ldr r1, = 0xffffffff //data wait for write to clock registry
    str r1, [r0]         //write 0xffffff to 0x020c4068 registry

    ldr r0, = 0x020c406c //CCGR1
    str r1, [r0]         

    ldr r0, = 0x020c4070 //CCGR2
    str r1, [r0]         

    ldr r0, = 0x020c4074 //CCGR3
    str r1, [r0]         

    ldr r0, = 0x020c4078 //CCGR4
    str r1, [r0]         

    ldr r0, = 0x020c407c //CCGR5
    str r1, [r0]         

    ldr r0, = 0x020c4080 //CCGR6
    str r1, [r0]         

/* set GPIO1_IO03 mux
   IOMUXC_SW_MUX_CTL_PAD_GPIO3=5
   IOMUXC_SW_MUX_CTL_PAD_GPIO3 addr:0x020e0068
*/
    ldr r0, = 0x020e0068 //GPIO1_IO03
    ldr r1, = 0x5
    str r1, [r0]    

/* set GPIO1_IO03 pad 
   IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03
   bit 0 : 0 low rate
   bit 3-5 : 0b110 driver ability
   bit 6-7 : 0b10 100MHz
   bit 11 : 0 
   bit 12 : 1
   bit 13 : 0
   bit 14-15 : 00 100K pull
   bit 16 : 0 close hys
   IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 addr:0x020e02f4
*/  

    ldr r0, = 0x020e02f4
    ldr r1, = 0x10b0
    str r1, [r0]

/* set GPIO function 
   GPIO1_GDIR addr 0x0209c004 
   set GPIO_GDIR bit3 : 0b1
*/

    ldr r0, = 0x0209c004
    ldr r1, = 0x8
    str r1, [r0]

/* open LED
   GPIO1_DR addr 0x0209c000
*/

    ldr r0, = 0x0209c000
    ldr r1, = 0
    str r1, [r0]

loop:
    b loop
