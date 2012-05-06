
#include "config.h"
#include "main.h"
#include "../RS232/rs232.h"

#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config MCLRE = ON
#pragma config LVP = OFF
#pragma config WDT = OFF,DEBUG=OFF


#pragma romdata
static unsigned char avancement=0;
void avancer(BYTE data)
{
	avancement=(avancement+data);
	if(avancement>255)
		avancement=avancement-255;
	led_afficher_int(avancement);
}
void main()
{
	unsigned long id;
	BYTE cpt_RB4;
	BYTE cpt_RB5;
    BYTE data_envoi[2]={0,0};
    BYTE data_recu[2]={0,0};
    BYTE dataLen=2;
    int i;
    
    ECAN_RX_MSG_FLAGS flags;
	init();
	
	cpt_RB4 = 0;
	cpt_RB5 = 0;
	
	for (i = 0; i < 8;i++)
		data_recu[i] = 0xFF;
	
	ECANInitialize();
    ECANSetBaudRate(2, 4, 8, 8, 8);
    
	while(1)
	{
		if(TRUE == ECANReceiveMessage(&id, data_recu, &dataLen, &flags))
		{
			if(data_recu[0]==1)
			{
				avancer(data_recu[1]);			
			}
		}
		

		if(bouton_RB4_pressed())
		{
			cpt_RB4 = cpt_RB4 + 1;
			data_envoi[0]=4;
			data_envoi[1] = (BYTE)cpt_RB4;
			while (!ECANSendMessage(0, data_envoi, 2, 0));
			PIC1_ONLY printf("compteur de RB4 : %u" NL, cpt_RB4);
			
		}
			
		if(bouton_RB5_pressed())
		{
			cpt_RB5 = cpt_RB5 + 1;
			data_envoi[0]=5;
			data_envoi[1] = (BYTE)cpt_RB5;
			while (!ECANSendMessage(0, data_envoi, 2, 0));
			PIC1_ONLY printf("compteur de RB5 : %u" NL, cpt_RB5);
			
		}
	}
}
