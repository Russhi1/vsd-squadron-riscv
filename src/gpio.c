/*
 * gpio.c — GPIO Hardware Abstraction Library
 * VSD Squadron Mini (CH32V003F4U6)
 *
 * Register reference (CH32V003 manual):
 *   RCC->APB2PCENR  — clock enable for each GPIO port
 *   GPIOx->CFGLR    — pin direction config, 4 bits per pin (pins 0–7)
 *   GPIOx->OUTDR    — output data register (write pin value)
 *   GPIOx->INDR     — input  data register (read  pin value)
 *
 * Author: Rushil Rai
 */

#include "gpio.h"

/* -----------------------------------------------------------------------
 * INTERNAL HELPER: enable_clock(port)
 *
 * The CH32V003 keeps GPIO peripherals OFF by default to save power.
 * Before touching any GPIO register you must turn the clock on.
 * This is done once per port — calling it multiple times is safe
 * because we use |= (set bits, never clear them).
 * ---------------------------------------------------------------------- */
static void enable_clock(GPIO_TypeDef *port)
{
    if (port == GPIOA)
        RCC->APB2PCENR |= RCC_APB2Periph_GPIOA;
    else if (port == GPIOC)
        RCC->APB2PCENR |= RCC_APB2Periph_GPIOC;
    else if (port == GPIOD)
        RCC->APB2PCENR |= RCC_APB2Periph_GPIOD;
}

/* -----------------------------------------------------------------------
 * gpio_init(port, pin, mode)
 *
 * How CFGLR works:
 *   Each pin occupies 4 bits in CFGLR.
 *   Pin 0 → bits [3:0],  pin 1 → bits [7:4],  ...,  pin 6 → bits [27:24]
 *   Bit position = 4 * pin
 *
 *   The 4 bits encode two fields: CNF[1:0] and MODE[1:0]
 *
 *   Value  Binary  Meaning
 *   0x3    0011    Push-pull output, 50 MHz           ← GPIO_OUTPUT
 *   0x4    0100    Floating input (no resistor)        ← GPIO_INPUT
 *   0x8    1000    Input with pull-up OR pull-down     ← GPIO_INPUT_PU/PD
 *                  (direction set by OUTDR bit:
 *                   OUTDR=1 → pull-up, OUTDR=0 → pull-down)
 *
 * Steps:
 *   1. Enable the port clock
 *   2. Clear the 4 bits for this pin  (always do this first!)
 *   3. Write the new mode value
 *   4. For pull-up/down: set or clear the OUTDR bit accordingly
 * ---------------------------------------------------------------------- */
void gpio_init(GPIO_TypeDef *port, uint8_t pin, uint8_t mode)
{
    /* Step 1 — power on the GPIO port */
    enable_clock(port);

    /* Step 2 — clear the 4 config bits for this pin */
    port->CFGLR &= ~(0xF << (4 * pin));

    /* Step 3 — write new config */
    if (mode == GPIO_OUTPUT)
    {
        /* 0x3 = push-pull output, 50MHz drive strength */
        port->CFGLR |= (0x3 << (4 * pin));
    }
    else if (mode == GPIO_INPUT)
    {
        /* 0x4 = floating input (no pull resistor) */
        port->CFGLR |= (0x4 << (4 * pin));
    }
    else if (mode == GPIO_INPUT_PU)
    {
        /* 0x8 = input with pull resistor enabled */
        port->CFGLR |= (0x8 << (4 * pin));
        /* Step 4 — OUTDR=1 selects pull-UP when in pull mode */
        port->OUTDR |= (1 << pin);
    }
    else if (mode == GPIO_INPUT_PD)
    {
        /* 0x8 = input with pull resistor enabled */
        port->CFGLR |= (0x8 << (4 * pin));
        /* Step 4 — OUTDR=0 selects pull-DOWN when in pull mode */
        port->OUTDR &= ~(1 << pin);
    }
}

/* -----------------------------------------------------------------------
 * gpio_write(port, pin, value)
 *
 * OUTDR is the Output Data Register.
 * Each bit corresponds to a pin number.
 * Setting bit N → pin N goes HIGH (3.3V)
 * Clearing bit N → pin N goes LOW  (0V)
 *
 * We use |= to set (never touch other bits)
 * and &= ~ to clear (never touch other bits)
 * ---------------------------------------------------------------------- */
void gpio_write(GPIO_TypeDef *port, uint8_t pin, uint8_t value)
{
    if (value == GPIO_HIGH)
        port->OUTDR |=  (1 << pin);   /* set bit   → pin HIGH */
    else
        port->OUTDR &= ~(1 << pin);   /* clear bit → pin LOW  */
}

/* -----------------------------------------------------------------------
 * gpio_toggle(port, pin)
 *
 * XOR flips the bit: if it was 1 it becomes 0, and if 0 it becomes 1.
 * The ^ operator is perfect for toggling a single bit without
 * disturbing any of the other pins.
 * ---------------------------------------------------------------------- */
void gpio_toggle(GPIO_TypeDef *port, uint8_t pin)
{
    port->OUTDR ^= (1 << pin);
}

/* -----------------------------------------------------------------------
 * gpio_read(port, pin)
 *
 * INDR is the Input Data Register.
 * It holds the live voltage state of every pin right now.
 * We shift right by pin number to bring our bit to position 0,
 * then mask with 0x1 to get either 0 or 1.
 * ---------------------------------------------------------------------- */
uint8_t gpio_read(GPIO_TypeDef *port, uint8_t pin)
{
    return (port->INDR >> pin) & 0x1;
}