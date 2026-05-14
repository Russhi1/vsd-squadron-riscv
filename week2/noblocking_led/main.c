#include <ch32v00x.h>

volatile unsigned long millis = 0;

void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void SysTick_Handler(void)
{
    SysTick->SR = 0;
    millis++;
}

void systick_init(void)
{
    SysTick->CTLR = 0;
    SysTick->SR = 0;
    SysTick->CNT = 0;

    // 24 MHz clock, 1 ms tick
    SysTick->CMP = 24000 - 1;

    // Enable SysTick interrupt
    NVIC_EnableIRQ(SysTicK_IRQn);

    // Enable counter, interrupt, auto-reload, HCLK source
    SysTick->CTLR = 0xF;

    // Enable global interrupts
    __enable_irq();
}

void gpio_init(void)
{
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOD;

    GPIOD->CFGLR &= ~(0xF << (4 * 6));
    GPIOD->CFGLR |=  (0x3 << (4 * 6));
}

int main(void)
{
    unsigned long previous_led_time = 0;

    gpio_init();
    systick_init();

    while(1)
    {
        if((millis - previous_led_time) >= 1000)
        {
            previous_led_time = millis;
            GPIOD->OUTDR ^= (1 << 6);
        }

        // Other tasks can run here
    }
}
