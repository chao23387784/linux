/***************************************************************
Copyright © zuozhongkai Co., Ltd. 1998-2019. All rights reserved.
文件名	: 	 start.s
作者	   : 左忠凯
版本	   : V1.0
描述	   : ZERO-I.MX6UL/I.MX6ULL开发板启动文件，完成C环境初始化，
		 C环境初始化完成以后跳转到C代码。
其他	   : 无
日志	   : 初版 2019/1/3 左忠凯修改
**************************************************************/

.global _start  		/* 全局标号 */

/*
 * 描述：	_start函数，程序从此函数开始执行，此函数主要功能是设置C
 *		 运行环境。
 */
_start:
	ldr pc, = Reset_Handler
	ldr pc, = Undefined_Handler
	ldr pc, = SVC_Handler
	ldr pc, = PrefAbort_Handler
	ldr pc, = DataAbort_Handler
	ldr pc, = NotUsed_Handler
	ldr pc, = IRQ_Handler
	ldr pc, = FIQ_Handler

Reset_Handler:
	cpsid i /* disable Interrupt */

	mrc p15, 0, r0, c1, c0, 0 //read CP15 c1 to r0
	bic r0, r0, #(0x01 << 12) // close I Cache
	bic r0, r0, #(0x01 << 2) // close D Cache
	bic r0, r0, #0x02  // close alignment check
	bic r0, r0, #(0x01 << 11) // close branch prediction
	bic r0, r0, #0x01 // close MMU
	mcr p15, 0, r0, c1, c0, 0 //write r0 to CP15 c1

	ldr r0, = 0x87800000
	dsb
	isb
	mcr p15, 0, r0, c12, c0, 0//set interrupt vector address
	dsb
	isb

	/* enter IQR mode and init stack pointer */
	mrs r0, cpsr
	bic r0, r0, #0x1F
	orr r0, r0, #0x12
	msr cpsr, r0
	ldr sp,=0X80600000	/* 设置栈指针			 */

	/* enter FIQ mode and init stack pointer */
	mrs r0, cpsr
	bic r0, r0, #0x1F
	orr r0, r0, #0x11
	msr cpsr, r0
	ldr sp,=0X80400000	/* 设置栈指针			 */

	/* enter SVC mode and init stack pointer */
	mrs r0, cpsr
	bic r0, r0, #0x1F
	orr r0, r0, #0x13
	msr cpsr, r0
	ldr sp,=0X80200000	/* 设置栈指针			 */

	cpsie i //enable interrupt

	//enable IRQ 
	mrs r0, cpsr
	bic r0, r0, #(1<<7)
	msr cpsr, r0

	b main

Undefined_Handler:
	ldr r0, = Undefined_Handler
	bx r0
SVC_Handler:
	ldr r0, = SVC_Handler
	bx r0
PrefAbort_Handler:
	ldr r0, = PrefAbort_Handler
	bx r0
DataAbort_Handler:
	ldr r0, = DataAbort_Handler
	bx r0
NotUsed_Handler:
	ldr r0, = NotUsed_Handler
	bx r0
IRQ_Handler:
	push {lr} //save current address
	push {r0-r3, r12} //save common register data

	mrs r0, spsr //save cpsr data from spsr
	push {r0} 

	mrc p15, 4, r1, c15, c0, 0 //read CP15 c0 in c15 to r1
	add r1, r1, #0x2000 //get CPU interface base address (GIC base address + 0x2000)
	ldr r0, [r1, #0xC] //get GICC_IAR register ?
	push {r0, r1} //why push r0 and r1 ?

	cps #0x13 //enter SVC mode
	push {lr} // why push lr in SVC mode?
	ldr r2, = system_irqhandler
	blx r2
	pop {lr}
	cps #0x12 //enter IRQ mode

	pop {r0, r1}
	str r0, [r1, #0x10] //write EIOR ?

	pop {r0} //restore r0
	msr spsr_cxsf, r0 //restore spsr_cxsf?

	pop {r0-r3, r12}
	pop {lr}

	subs pc, lr, #4 // write lr back to pc and continue execute

FIQ_Handler:
	ldr r0, = FIQ_Handler
	bx r0

