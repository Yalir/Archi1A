
#include "can.h"
#include "config.h"
#include "ECAN.h"
#include "rs232.h"
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


CANResult can_receive(Command *c, BYTE *param)
{
	unsigned long id;
	BYTE data_recu[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	BYTE dataLen;
    ECAN_RX_MSG_FLAGS flags;
	CANResult res = CAN_NoData;
	
	if (c != NULL && param != NULL)
	{
		BOOL didReceiveData = ECANReceiveMessage(&id, data_recu, &dataLen, &flags);
		
		if (didReceiveData)
		{
			// FIXME: peut etre verifier les bits de la variable 'flags'
			*c = data_recu[0];
			*param = data_recu[1];
			res = CAN_DidReceiveData;
		}
	}
	else
	{
		res = CAN_InvalidParameter;
	}
	
	return res;
}
