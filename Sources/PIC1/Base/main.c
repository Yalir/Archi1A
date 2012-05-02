#include "main.h"

#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config MCLRE = ON
#pragma config LVP = OFF
#pragma config WDT = OFF,DEBUG=OFF

int action=0;
void handler(void)
{
		/*On masque les autres interruptions*/
		
		unsigned long id;
    	BYTE data[4];
    	BYTE dataLen=4;
    	ECAN_RX_MSG_FLAGS flags;
    	if(INTCONbits.RBIF==1)
		{
			if(PORTBbits.RB4==0)
				action=4;
			
			if(PORTBbits.RB5==0)
				action=5;
			INTCONbits.RBIF=0;	
		}
}	


#pragma code InterruptVectorHigh = 0x08        //placer le code suivant à l'adresse 0x18
void InterruptVectorHigh (void)
{
    _asm
        goto handler //jump to interrupt routine
    _endasm

}
	
#pragma romdata 
void main()
{
	
	unsigned long id;
    BYTE data_envoi[4]={0,0,0,0};
    BYTE data_recu[4]={0,0,0,0};
    BYTE dataLen=1;
    ECAN_RX_MSG_FLAGS flags;
	init();
    ECANInitialize();
    ECANSetBaudRate(2, 4, 8, 8, 8);
	while(1)
	{
		if(!ECANReceiveMessage(&id, data_recu, &dataLen, &flags))
		{	
			if(data_recu[0]==4)
				led_on(4);
			if(data_recu[0]==5)
				led_on(5);
		}
		if(action!=0)
		{
			led_alert();
			led_on(action+2);
			if(action==4)
			{
				data_envoi[0]=(BYTE)4;
				while( !ECANSendMessage(&id, data_envoi, &dataLen, &flags) );
			}
			if(action==5)
			{
				data_envoi[0]=(BYTE)5;
				while( !ECANSendMessage(&id, data_envoi, &dataLen, &flags) );
			}
			action=0;
		}
	}
}
