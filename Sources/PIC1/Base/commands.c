
#include "commands.h"
#include "config.h"
#include "led.h"
#include "rs232.h"
#include "can.h"
#include "rheo.h"
#include <stdlib.h>

static long avancement;


void commands_init(void)
{
	avancement = 0;
}

void command_help(void)
{
	printf("Commandes disponibles:" NL);
	printf("alert \t\t Affiche la séquence d'alerte des LEDs" NL);
	printf("avancer \t Avance de N pas" NL);
	printf("clear \t\t Efface l'écran" NL);
	printf("help \t\t Affiche ce message d'aide" NL);
	printf("reculer \t Permet de reculer de N pas" NL);
    printf("degree \t\t Récupère la valeur de la température" NL);
	printf("reset \t\t Redémarre le programme" NL);
	printf(NL);
}

void command_clear()
{
	int i;
	for(i = 0;i < 40;i++)
		printf(NL);
}


void command_avancer(void)
{
	char buf[64];
	int n;
	BYTE data_recun[2];
	int pic;

	printf("De combien de pas ? ");
	rs232_read_line(buf);
	n = atoi(buf);

	printf("Numero du pic ? (1 ou 2) ");
	rs232_read_line(buf);
	pic = atoi(buf);

	if(pic == 1)
	{
		if (avancement + n < 256 && avancement + n >= 0)
		{
			avancement += n;
		}
		else
		{
			printf("Vous devez donner un nombre de pas permettant de rester entre 0 et 255. L'avancement actuel est déjà de %ld pas." NL, avancement);
		}
		
		led_afficher_int(avancement);
	}
	else if(pic == 2)
	{
		can_send(Avancer, n);
	}
	else
	{
		printf("Le numéro du pic choisi n'est pas valable" NL);
	}
}

void command_reculer(void)
{
	char buf[64];
	int n, pic;

	printf("De combien de pas ? ");
	rs232_read_line(buf);
	n = atoi(buf);
	
	printf("Numero du pic ? (1 ou 2) ");
	rs232_read_line(buf);
	pic = atoi(buf);
	
	if(pic == 1)
	{
		if (avancement - n >= 0 && avancement - n < 256)
		{
			avancement -= n;
		}
		else
		{
			printf("Vous devez donner un nombre de pas permettant de rester entre 0 et 255. L'avancement actuel est déjà de %ld pas." NL, avancement);
		}

		led_afficher_int(avancement);
	}
	else if(pic == 2)
	{
		can_send(Reculer, n);
	}
	else
	{
		printf("Le numéro du pic choisi n'est pas valable" NL);
	}
}


void command_alert(void)
{
	led_alert();
	led_afficher_int(avancement);
}

void command_degree(void)
{
	char buf[64];
	int pic;
	unsigned char rheo_val;
	
	printf("Numero du pic ? (1 ou 2) ");
	rs232_read_line(buf);
	pic = atoi(buf);

	if(pic == 1)
	{
		rheo_get_value(&rheo_val);
		
		printf("La valeur du potentiomètre du PIC 1 est %d."NL, rheo_val);
	}
	else if(pic == 2)
	{
		can_send(Degree, 0);
	}
	else
	{
		printf("Le numéro du PIC choisi n'est pas valable." NL);
	}
}
