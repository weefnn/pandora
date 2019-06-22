#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "main.h"

#define KEY0_PRESSED 0x01
#define KEY1_PRESSED 0x02
#define KEY2_PRESSED 0x04

#define WK_UP_PRESSED 0x08


extern volatile uint8_t button_pressed;

#endif

