
#include "systeme.h"
#include "config.h"
#include "rs232.h"
#include "can.h"
#include "led.h"
#include "commands.h"
#include "interruption.h"

/* Fonction d'initialisation des paramètres pour les interruptions*/
void init_interruption()
{
						/*Interruption générale*/
	RCONbits.IPEN=0;
	INTCONbits.GIE=1;
	INTCONbits.PEIE=0;
						/*Interruption du port B*/
	INTCONbits.RBIE=1;
	INTCON2bits.RBIP=0;
	PORTD=0;
	TRISD=0;
}


/* Fonction générale de configuration*/
void init(void)
{
	init_interruption();
	rs232_init();
	can_init();
	commands_init();
	led_init();
	interruption_init();
}
