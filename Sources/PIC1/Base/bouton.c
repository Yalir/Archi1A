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

int bouton_RB4_pressed(void)
{
	static int prevState = 0;
	int res = 0;
	
	if (bouton_RB4_on() && prevState == 0)
	{
		res = 1;
		prevState = 1;
	}
	else if (!bouton_RB4_on() && prevState == 1)
	{
		prevState = 0;
	}
	
	return res;
}

int bouton_RB5_pressed(void)
{
	static int prevState = 0;
	int res = 0;
	
	if (bouton_RB5_on() && prevState == 0)
	{
		res = 1;
		prevState = 1;
	}
	else if (!bouton_RB5_on() && prevState == 1)
	{
		prevState = 0;
	}
	
	return res;
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
