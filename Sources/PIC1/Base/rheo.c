
#include "rheo.h"

/*
 * Fonction d'initialisation du potentiomètre
 */
void rheo_init(void)
{
	// Make RA0/AN0 as analog pin, internal reference
    ADCON1 = 0b00001110;

    // A/D result would be right justified, auto acquisition of
    // 4Tad, Fosc/32 clock
    ADCON2 = 0b10010010;

    // Select channel 1 and turn on the ADC Module.
    ADCON0 = 0b00000001;
    //TRISA=0;
    //PORTA=0;
}

void rheo_get_value(unsigned int * val)
{
	  // Start the conversion
        ADCON0bits.GO = 1;

        // Wait till conversion is over.
        while( ADCON0bits.GO );

        // Display the result.
        *val = ADRES;
}
