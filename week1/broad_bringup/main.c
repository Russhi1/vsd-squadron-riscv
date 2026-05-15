

#include <ch32v00x.h>
#include "gpio.h"

int main(void)
{
    /* Configure onboard LED pin as output */
    gpio_init(PORT_D, LED_PIN, GPIO_OUTPUT);

    /* Turn LED ON — this is your "board is alive" signal */
    gpio_write(PORT_D, LED_PIN, GPIO_HIGH);

    /* Stay here forever — LED stays ON */
    while (1)
    {
    }
}