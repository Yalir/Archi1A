#include <p18f6680.h>

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
	volatile long int i;
	TRISD=0;
	PORTD=0;
	TRISB = 0xFF;
	while (1)
	{
		if (!PORTBbits.RB4) PORTD = 0xFF;
		else PORTD = 0;
		
	}
	return 0;
}
