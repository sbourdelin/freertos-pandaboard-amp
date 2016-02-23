#include "board.h"
#include "gpio.h"

#define GPIO_LED1_POS	7
#define GPIO_LED2_POS	8

void led_toggle(unsigned int led)
{
	if (led >= 2)
		return;

	gpio_toggle(IPU_GPIO1, (led == 0) ? GPIO_LED1_POS : GPIO_LED2_POS);
}
