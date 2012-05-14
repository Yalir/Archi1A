
#include "led.h"

#include <p18f8680.h>
#define TEMPORISATION 20000

static int led_check_initialized = 0;
static void led_check_init(void);

static void led_check_init(void)
{
	if (led_check_initialized == 0)
	{
							/*Configuration du Port D en Output*/
		TRISD=0;
							/*On éteint toutes les leds*/
		PORTD=0;
		
		led_check_initialized = 1;
	}
}

/* Fonction qui permet d'allumer une led

	Argument en entrée le numéro de la diode de 0 à 7
	si le numéro de la diode n'est pas l'intervalle la diode 1 sera allumée
	Valeur retour 0 si aucun pb
				  1 sinon	
*/
void led_on(int i)
{
	led_check_init();
	
	if (i >= 0 && i <= 7)
		PORTD |= (1 << i);
	else
		led_alert();
}
/* Fonction qui permet d'éteindre une led

	Argument en entrée le numéro de la diode de 0 à 7
	si le numéro de la diode n'est pas l'intervalle la diode 1 sera éteindre
	Valeur retour 0 si aucun pb
				  1 sinon	
*/		
void led_off(int i)
{
	led_check_init();
	
	if (i >= 0 && i <= 7)
		PORTD &= ~(1 << i);
	else
		led_alert();
}

void led_sequence1(void)
{
	led_check_init();

	{
		int i;
		int cpt;
		for(cpt=0;cpt<5;cpt++)
		{
				PORTDbits.RD0=1;
				for(i=0;i<TEMPORISATION;i++);
				PORTDbits.RD0=0;
				PORTDbits.RD1=1;			
				for(i=0;i<TEMPORISATION;i++);
				PORTDbits.RD1=0;
				PORTDbits.RD2=1;						
				for(i=0;i<TEMPORISATION;i++);
				PORTDbits.RD2=0;
				PORTDbits.RD3=1;									
				for(i=0;i<TEMPORISATION;i++);
				PORTDbits.RD3=0;
				PORTDbits.RD4=1;									
				for(i=0;i<TEMPORISATION;i++);
				PORTDbits.RD4=0;
				PORTDbits.RD5=1;									
				for(i=0;i<TEMPORISATION;i++);
				PORTDbits.RD5=0;
				PORTDbits.RD6=1;									
				for(i=0;i<TEMPORISATION;i++);
				PORTDbits.RD6=0;
				PORTDbits.RD7=1;									
				for(i=0;i<TEMPORISATION;i++);
				PORTDbits.RD7=0;
		}
	}
}


void led_sequence2(void)
{
	led_check_init();
	
	{
		int i;
		int cpt;
		TRISD=0;
		for(cpt=0;cpt<10;cpt++)
		{
				PORTDbits.RD0=1;
				PORTDbits.RD2=1;
				PORTDbits.RD4=1;
				PORTDbits.RD6=1;
				for(i=0;i<27000;i++);
				PORTDbits.RD0=0;
				PORTDbits.RD2=0;
				PORTDbits.RD4=0;
				PORTDbits.RD6=0;
	
				PORTDbits.RD1=1;
				PORTDbits.RD3=1;
				PORTDbits.RD5=1;
				PORTDbits.RD7=1;
				for(i=0;i<27000;i++);
				PORTDbits.RD1=0;
				PORTDbits.RD3=0;
				PORTDbits.RD5=0;
				PORTDbits.RD7=0;
		}
	}
}

void led_afficher_int(unsigned char valeur)
{
	led_check_init();
	PORTDbits.RD0 = ((valeur & (1 /*<< 0*/)) != 0) ? 1 : 0;
	PORTDbits.RD1 = ((valeur & (1 << 1)) != 0) ? 1 : 0;
	PORTDbits.RD2 = ((valeur & (1 << 2)) != 0) ? 1 : 0;
	PORTDbits.RD3 = ((valeur & (1 << 3)) != 0) ? 1 : 0;
	PORTDbits.RD4 = ((valeur & (1 << 4)) != 0) ? 1 : 0;
	PORTDbits.RD5 = ((valeur & (1 << 5)) != 0) ? 1 : 0;
	PORTDbits.RD6 = ((valeur & (1 << 6)) != 0) ? 1 : 0;
	PORTDbits.RD7 = ((valeur & (1 << 7)) != 0) ? 1 : 0;
}

void led_alert(void)
{
	led_check_init();
	
	{
		int i,j;
		PORTD=0;
		for(i=0;i<10;i++)
		{
			PORTD = ~PORTD;
			for(j=0;j<TEMPORISATION;j++);
		}
	}
}
