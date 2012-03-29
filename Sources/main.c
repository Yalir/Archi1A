#include "main.h"
#include <delays.h>
#pragma interrupt handler
void handler(void)
{
		static int i=0;	
		/*On masque les autres interruptions*/
		INTCONbits.GIEH=0;
		INTCONbits.GIEL=0;
		if(INTCONbits.RBIF==1)
		{
			if(PORTBbits.RB4==1)
			{
					i=!i;
					if(i==0)
					{
						/*sequence_led();*/
						PORTDbits.RD0=1;
						PORTDbits.RD2=0;
					}
					if(i==1)
					{
						/*sequence_led2();*/
						PORTDbits.RD0=0;
						PORTDbits.RD2=1;
					}
			
			PORTBbits.RB4=0;
				
			}
			/*On désactive le flag du PORTB*/
			INTCONbits.RBIF=0;
		}
		/* On demasque toutes les interruptions*/				
		INTCONbits.GIEH=1;
		INTCONbits.GIEL=1;
		
}	

#pragma romdata CONFIG

_CONFIG_DECL(_OSC_EC_1H, \
             _CONFIG2L_DEFAULT, \
             _WDT_OFF_2H, \
             _CONFIG3L_DEFAULT, \
             _CONFIG3H_DEFAULT, \
             _LVP_OFF_4L & _DEBUG_OFF_4L, \
             _CONFIG5L_DEFAULT, \
             _CONFIG5H_DEFAULT, \
             _CONFIG6L_DEFAULT, \
             _CONFIG6H_DEFAULT, \
             _CONFIG7L_DEFAULT, \
             _CONFIG7H_DEFAULT);

#pragma romdata



void main()
{
	int i=0;
	int j;
	TRISD=0;
	PORTD=0;
	PORTB=0;
	TRISB = 0xFF;
	
	/*
	RCONbits.IPEN=1;
	INTCONbits.GIEH=1;
	INTCONbits.GIEL=1;
	INTCONbits.RBIE=1;*/

	while (1)
	{
		/*sequence_led();
		PORTDbits.RD1=1;
		if(PORTBbits.RB4==0)
		{	i=!i;
			if(i==0)
				sequence_led();
			else
				sequence_led2();
		}*/
		allumer_led(-1);
/*
		i++;
		i=i%8;
*/	
	}
}


