#include "board.h"
#include "gpio.h"
#include "led.h"

#define DEFAULT_SLEEP 500000

void sleep(unsigned int s)
{
	volatile int i;

	if (s == 0)
		s = DEFAULT_SLEEP;

	for (i = 0; i < s; i++)
		asm volatile ("nop");
}

void debug_blink(int led)
{
	volatile int i;

	if (led >= 2)
		return;

	for (i = 0; i < 2; i++) {
		led_toggle(led);
		sleep(0);
	}
}
