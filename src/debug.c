#include <string.h>
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

char *trace_buf = (char *)IPU_MEM_TRACE_BASE;
void debug_trace(const char *const msg)
{
	unsigned int len;

	len = strlen(msg);

	/* simply reset the trace buffer position when the size exceed the
	 * buffer size, a more sophisticated solution like log rotatation could
	 * be imagine. */
	if (((unsigned int)trace_buf + len) > (IPU_MEM_TRACE_BASE +
			IPU_MEM_TRACE_SIZE))
		trace_buf = (char *)IPU_MEM_TRACE_BASE;

	strncpy(trace_buf, msg, len);
	trace_buf += len;
}
