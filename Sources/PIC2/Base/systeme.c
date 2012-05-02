#include "systeme.h"
#include "../RS232/rs232.h"

/* Fonction d'initialisation des paramètres pour les interruptions*/
void init_interruption()
{
						/*Interruption générale*/
	RCONbits.IPEN=0;
	INTCONbits.GIE=1;
	INTCONbits.PEIE=1;
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
}
