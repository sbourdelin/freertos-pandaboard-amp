#ifndef __INTERRUPT_H
#define __INTERRUPT_H

#define NVIC_SET_ENABLE_REG	0xE000E100
#define NVIC_CLEAR_PENDING_REG	0xE000E280

#define NVIC_GPIO2_MPU_IRQ	36

void nvic_irqenable(unsigned int irq);
void nvic_irqclear(unsigned int irq);

#endif
