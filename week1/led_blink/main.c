

#include <ch32v00x.h>
#include "gpio.h"

void delay(void)
{
    /* Roughly 500ms at 24MHz clock */
    for (volatile int i = 0; i < 5000000; i++);
}

int main(void)
{
    /* Configure onboard LED (PD6) as output */
    gpio_init(PORT_D, LED_PIN, GPIO_OUTPUT);

    while (1)
    {
        gpio_toggle(PORT_D, LED_PIN);   /* flip LED state */
        delay();                         /* wait ~500ms    */
    }
}