
#include "can.h"
#include "config.h"
#include "ECAN.h"
#include "rs232.h"
#include "bouton.h"
#include "interruption.h"

#pragma romdata
void can_init(void)
{
	ECANInitialize();
    ECANSetBaudRate(2, 4, 8, 8, 8);
}

void can_send(Command c, BYTE param)
{
	BYTE data_envoi[2];
	data_envoi[0] = c;
	data_envoi[1] = param;
	while (!ECANSendMessage(0, data_envoi, 2, 0));
}

 /** R�sultat :
 * 0 s'il n'y a aucune donn�e re�ue sur le bus CAN
 * 1 si des donn�es ont �t� correctement re�ues
 * 2 si c est nul ou param est nul
 */
int can_receive(Command *c, BYTE *param)
{
	unsigned long id;
	BYTE data_recu[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	BYTE dataLen;
	ECAN_RX_MSG_FLAGS flags;
	int res = 0;

	if (c != NULL && param != NULL)
	{
		BOOL didReceiveData = ECANReceiveMessage(&id, data_recu, &dataLen, &flags);

		if (didReceiveData)
		{
			// FIXME: peut etre verifier les bits de la variable 'flags'
			*c = data_recu[0];
			*param = data_recu[1];
			res = 1;
		}
	}
	else
	{
		res = 2;
	}

	return res;
}	

/** V�rification p�riodique dans le cas de donn�es �mises par le PIC 2
 */
void can_check_for_received_data(void)
{
	Command c;
	BYTE param;
	
	int res = can_receive(&c, &param);
	
	if (res == 1)
	{
		switch (c)
		{
			case Degree:
				interruption_save_data(Int_RHEOChanged2, param);
        		rs232_interrupt_reading();
        		break;
        		
        	case BoutonRB4:
        		interruption_save_data(Int_RB4ButtonPressed2, 0);
        		rs232_interrupt_reading();
        		break;
        		
        	case BoutonRB5:
        		interruption_save_data(Int_RB5ButtonPressed2, 0);
        		rs232_interrupt_reading();
        		break;
        		
        	default:
        		break;
		}	
	}	
}	

