#include "common.h"
#include "nvic.h"

static void nvic_set(unsigned int reg, unsigned int irq)
{
	if (irq > 31) {
		reg += 0x4;
		irq -= 32;
	}

	BIT_SET((reg), (irq));
}

void nvic_irqenable(unsigned int irq)
{
	nvic_set(NVIC_SET_ENABLE_REG, irq);
}

void nvic_irqclear(unsigned int irq)
{
	nvic_set(NVIC_CLEAR_PENDING_REG, irq);
}
