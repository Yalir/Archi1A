#include "bouton.h"
#include <p18f6680.h>

static int bouton_initialized = 0;
static void bouton_check_init(void);

static void bouton_check_init(void)
{
	if (bouton_initialized == 0)
	{
							/*Port B en Input*/
		TRISBbits.RB4 = 1;
		TRISBbits.RB5 = 1;
		bouton_initialized = 1;
	}	
}	

/* 	Fonction bouton_RB4_on
	Renvoie 1 si le bouton RB4 est actionné
	Renvoie 0 sinon
*/
int bouton_RB4_on(void)
{
	bouton_check_init();
	return !(PORTBbits.RB4);
}

/* 	Fonction bouton_RB5_on
	Renvoie 1 si le bouton RB5 est actionné
	Renvoie 0 sinon
*/	
int bouton_RB5_on(void)
{
	bouton_check_init();
	return !(PORTBbits.RB5);
}
