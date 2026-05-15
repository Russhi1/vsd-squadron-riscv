/*
 * week2/counter/main.c
 * Counter — LED turns ON when counter is even, OFF when odd
 *
 * This demonstrates using a variable to track state and
 * control GPIO output based on logic (even/odd check).
 *
 * Original bare-metal version used direct register writes.
 * Library version: same behaviour, cleaner code.
 */

#include <ch32v00x.h>
#include "gpio.h"

void delay(void)
{
    for (volatile int i = 0; i < 1250000; i++);
}

int main(void)
{
    unsigned int counter = 0;

    /* Configure onboard LED (PD6) as output */
    gpio_init(PORT_D, LED_PIN, GPIO_OUTPUT);

    while (1)
    {
        counter++;

        /*
         * Even counter → LED ON
         * Odd  counter → LED OFF
         *
         * This is the same logic as the original, just expressed
         * with gpio_write instead of OUTDR register manipulation.
         */
        if (counter % 2 == 0)
        {
            gpio_write(PORT_D, LED_PIN, GPIO_HIGH);  /* even → LED ON  */
        }
        else
        {
            gpio_write(PORT_D, LED_PIN, GPIO_LOW);   /* odd  → LED OFF */
        }

        delay();
    }
}