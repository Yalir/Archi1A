
#include "can.h"
#include "config.h"
#include "ECAN.h"
#include "rs232.h"
#include "bouton.h"
#include "../Base/interruption.h"
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

void can_recieve(void)
{
	unsigned long id=0;
	BYTE data_recu[2]={19,19};
	BYTE dataLen=2;
    ECAN_RX_MSG_FLAGS flags;
	if(ECANReceiveMessage(&id, data_recu, &dataLen, &flags))
	{
	printf("Data = %d"NL,data_recu[0]);
		if(data_recu[0]==4)
			interruption_save_data(Int_RB4ButtonPressed2,0);
		if (data_recu[0]==5)
			interruption_save_data(Int_RB5ButtonPressed2,0);
		rs232_interrupt_reading();
		
	}
}