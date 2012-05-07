
#include "config.h"
#include "systeme.h"
#include "rs232.h"
#include "commands.h"
#include <string.h>

#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config MCLRE = ON
#pragma config LVP = OFF
#pragma config WDT = OFF,DEBUG=OFF

#pragma romdata


void main()
{
    char buffer[64];
    int run;
	
	run = 1;
	init();
	
	printf(NL NL "Début du programme" NL);
	printf("Bienvenue sur le terminal 1.0 de la carte PICDEM CAN-LIN 3" NL);
	printf("Afin d'avoir un aperçu des commandes disponibles, utilisez la commande 'help'" NL NL);
    
	while(run)
	{
		printf("> ");
		rs232_read_line(buffer);
		
		if (strcmppgm2ram(buffer, "help") == 0)
		{
			command_help();
		}
		else if (strcmppgm2ram(buffer, "reset") == 0)
		{
			run = 0;
		}
		else if (strcmppgm2ram(buffer, "avancer") == 0)
		{
			command_avancer();
		}
		else if (strcmppgm2ram(buffer, "reculer") == 0)
		{
			command_reculer();
		}
		else if (strcmppgm2ram(buffer, "") == 0)
		{
		}
		else if(strcmppgm2ram(buffer, "clear") == 0)
		{
			command_clear();
		}
		else
		{
			printf("%s: commande non reconnue" NL, buffer);
		}	
	}
}