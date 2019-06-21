#ifndef _LED_H_
#define _LED_H_

#include "main.h"

typedef enum _ENUM_LED
{
	LED_R,
	LED_G,
	LED_B,
}E_LED;


void led_on(E_LED led);
void led_off(E_LED led);
void led_toggle(E_LED led);




#endif

