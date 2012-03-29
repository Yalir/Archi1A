
#include "rs232.h"
#include <usart.h>
#include <p18f6680.h>

#define FOSC 25000000

void rs232_init(void)
{
	/* baudRate = FOSC / (64 * (spbgr + 1))
	 * spbgr = (FOSC / (baudRate * 64)) - 1
	 */
	long baudRate = 1200;
	long spbgr = (FOSC / (baudRate * 64)) - 1; // = 324 en théorie
	
	/* vérifier sur la carte à quel pin est connecté le RS232,
	 * et en particulier s'il s'agit bien de la porte C
	 */
	TRISC = 0x00;
	
	OpenUSART(	USART_TX_INT_OFF & USART_RX_INT_OFF &
				USART_ASYNCH_MODE & USART_EIGHT_BIT &
				USART_CONT_RX & USART_BRGH_LOW, spbgr );
}

void rs232_clean(void)
{
	CloseUSART();
}	

