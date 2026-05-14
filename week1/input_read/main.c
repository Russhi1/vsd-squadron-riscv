#include <ch32v00x.h>

void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    // PD6 as output for built-in LED
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    // PD0 as input for push button
    // External 10k pull-down resistor is used
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

int main(void)
{
    SystemCoreClockUpdate();

    GPIO_Config();

    while(1)
    {
        if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0) == SET)
        {
            // Button pressed -> LED ON
            GPIO_WriteBit(GPIOD, GPIO_Pin_6, RESET);
        }
        else
        {
            // Button released -> LED OFF
            GPIO_WriteBit(GPIOD, GPIO_Pin_6, SET);
        }
    }
}
