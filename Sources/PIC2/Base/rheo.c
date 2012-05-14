
#include "rheo.h"
#include "config.h"

void rheo_get_value(unsigned int * val)
{
	// Start the conversion
	ADCON0bits.GO = 1;

	// Wait till conversion is over.
	while( ADCON0bits.GO );

	// Display the result.
	*val = ADRES;
}
