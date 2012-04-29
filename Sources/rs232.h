
#ifndef RS232_H
#define RS232_H

#include <stdio.h> // define printf() & co

/** Raccourci (facultatif) pour écrire un retour à la ligne
 *
 * Exemple :
 * printf("du texte" NL);
 */
#define NL "\r\n"


/** Initialiser la communication RS232
 *
 * La communication est initialisée à un débit de 1200 bauds.
 * La fonction rs232_init() doit être appelée une première fois afin que printf()
 * et rs232_read_line() puissent fonctionner.
 */
void rs232_init(void);

/** Libérer les ressources de la communication RS232
 */
void rs232_clean(void);

/** Lire du texte sur la ligne RS232
 *
 * Cette fonction ne se termine que lorsqu'un retour à la ligne a été tapé
 * ou que le tampon a été entièrement rempli
 *
 * Les données rendues ne contient pas le caractère de retour à la ligne
 *
 * @param buffer Le tampon dans lequel seront stockés les caractères lus
 */
void rs232_read_line(char buffer[64]);

#endif
