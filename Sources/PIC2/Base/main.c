
#include "config.h"
#include "main.h"
#include "can.h"

#pragma config PWRT = OFF
#pragma config BOR = ON
#pragma config MCLRE = ON
#pragma config LVP = OFF
#pragma config WDT = OFF,DEBUG=OFF


#pragma romdata
static unsigned char avancement=0;
void avancer(BYTE data)
{
    avancement += data;
	led_afficher_int(avancement);
}

void reculer(BYTE data)
{
    avancement -= data;
	led_afficher_int(avancement);
}

void degree(void)
{
	unsigned char rheo_val;
	rheo_get_value(&rheo_val);
	can_send(Degree, rheo_val);
}	


void main()
{
	BYTE cpt_RB4;
	BYTE cpt_RB5;
    Command cmd;
    BYTE param;
    int run = 1;

	init();
	
	cpt_RB4 = 0;
	cpt_RB5 = 0;
	avancement = 0;

	while(run)
	{
		if (1 == can_receive(&cmd, &param))
		{
			switch (cmd)
			{
				case Avancer:
					avancer(param);
					break;
					
				case Reculer:
					reculer(param);
					break;
					
				case Degree:
					degree();
					break;
				
				case Reset:
					run = 0;
					break;
				default:
					break;
			}	
		}

		if(bouton_RB4_pressed())
		{
			cpt_RB4++;
			can_send(BoutonRB4, cpt_RB4);
		}

		if(bouton_RB5_pressed())
		{
			cpt_RB5++;
			can_send(BoutonRB5, cpt_RB5);
		}
	}
}
