
#include "can.h"
#include "config.h"
#include "ECAN.h"
#include "rs232.h"
#include "bouton.h"

void handler(void)
{
		/*On masque les autres interruptions*/
		
		unsigned long id;
    	BYTE data[4];
    	BYTE dataLen=4;
    	ECAN_RX_MSG_FLAGS flags;
		INTCONbits.GIE=0;
    	if(INTCONbits.RBIF==1)
		{
			if(PORTBbits.RB4==0)
				printf("Appui du bouton RB4 du PIC 1"NL);
			
			if(bouton_RB5_pressed())
				printf("Appui du bouton RB5 du PIC 1"NL);
			
			INTCONbits.RBIF=0;	
		}
		printf(NL">");
		INTCONbits.GIE=1;
}	


#pragma code InterruptVectorHigh = 0x08        //placer le code suivant à l'adresse 0x18
void InterruptVectorHigh (void)
{
    _asm
        goto handler //jump to interrupt routine
    _endasm

}

#pragma romdata
void can_init(void)
{
	ECANInitialize();
    ECANSetBaudRate(2, 4, 8, 8, 8);
}

void can_send(Command c, BYTE param)
{
	BYTE data_envoi[2];
	data_envoi[0] = c;
	data_envoi[1] = param;
	while (!ECANSendMessage(0, data_envoi, 2, 0));
}	

