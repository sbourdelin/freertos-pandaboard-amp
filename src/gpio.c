#include "board.h"
#include "common.h"
#include "gpio.h"

void gpio_direction_output(uint32_t gpio_bank, unsigned int gpio)
{
	BIT_CLEAR(GPIO_OE(gpio_bank), GPIO_ON_BANK(gpio));
}

void gpio_toggle(uint32_t gpio_bank, unsigned int gpio)
{
	gpio_direction_output(gpio_bank, GPIO_ON_BANK(gpio));
	BIT_TOGGLE(GPIO_DATAOUT(gpio_bank), GPIO_ON_BANK(gpio));
}

void gpio_irqenable(uint32_t gpio_bank, unsigned int gpio)
{
	/* enable gpio bank */
	BIT_CLEAR(GPIO_CTRL(gpio_bank), 0);

	/* triggering mode */
	BIT_SET(GPIO_RISINGDETECT(gpio_bank), GPIO_ON_BANK(gpio));
	BIT_SET(GPIO_FALLINGDETECT(gpio_bank), GPIO_ON_BANK(gpio));

	/* enable the irq waken mode */
	BIT_SET(GPIO_IRQ_WAKEN0(gpio_bank), GPIO_ON_BANK(gpio));

	/* enable the irq line */
	BIT_SET(GPIO_IRQ_STATUS_SET_0(IPU_GPIO2), GPIO_ON_BANK(33));
}

void gpio_irqclear(uint32_t gpio_bank, unsigned int gpio)
{
	/* disable the irq line */
	BIT_SET(GPIO_IRQ_STATUS_CLR_0(gpio_bank), GPIO_ON_BANK(gpio));

	/* ack the irq */
	BIT_SET(GPIO_IRQ_STATUS0(gpio_bank), GPIO_ON_BANK(gpio));

	/* enable the irq line */
	BIT_SET(GPIO_IRQ_STATUS_SET_0(IPU_GPIO2), GPIO_ON_BANK(33));
}
