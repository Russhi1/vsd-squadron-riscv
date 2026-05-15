/*
 * week1/input_read/main.c
 * Digital Input — read a push button, control the LED
 *
 * Original bare-metal version used:
 *   GPIO_InitTypeDef structs
 *   GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0)
 *   GPIO_WriteBit(GPIOD, GPIO_Pin_6, ...)
 *
 * Library version: same behaviour, much cleaner code.
 *
 * Wiring:
 *   PD6 → onboard LED
 *   PD0 → push button (other side to GND)
 *
 * Behaviour:
 *   Button pressed  → LED ON
 *   Button released → LED OFF
 */

#include <ch32v00x.h>
#include "gpio.h"

int main(void)
{
    /* PD6 = LED output */
    gpio_init(PORT_D, LED_PIN, GPIO_OUTPUT);

    /*
     * PD0 = button input with pull-up
     *
     * Why GPIO_INPUT_PU?
     * The original code used GPIO_Mode_IN_FLOATING with an external
     * 10k pull-down resistor on the board. GPIO_INPUT_PU uses the
     * chip's built-in pull-up instead — no external resistor needed.
     * Button unpressed = pin reads HIGH (1)
     * Button pressed   = pin pulled to GND, reads LOW (0)
     */
    gpio_init(PORT_D, 0, GPIO_INPUT_PU);

    while (1)
    {
        if (gpio_read(PORT_D, 0) == GPIO_LOW)
        {
            gpio_write(PORT_D, LED_PIN, GPIO_HIGH);  /* button pressed  → LED ON  */
        }
        else
        {
            gpio_write(PORT_D, LED_PIN, GPIO_LOW);   /* button released → LED OFF */
        }
    }
}