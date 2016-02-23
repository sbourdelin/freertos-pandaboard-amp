#include <stdint.h>
#include "board.h"
#include "debug.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "gpio.h"
#include "led.h"
#include "nvic.h"
#include "task.h"

static void heartbeat(void *Parameters)
{
	/* change GPIO_LED2 state */
	while (1) {
		led_toggle(1);
		vTaskDelay(1000);
	}
}

int main()
{
	/* enable the GPIO2 irq in the NVIC */
	nvic_irqenable(NVIC_GPIO2_MPU_IRQ);

	/* enable the GPIO2 irq to be trigger by our specific GPIO */
	gpio_irqenable(IPU_GPIO2, GPIO_USED_FOR_IRQ);

	/* Create a FreeRTOS task which will toggle a led */
	xTaskCreate(heartbeat, "heartbeat", 1024, NULL, tskIDLE_PRIORITY + 1, NULL);
	vTaskStartScheduler();
}
