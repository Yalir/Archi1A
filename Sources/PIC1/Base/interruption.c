
#include "interruption.h"
#include "rs232.h"
#include "bouton.h"

static BOOL has_interruption;
static Interruption interruption_type;
static BYTE interruption_value;


void handler(void)
{
		/*On masque les autres interruptions*/
		INTCONbits.GIE=0;
    	if(INTCONbits.RBIF==1)
		{
			if(bouton_RB4_pressed())
			//if (PORTBbits.RB4 == 0)
			{
				interruption_save_data(Int_RB4ButtonPressed, 0);
				rs232_interrupt_reading();
			}	
			else if(bouton_RB5_pressed())
			//else if (PORTBbits.RB5 == 0)
			{
				interruption_save_data(Int_RB5ButtonPressed, 0);
				rs232_interrupt_reading();
			}	
			
			INTCONbits.RBIF=0;	
		}
		
		INTCONbits.GIE=1;
}	


#pragma code InterruptVectorHigh = 0x08        //placer le code suivant à l'adresse 0x18
void InterruptVectorHigh (void)
{
    _asm
        goto handler //jump to interrupt routine
    _endasm

}


void interruption_init(void)
{
	has_interruption = FALSE;
}	

BOOL interruption_did_occur(void)
{
	return has_interruption;
}	

int interruption_get_data(Interruption *type, BYTE *value)
{
	int flag;
	
	if (has_interruption == TRUE)
	{
		if (type == NULL || value == NULL)
		{
			flag = 1;
		}
		else
		{
			*type = interruption_type;
			*value = interruption_value;
			has_interruption = 0;
			flag = 0;
		}	
	}
	else
	{
		flag = 2;
	}
	
	return flag;
}	

void interruption_save_data(Interruption type, BYTE value)
{
	interruption_type = type;
	interruption_value = value;
	has_interruption = TRUE;
}	

