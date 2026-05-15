/*
 * week2/blocking_delay/main.c
 * Blocking Delay — LED blink using a busy-wait delay loop
 *
 * "Blocking" means the CPU is stuck inside the delay loop doing nothing.
 * No other task can run during that time. This is the simplest approach
 * but not suitable for real applications where you need multitasking.
 *
 * Original bare-metal version used direct register writes.
 * Library version: same behaviour, cleaner code.
 */

#include <ch32v00x.h>
#include "gpio.h"

/*
 * delay() — blocking busy-wait
 * At 24MHz, this loop takes roughly 250ms.
 * The CPU is 100% occupied here — it cannot do anything else.
 */
void delay(void)
{
    for (volatile int i = 0; i < 1250000; i++);
}

int main(void)
{
    /* Configure onboard LED (PD6) as output */
    gpio_init(PORT_D, LED_PIN, GPIO_OUTPUT);

    while (1)
    {
        gpio_toggle(PORT_D, LED_PIN);  /* flip LED */
        delay();                        /* block for ~250ms */
    }
}