#include "led.h"
#define TEMPORISATION 30000
/* Fonction qui permet d'allumer une led

	Argument en entrée le numéro de la diode de 0 à 7
	si le numéro de la diode n'est pas l'intervalle la diode 1 sera allumée
	Valeur retour 0 si aucun pb
				  1 sinon	
*/
int allumer_led(int i)
{
	TRISD=0;
	switch(i)
	{
		default:
			sequence_led2();
			sequence_led();
			return 1;
			break;

		case 0:
			PORTDbits.RD0=1;
			break;

		case 1:
			PORTDbits.RD1=1;
			break;
		
		case 2:
			PORTDbits.RD2=1;
			break;

		case 3:
			PORTDbits.RD3=1;
			break;
		
		case 4:
			PORTDbits.RD4=1;
			break;
		
		case 5:
			PORTDbits.RD5=1;
			break;
		case 6:
			PORTDbits.RD6=1;
			break;
		
		case 7:
			PORTDbits.RD7=1;
			break;
	}
	return 0;
}
/* Fonction qui permet d'éteindre une led

	Argument en entrée le numéro de la diode de 0 à 7
	si le numéro de la diode n'est pas l'intervalle la diode 1 sera éteindre
	Valeur retour 0 si aucun pb
				  1 sinon	
*/		
int eteindre_led(int i)
{
	TRISD=0;
	switch(i)
	{
		default:
			sequence_led2();
			sequence_led();
			return 1;
			break;

		case 0:
			PORTDbits.RD0=0;
			break;

		case 1:
			PORTDbits.RD1=0;
			break;
		
		case 2:
			PORTDbits.RD2=0;
			break;

		case 3:
			PORTDbits.RD3=0;
			break;
		
		case 4:
			PORTDbits.RD4=0;
			break;
		
		case 5:
			PORTDbits.RD5=0;
			break;
		case 6:
			PORTDbits.RD6=0;
			break;
		
		case 7:
			PORTDbits.RD7=0;
			break;
	}
	return 0;
}

void sequence_led(void)
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


void sequence_led2(void)
{
	int i;
	int cpt;
	PORTD=0;
	PORTB=0;
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
