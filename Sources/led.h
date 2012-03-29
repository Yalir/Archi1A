#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED
#include <p18f6680.h>

int allumer_led(int i);
int eteindre_led(int i);
void sequence_led(void);
void sequence_led2(void);
#endif