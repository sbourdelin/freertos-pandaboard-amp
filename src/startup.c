#include <stdint.h>
#include "board.h"
#include "gpio.h"
#include "led.h"

/* Forward declaration of the default CORTEX-M3 fault handlers. */
void ResetISR(void);
static void NmiISR(void);
static void FaultISR(void);
static void DefaultISR(void);
static void GPIO2_ISR(void);
extern void xPortPendSVHandler(void);
extern void xPortSysTickHandler(void);
extern void vPortSVCHandler(void);

/* Application Entry point */
extern int main(void);

/* Reserve space for the system stack */
#ifndef STACK_SIZE
#define STACK_SIZE 64
#endif
static unsigned long pulStack[STACK_SIZE];

/*
 * Interrupt Vector table for CORTEX-M3 on OMAP4430.
 * This relies on the linker script to place this vector at the correct location
 * in memory which is expected to be at physical address 0x00000000.
 * The exception vector are part of the CORTEX-M3 TRM.
 * The external interrupt vector are part of the OMAP4430 TRM.
 */
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
	/* Exception vector */
	(void (*)(void))((unsigned long)pulStack + sizeof(pulStack)),
					/* The initial stack pointer */
	ResetISR,			/* The reset handler */
	NmiISR,				/* The NMI handler */
	FaultISR,			/* The hard fault handler */
	DefaultISR,			/* The MPU fault handler */
	DefaultISR,			/* The bus fault handler */
	DefaultISR,			/* The usage fault handler */
	0,				/* Reserved */
	0,				/* Reserved */
	0,				/* Reserved */
	0,				/* Reserved */
	vPortSVCHandler,		/* SVCall handler */
	DefaultISR,			/* Debug monitor handler */
	0,				/* Reserved */
	xPortPendSVHandler,		/* The PendSV handler */
	xPortSysTickHandler,		/* The SysTick handler */

	/* External interrupt vector */
	DefaultISR,			/* IRQ #0 */
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,			/* IRQ #10 */
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,			/* IRQ #20 */
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,			/* IRQ #30 */
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	GPIO2_ISR,			/* IRQ #36 */
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR			/* IRQ #40 */
};

/* The following are segments created by the linker script. */
extern unsigned long _text;	/* start of text segment */
extern unsigned long _etext;	/* end of text segment */
extern unsigned long _data;	/* start of data segment */
extern unsigned long _edata;	/* end of data segment */
extern unsigned long _bss;	/* start of bss segment */
extern unsigned long _ebss;	/* end of bss segment */

/* This is the first instructions execute by the processor following a reset
 * event. */
void ResetISR(void)
{
	volatile uint32_t *PID0_REG = ((uint32_t *)IPU_PID0_REG);
	unsigned long *pulDest;

	/* If we are core1, go to sleep.
	 * Thanks to guillaume aubertin:
	 * https://github.com/g-aubertin/ducati_FreeRTOS */
	if (*PID0_REG != 0) {
		asm volatile ("wfi");
	}

	/* The bss segment contains all the unitialize known variables (eg:
	 * dynamic allocated variable will be stored in the heap).
	 * This space is actually reserved by the executable loader and are not
	 * stored in the object file to save space.
	 * We should zero fill the bss segment */
	for (pulDest = &_bss; pulDest != &_ebss; pulDest++) {
	    *pulDest = 0;
	}

	/* Finally call the application's entry point. */
	main();
}

/* This is the code that gets called when the processor receives a non-masquable
 * interrupt (MMI). */
static void NmiISR(void)
{
	while (1) {
	}
}

/* This is the code that gets called when the processor receives a fault
 * interrupt. */
static void FaultISR(void)
{
	while (1) {
	}
}

/* This is the code that gets called when the processor receives an unexpected
 * interrupt. */
static void DefaultISR(void)
{
	while (1) {
	}
}

/* This is the code that gets called when the GPIO2 MPU IRQ line is trigger */
static void GPIO2_ISR(void)
{
	/* toggle the output gpio for measure */
	gpio_toggle(IPU_GPIO2, GPIO_TO_TOGGLE);

	/* toggle the led for visual output */
	led_toggle(0);

	/* ack the IRQ */
	gpio_irqclear(IPU_GPIO2, GPIO_USED_FOR_IRQ);
}
