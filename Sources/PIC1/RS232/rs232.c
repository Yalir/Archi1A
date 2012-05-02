
#include "rs232.h"
#include "led.h"
#include <p18f6680.h>
#include <usart.h>


#define BIT0 (1 << 0)
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)
#define BIT3 (1 << 3)
#define BIT4 (1 << 4)
#define BIT5 (1 << 5)
#define BIT6 (1 << 6)
#define BIT7 (1 << 7)

static int rs232_initialized = 0;

void rs232_init(void)
{
	if (rs232_initialized == 0)
	{
		/* baudRate = FOSC / (16 * (spbgr + 1))
		 * spbgr = (FOSC / (baudRate * 16)) - 1
		 */
		const long fosc = 25000000;
		const long baudRate = 1200;
		// long spbgr = (FOSC / (baudRate * 16)) - 1;
		// equivalent pré-calculé :
		const long spbgr = 1301;
		
		OpenUSART(	USART_TX_INT_OFF & USART_RX_INT_OFF &
					USART_ASYNCH_MODE & USART_EIGHT_BIT &
					USART_CONT_RX & USART_BRGH_HIGH, spbgr );
		
		TXSTA = BIT5;
		RCSTA = BIT4 | BIT7;
		BAUDCON = BIT3;
		
		rs232_initialized = 1;
	}
}

void rs232_clean(void)
{
	if (rs232_initialized == 1)
	{
		CloseUSART();
		rs232_initialized = 0;
	}
}	

void rs232_read_line(char buffer[64])
{
	unsigned int index = 0;
	char c;
	
	// Initialiser le tampon
	for (index = 0; index < 64;index++)
		buffer[index] = '\0';
	
	index = 0;
	
	// Lire le texte
	do {
		// Lire un caractère
		while (!DataRdyUSART());
		c = ReadUSART();
		buffer[index] = c;
		index++;
		
		// Afficher les caractères entrés
		while (BusyUSART());
		WriteUSART(c);
	} while (c != '\r' && index < 64);
	
	// Eviter de réécrire par dessus le texte saisi
	while (BusyUSART());
	WriteUSART('\n');
	
	// Remove '\r'
	buffer[index-1] = '\0';
}	
