
#include "config.h"
#include "systeme.h"
#include "rs232.h"
#include "commands.h"
#include "interruption.h"
#include "can.h"
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
    int writtenLen;
    int i;
    BOOL interrupted;

	run = 1;
	system_init();

	printf(NL NL "Début du programme" NL);
	printf("Bienvenue sur le terminal 1.0 de la carte PICDEM CAN-LIN 3" NL);
	printf("Afin d'avoir un aperçu des commandes disponibles, utilisez la commande 'help'" NL NL);
	
#warning euh bof...
    can_init();
    
	while(run)
	{
		printf("> ");
		interrupted = rs232_read_line(buffer);
		writtenLen = strlen(buffer);
		if (interrupted == TRUE)
		{
			Interruption type;
			BYTE value;

			printf("\r");
			interruption_get_data(&type, &value);
			switch (type)
			{
				case Int_RB4ButtonPressed:
					printf("Notification : le bouton RB4 du PIC 1 a été enfoncé." NL);
					break;

				case Int_RB5ButtonPressed:
					printf("Notification : le bouton RB5 du PIC 1 a été enfoncé." NL);
					break;

				case Int_RB4ButtonPressed2:
					printf("Notification : le bouton RB4 du PIC 2 a été enfoncé." NL);
					break;

				case Int_RB5ButtonPressed2:
					printf("Notification : le bouton RB5 du PIC 2 a été enfoncé." NL);
					break;

				/* case Int_RHEOChanged:
					// géré dans commands.c
					*/
					
				case Int_RHEOChanged2:
					printf("La valeur du potentiomètre du PIC 2 est %d" NL, value * 5);
					break;
					
               	default:
					printf("Notification : interruption inconnue" NL);
			}
		}
		else
		{
			if (strcmppgm2ram(buffer, "help") == 0)
			{
				command_help();
			}
			else if (strcmppgm2ram(buffer, "reset") == 0)
			{
				can_send(Reset, 0);
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
			else if (strcmppgm2ram(buffer, "clear") == 0)
			{
				command_clear();
			}
			else if (strcmppgm2ram(buffer, "alert") == 0)
			{
				command_alert();
			}
			else if (strcmppgm2ram(buffer, "degree") == 0)
			{
				command_degree();
			}
			else if (strcmppgm2ram(buffer, "") == 0)
			{
				// nothing to do
			}	
			else
			{
				printf("%s: commande non reconnue" NL, buffer);
			}
		}
	}
}
