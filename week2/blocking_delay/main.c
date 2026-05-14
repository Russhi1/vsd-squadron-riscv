#include <ch32v00x.h>

void delay(void)
{
    for(volatile int i = 0; i < 1250000; i++);
}

int main(void)
{
    RCC->APB2PCENR |= RCC_APB2Periph_GPIOD;

    GPIOD->CFGLR &= ~(0xF << (4 * 6));
    GPIOD->CFGLR |=  (0x3 << (4 * 6));

    while(1)
    {
        GPIOD->OUTDR ^= (1 << 6);
        delay();
    }
}
