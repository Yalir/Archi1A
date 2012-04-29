
#include "rs232.h"

/* ! REMARQUE !
 * La constante NL permet d'effectuer un retour � la ligne sans devoir
 * �crire � chaque fois \r\n � la main dans le code. L'utilisation de cette
 * constante est facultative.
 */

void main()
{
	// D�clarer un tampon pour stocker le texte saisi par l'utilisateur
	char buf[64];
	
	// Initialiser la communication RS-232
	rs232_init();
	
	// Messages de d�but
	printf(NL);
	printf("==== D�but du programme ====" NL);
	printf("Entrez un texte :" NL);
	
	// Saisie des donn�es
	rs232_read_line(buf);
	
	// Messages de fin
	printf("Donn�es lues :" NL);
	printf("%s" NL, buf);
	printf("==== Fin du programme ====" NL);
}

