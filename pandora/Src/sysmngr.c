#include "sysmngr.h"


void usr_system_init(void)
{
    __nop();
}



void usr_system_ctrl_manager(void)
{
    if (button_pressed != 0)
    {
        if (button_pressed&KEY0_PRESSED)
        {
            led_toggle(LED_R);
            beep(OFF);
        }
        if (button_pressed&KEY1_PRESSED)
        {
            led_toggle(LED_G);
        }
        if (button_pressed&KEY2_PRESSED)
        {
            led_toggle(LED_B);
        }
        
        if (button_pressed&WK_UP_PRESSED)
        {
            beep(ON);
        }
        
        button_pressed = 0;
    }
}

