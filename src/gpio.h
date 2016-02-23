#ifndef __GPIO_H
#define __GPIO_H

#define GPIO_ON_BANK(x)			(x & 0x1F)

#define GPIO_OE(x)			(x + 0x134)
#define GPIO_DATAOUT(x)			(x + 0x13c)
#define GPIO_IRQ_STATUS0(x)		(x + 0x2c)
#define GPIO_IRQ_STATUS1(x)		(x + 0x30)
#define GPIO_IRQ_ENABLE1(x)		(x + 0x11c)
#define GPIO_IRQ_ENABLE2(x)		(x + 0x12c)
#define GPIO_IRQ_WAKEN0(x)		(x + 0x44)
#define GPIO_IRQ_WAKEN1(x)		(x + 0x48)
#define GPIO_RISINGDETECT(x)		(x + 0x148)
#define GPIO_FALLINGDETECT(x)		(x + 0x14c)
#define GPIO_IRQ_STATUS_SET_0(x)	(x + 0x34)
#define GPIO_IRQ_STATUS_CLR_0(x)	(x + 0x3C)
#define GPIO_CTRL(x)			(x + 0x130)

void gpio_direction_output(uint32_t, unsigned int);
void gpio_toggle(uint32_t, unsigned int);
void gpio_irqenable(uint32_t, unsigned int);
void gpio_irqclear(uint32_t, unsigned int);

#endif
