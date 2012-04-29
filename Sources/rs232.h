
#ifndef RS232_H
#define RS232_H

#include <stdio.h> // define printf() & co

/** Raccourci (facultatif) pour �crire un retour � la ligne
 *
 * Exemple :
 * printf("du texte" NL);
 */
#define NL "\r\n"


/** Initialiser la communication RS232
 *
 * La communication est initialis�e � un d�bit de 1200 bauds.
 * La fonction rs232_init() doit �tre appel�e une premi�re fois afin que printf()
 * et rs232_read_line() puissent fonctionner.
 */
void rs232_init(void);

/** Lib�rer les ressources de la communication RS232
 */
void rs232_clean(void);

/** Lire du texte sur la ligne RS232
 *
 * Cette fonction ne se termine que lorsqu'un retour � la ligne a �t� tap�
 * ou que le tampon a �t� enti�rement rempli
 *
 * Les donn�es rendues ne contient pas le caract�re de retour � la ligne
 *
 * @param buffer Le tampon dans lequel seront stock�s les caract�res lus
 */
void rs232_read_line(char buffer[64]);

#endif
