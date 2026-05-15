
#ifndef GPIO_H
#define GPIO_H

#include <ch32v00x.h>

#define PORT_A    GPIOA
#define PORT_C    GPIOC
#define PORT_D    GPIOD


#define GPIO_OUTPUT      0    /* Push-pull output, 50MHz drive speed       */
#define GPIO_INPUT       1    /* Floating input — no pull resistor          */
#define GPIO_INPUT_PU    2    /* Input with internal pull-UP resistor       */
#define GPIO_INPUT_PD    3    /* Input with internal pull-DOWN resistor     */


#define GPIO_HIGH    1
#define GPIO_LOW     0

/* -----------------------------------------------------------------------
 * COMMON PIN SHORTCUTS  (saves typing for frequent pins)
 * ---------------------------------------------------------------------- */
#define LED_PIN      6    /* PD6 — onboard user LED */
#define BTN_PIN      4    /* PD4 — onboard push button */

/* -----------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 * ---------------------------------------------------------------------- */

/*
 * gpio_init(port, pin, mode)
 *
 * Enables the clock for the port and configures the pin direction.
 * Must be called before gpio_write / gpio_read / gpio_toggle.
 *
 * Example:
 *   gpio_init(PORT_D, 6, GPIO_OUTPUT);   // LED as output
 *   gpio_init(PORT_D, 0, GPIO_INPUT_PU); // Button with pull-up
 */
void gpio_init(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);

/*
 * gpio_write(port, pin, value)
 *
 * Sets a pin HIGH (1 = 3.3V) or LOW (0 = 0V).
 * Pin must be configured as GPIO_OUTPUT first.
 *
 * Example:
 *   gpio_write(PORT_D, 6, GPIO_HIGH);   // LED ON
 *   gpio_write(PORT_D, 6, GPIO_LOW);    // LED OFF
 */
void gpio_write(GPIO_TypeDef *port, uint8_t pin, uint8_t value);

/*
 * gpio_toggle(port, pin)
 *
 * Flips a pin: if it was HIGH it goes LOW, and vice versa.
 * Useful for blinking without tracking state manually.
 *
 * Example:
 *   gpio_toggle(PORT_D, 6);   // blink LED
 */
void gpio_toggle(GPIO_TypeDef *port, uint8_t pin);

/*
 * gpio_read(port, pin)
 *
 * Returns 1 if the pin is HIGH, 0 if LOW.
 * Pin must be configured as an INPUT mode first.
 *
 * Example:
 *   if (gpio_read(PORT_D, 0) == GPIO_HIGH) { ... }
 */
uint8_t gpio_read(GPIO_TypeDef *port, uint8_t pin);

#endif /* GPIO_H */