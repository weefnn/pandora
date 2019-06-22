#include "led.h"

void led_on(E_LED led)
{
    if (led == LED_R)
    {
        HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
    }
    else if (led == LED_G)
    {
        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
    }
    else if (led == LED_B)
    {
        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET);
    }
}

void led_off(E_LED led)
{
    if (led == LED_R)
    {
        HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
    }
    else if (led == LED_G)
    {
        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
    }
    else if (led == LED_B)
    {
        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_B_Pin, GPIO_PIN_SET);
    }
}

void led_toggle(E_LED led)
{
    if (led == LED_R)
    {
        HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
    }
    else if (led == LED_G)
    {
        HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
    }
    else if (led == LED_B)
    {
        HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_B_Pin);
    }
}

void beep(E_ON_OFF state)
{
    if (state == ON)
    {
        HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
    }
    else if (state == OFF)
    {
        HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
    }
}

