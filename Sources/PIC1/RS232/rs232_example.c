
#include "rs232.h"

/* ! REMARQUE !
 * La constante NL permet d'effectuer un retour à la ligne sans devoir
 * écrire à chaque fois \r\n à la main dans le code. L'utilisation de cette
 * constante est facultative.
 */

void main()
{
	// Déclarer un tampon pour stocker le texte saisi par l'utilisateur
	char buf[64];
	
	// Initialiser la communication RS-232
	rs232_init();
	
	// Messages de début
	printf(NL);
	printf("==== Début du programme ====" NL);
	printf("Entrez un texte :" NL);
	
	// Saisie des données
	rs232_read_line(buf);
	
	// Messages de fin
	printf("Données lues :" NL);
	printf("%s" NL, buf);
	printf("==== Fin du programme ====" NL);
}

