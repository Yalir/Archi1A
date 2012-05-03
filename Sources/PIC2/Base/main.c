
#include "config.h"
#include "main.h"
#include "../RS232/rs232.h"

#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config MCLRE = ON
#pragma config LVP = OFF
#pragma config WDT = OFF,DEBUG=OFF


#pragma romdata

void main()
{
	unsigned long id;
	BYTE cpt_RB4;
	BYTE cpt_RB5;
    BYTE data_envoi;
    BYTE data_recu[8];
    BYTE dataLen;
    int i;
    
    ECAN_RX_MSG_FLAGS flags;
	init();
	
	cpt_RB4 = 0;
	cpt_RB5 = 0;
	data_envoi = 0;
	
	for (i = 0; i < 8;i++)
		data_recu[i] = 0xFF;
	
	printf(NL NL "début programme" NL);
    ECANInitialize();
    ECANSetBaudRate(2, 4, 8, 8, 8);
    
	while(1)
	{
		if(TRUE == ECANReceiveMessage(&id, data_recu, &dataLen, &flags))
		{
			PIC1_ONLY printf("ECAN: reçu %u octet(s) : %u" NL, dataLen, data_recu[0]);
			led_afficher_int(data_recu[0]);
		}
		
		
		if(bouton_RB4_pressed())
		{
			cpt_RB4 = cpt_RB4 + 1;
			
			data_envoi = (BYTE)cpt_RB4;
			while (!ECANSendMessage(0, &data_envoi, 1, 0));
			PIC1_ONLY printf("compteur de RB4 : %u" NL, cpt_RB4);
			
			led_afficher_int(cpt_RB4);
		}
			
		if(bouton_RB5_pressed())
		{
			cpt_RB5 = cpt_RB5 + 1;
			
			data_envoi = (BYTE)cpt_RB5;
			while (!ECANSendMessage(0, &data_envoi, 1, 0));
			PIC1_ONLY printf("compteur de RB5 : %u" NL, cpt_RB5);
			
			led_afficher_int(cpt_RB5);
		}
	}
}
