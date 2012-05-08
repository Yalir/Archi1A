
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

