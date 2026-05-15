/*
 * week2/noblocking_led/main.c
 * Non-Blocking LED — blink using SysTick timer interrupt
 *
 * "Non-blocking" means the CPU is NOT stuck in a delay loop.
 * The SysTick timer fires an interrupt every 1ms and increments
 * a counter. The main loop checks elapsed time and only acts
 * when 1000ms has passed — but in between it's FREE to do other work.
 *
 * This is how real firmware is written. You will use this pattern
 * constantly in future weeks.
 *
 * Original bare-metal version used direct register writes for GPIO.
 * The SysTick setup is unchanged — that is NOT GPIO, it's a timer.
 * Only the GPIO parts are replaced with library calls.
 */

#include <ch32v00x.h>
#include "gpio.h"

/* -------------------------------------------------------------------
 * millis — incremented every 1ms by the SysTick interrupt
 * volatile tells the compiler: this variable can change at any time
 * (from inside the interrupt), so never cache it in a register.
 * ------------------------------------------------------------------- */
volatile unsigned long millis = 0;

/* -------------------------------------------------------------------
 * SysTick_Handler — interrupt service routine (ISR)
 * Runs automatically every 1ms. We just:
 *   1. Clear the interrupt flag (SR = 0), otherwise it keeps firing
 *   2. Increment our millisecond counter
 * ------------------------------------------------------------------- */
void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void SysTick_Handler(void)
{
    SysTick->SR = 0;   /* clear interrupt flag */
    millis++;           /* count up every 1ms  */
}

/* -------------------------------------------------------------------
 * systick_init — configure SysTick for 1ms ticks at 24MHz
 *
 * SysTick is a countdown timer built into the RISC-V core.
 * It counts down from CMP to 0, fires the interrupt, then resets.
 * At 24MHz: 24,000 clock cycles = exactly 1ms.
 * ------------------------------------------------------------------- */
void systick_init(void)
{
    SysTick->CTLR = 0;         /* disable while configuring    */
    SysTick->SR   = 0;         /* clear any pending interrupt  */
    SysTick->CNT  = 0;         /* reset counter to 0           */
    SysTick->CMP  = 24000 - 1; /* 24MHz / 24000 = 1ms tick     */

    NVIC_EnableIRQ(SysTicK_IRQn);  /* enable SysTick interrupt */

    /* CTLR = 0xF enables: counter, interrupt, auto-reload, HCLK source */
    SysTick->CTLR = 0xF;

    __enable_irq();  /* enable global interrupts */
}

int main(void)
{
    unsigned long previous_led_time = 0;

    /* Configure onboard LED (PD6) as output */
    gpio_init(PORT_D, LED_PIN, GPIO_OUTPUT);

    /* Start the 1ms SysTick timer */
    systick_init();

    while (1)
    {
        /*
         * Has 1000ms passed since we last toggled the LED?
         * If yes → toggle and reset the timer reference.
         * If no  → skip and keep doing other things below.
         *
         * The CPU is NEVER stuck waiting. It just checks and moves on.
         */
        if ((millis - previous_led_time) >= 1000)
        {
            previous_led_time = millis;
            gpio_toggle(PORT_D, LED_PIN);
        }

        /*
         * Everything here runs freely between LED toggles.
         * In future weeks this is where you'll read sensors,
         * handle UART, update displays, etc.
         */
    }
}