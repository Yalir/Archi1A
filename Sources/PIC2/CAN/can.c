
#include "can.h"
#include "config.h"
#include "ECAN.h"
#include "bouton.h"

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

 /** Résultat :
 * 0 s'il n'y a aucune donnée reçue sur le bus CAN
 * 1 si des données ont été correctement reçues
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

