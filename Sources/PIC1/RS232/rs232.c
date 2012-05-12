
#include "rs232.h"
#include "config.h"
#include "systeme.h"
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
static BOOL has_interruption = FALSE;

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
		
		has_interruption = FALSE;
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

BOOL rs232_read_line(char buffer[64])
{
	int index = 0;
	int delete = 0;
	char c;
	BOOL got_interrupted = FALSE;
	
	// Initialiser le tampon
	for (index = 0; index < 64;index++)
		buffer[index] = '\0';
	
	index = 0;
	has_interruption = FALSE;
	
	// Lire le texte
	do {
		// Lire un caractère
		while (!DataRdyUSART() && has_interruption == FALSE)
			system_perform_states_check();
				
		
		if (has_interruption == FALSE)
		{
			c = ReadUSART();
			
			if (c != 127)
			{
				buffer[index] = c;
				index++;
			}
			else
			{
				if (index > 0)
				{
					index--;
					buffer[index] = '\0';
					delete = 1;
				}
			}	
			
			if (c != 127 || (c == 127 && delete == 1))
			{
				// Afficher les caractères entrés
				while (BusyUSART());
				WriteUSART(c);
				
				if (delete == 1)
					delete = 0;
			}
		}
	} while (c != '\r' && index < 63 && has_interruption == FALSE);
	
	// Eviter de réécrire par dessus le texte saisi
	
	if (has_interruption)
	{
		got_interrupted = TRUE;
	}
	else
	{
		if (index == 63)
		{
			while (BusyUSART());
			WriteUSART('\r');
		}
			
		while (BusyUSART());
		WriteUSART('\n');
		
		// Remove '\r'
		buffer[index-1] = '\0';
	}
	
	return got_interrupted;
}	

void rs232_clear_characters(int length)
{
	int i;
	
	for (i = 0; i < length;i++)
		printf("%c", 127);
}	

void rs232_interrupt_reading(void)
{
	has_interruption = TRUE;
}	
