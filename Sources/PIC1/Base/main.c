
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


#pragma romdata

static long avancement;

void display_help(void)
{
	printf("Commandes disponibles:" NL);
	
	printf("help - afficher ce message d'aide" NL);
	printf("exit - redémarrer le programme" NL);
	printf("avancer - permet d'avancer de N pas" NL);
	printf("reculer - permet de reculer de N pas" NL);
	
	printf(NL);
}

void avancer(void)
{
	char buf[64];
	int n;
	
	printf("De combien de pas ? ");
	rs232_read_line(buf);
	
	n = atoi(buf);
	
	if (avancement + n < 256 && avancement + n >= 0)
		avancement += n;
	else
		printf("Vous devez donner un nombre de pas permettant de rester entre 0 et 255. L'avancement actuel est déjà de %ld pas." NL, avancement);
	
	led_afficher_int(avancement);
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
		else if (strcmppgm2ram(buffer, "exit") == 0)
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
		else
		{
			printf("%s: commande non reconnue" NL, buffer);
		}	
	}
}
