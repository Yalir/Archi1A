
#include "systeme.h"
#include "config.h"
#include "rs232.h"
#include "can.h"
#include "led.h"
#include "commands.h"
#include "interruption.h"
#include "rheo.h"


/* Fonction g�n�rale de configuration*/
void system_init(void)
{
	rs232_init();
	can_init();
	commands_init();
	led_init();
	interruption_init();
	rheo_init();
}


/** Fonction appel�e par les appels bloquants pour permettre de v�rifier
 * des �tats normalement g�r�s par interruption
 */
void system_perform_states_check(void)
{
	can_check_for_received_data();
}	
