#include "main.h"
#include "../RS232/rs232.h"

#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config MCLRE = ON
#pragma config LVP = OFF
#pragma config WDT = OFF,DEBUG=OFF

//static int action=0;
//void handler(void)
//{
//		/*On masque les autres interruptions*/
//		
//		unsigned long id;
//    	BYTE data[4];
//    	BYTE dataLen=4;
//    	ECAN_RX_MSG_FLAGS flags;
//    	
//    	printf("handler interruption" NL);
//    	
//    	if(INTCONbits.RBIF==1)
//		{
//			if(PORTBbits.RB4==0)
//				action=4, printf("action détectée : 4" NL);
//			else if(PORTBbits.RB5==0)
//				action=5, printf("action détectée : 5" NL);
//			else
//				printf("action non détectée" NL);
//			
//			printf("valeur actuelle de l'action : %d" NL, action);
//			printf("PORTB : %.8b" NL, PORTB);
//			
//			INTCONbits.RBIF=0;	
//		}
//		
//		INTCONbits.GIE=1;
//	INTCONbits.PEIE=1;
//}	
//
//
//#pragma code InterruptVectorHigh = 0x08        //placer le code suivant à l'adresse 0x18
//void InterruptVectorHigh (void)
//{
//    _asm
//        goto handler //jump to interrupt routine
//    _endasm
//
//}
//	
#pragma romdata 
void main()
{
	unsigned long id;
	BYTE cpt_RB4=0;
	BYTE cpt_RB5=0;
    BYTE data_envoi[4]={0,0,0,0};
    BYTE data_recu[4]={0,0,0,0};
    BYTE dataLen=1;
    ECAN_RX_MSG_FLAGS flags;
	init();
	
	printf(NL NL "début programme" NL);
    ECANInitialize();
    ECANSetBaudRate(2, 4, 8, 8, 8);
	while(1)
	{
		//printf("début de boucle" NL);
		
		if(TRUE == ECANReceiveMessage(&id, data_recu, &dataLen, &flags))
		{
			printf("reçu message sur le PIC1 : %u" NL, data_recu[0]);
			
			if(data_recu[0]==4)
				led_on(4);
			if(data_recu[0]==5)
				led_on(5);
				
			printf("Données reçues = %u" NL, data_recu[0]);
		}
		
		
		if(bouton_RB4_pressed())
		{
			printf("bouton RB4 appuyé" NL);
			cpt_RB4++;
			led_afficher_int(cpt_RB4);
			data_envoi[0]=(BYTE)cpt_RB4;
			while( !ECANSendMessage(id, data_envoi, dataLen, flags) ) printf("envoi ECAN (action 4)" NL);
			
			printf("compteur RB4 appuyé %u fois" NL, cpt_RB4);
		}
			
		if(bouton_RB5_pressed())
		{
			printf("bouton RB5 appuyé" NL);
			cpt_RB5++;
			led_afficher_int(cpt_RB5);
			data_envoi[0]=(BYTE)cpt_RB5;
			while( !ECANSendMessage(id, data_envoi, dataLen, flags) ) printf("envoi ECAN (action 5)" NL);
			
			printf("compteur RB5 appuyé %u fois" NL, cpt_RB5);
		}
		
		//printf("fin de boucle" NL);
	}
}
