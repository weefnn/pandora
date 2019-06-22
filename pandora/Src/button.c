#include "button.h"

volatile uint8_t button_pressed;



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == KEY0_Pin)
    {
        button_pressed |= KEY0_PRESSED;
    }
    
    if (GPIO_Pin == KEY1_Pin)
    {
        button_pressed |= KEY1_PRESSED;
    }
    
    if (GPIO_Pin == KEY2_Pin)
    {
        button_pressed |= KEY2_PRESSED;
    }
    
    if (GPIO_Pin == WK_UP_Pin)
    {
        button_pressed |= WK_UP_PRESSED;
    }
}





