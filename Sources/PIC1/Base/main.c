
#include "config.h"
#include "main.h"
#include "../RS232/rs232.h"
#include <string.h>
#include <stdlib.h>

#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config MCLRE = ON
#pragma config LVP = OFF
#pragma config WDT = OFF,DEBUG=OFF

void clear();
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

static long avancement=0;

void display_help(void)
{
	printf("Commandes disponibles:" NL);
	printf("help - afficher ce message d'aide" NL);
	printf("reset - redémarrer le programme" NL);
	printf("avancer - permet d'avancer de N pas" NL);
	printf("reculer - permet de reculer de N pas" NL);
	printf("clear - Permet d'effacer l'écran" NL);
	printf(NL);
}

void avancer(void)
{
	char buf[64];
	int n;
	BYTE data_envoi[2];
	BYTE data_recun[2];
	int pic;
	printf("De combien de pas ? ");
	rs232_read_line(buf);
	n = atoi(buf);
	printf(NL);
	printf("Numero du pic ");
	rs232_read_line(buf);
	pic = atoi(buf);
	if(pic==0)
	{
		if (avancement + n < 256 && avancement + n >= 0)
			avancement += n;
		else
			printf("Vous devez donner un nombre de pas permettant de rester entre 0 et 255. L'avancement actuel est déjà de %ld pas." NL, avancement);
	
		led_afficher_int(avancement);
	}
	else if(pic==1 && n>-1 && n<256)
	{
		data_envoi[0]=1;
		data_envoi[1]=n;
		while (!ECANSendMessage(0, data_envoi, 2, 0));
	}
	else
	{
		printf("Le numéro du pic choisi n'est pas valable" NL);
	}
}

void reculer(void)
{
	char buf[64];
	int n;
	
	printf("De combien de pas ? ");
	rs232_read_line(buf);
	
	n = atoi(buf);
	if (avancement - n < 256 && avancement - n >= 0)
		avancement -= n;
	else
		printf("Vous devez donner un nombre de pas permettant de rester entre 0 et 255. L'avancement actuel est déjà de %ld pas." NL, avancement);
	
	
	led_afficher_int(avancement);
}		

void clear()
{
	int i;
	for(i=0;i<40;i++)
		printf(NL);
}

void main()
{
	unsigned long id;
    BYTE data_envoi;
    BYTE data_recu[8];
    BYTE dataLen;
    int i;
    char buffer[64];
    int run;
    ECAN_RX_MSG_FLAGS flags;
	
	init();
	run = 1;
	avancement = 0;
	
	data_envoi = 0;
	
	for (i = 0; i < 8;i++)
		data_recu[i] = 0xFF;
	
	printf(NL NL "Début du programme" NL);
    ECANInitialize();
    ECANSetBaudRate(2, 4, 8, 8, 8);
    
    led_afficher_int(0);
    
    
	printf("Bienvenue sur le terminal 1.0 de la carte PICDEM CAN-LIN 3" NL);
	printf("Afin d'avoir un aperçu des commandes disponibles, utilisez la commande 'help'" NL NL);
    
	while(run)
	{
		int j;
		printf("> ");
		rs232_read_line(buffer);
		
		if (strcmppgm2ram(buffer, "help") == 0)
		{
			display_help();
		}
		else if (strcmppgm2ram(buffer, "reset") == 0)
		{
			run = 0;
		}
		else if (strcmppgm2ram(buffer, "avancer") == 0)
		{
			avancer();
		}
		else if (strcmppgm2ram(buffer, "reculer") == 0)
		{
			reculer();
		}
		else if (strcmppgm2ram(buffer, "") == 0)
		{
		}
		else if(strcmppgm2ram(buffer, "clear") == 0)
		{
			clear();
		}
		else
		{
			printf("%s: commande non reconnue" NL, buffer);
		}	
	}
}