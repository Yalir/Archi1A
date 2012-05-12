
#include "systeme.h"
#include "can.h"

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

void init_rheo(void)
{
		// Make RA0/AN0 as analog pin, internal reference
    ADCON1 = 0b00001110;

    // A/D result would be right justified, auto acquisition of
    // 4Tad, Fosc/32 clock
    ADCON2 = 0b10010010;

    // Select channel 1 and turn on the ADC Module.
    ADCON0 = 0b00000001;
}


/* Fonction générale de configuration*/
void init(void)
{
	//init_interruption();
	init_rheo();
	can_init();	
}
