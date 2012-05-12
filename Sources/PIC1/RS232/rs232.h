
#ifndef RS232_H
#define RS232_H

#include <stdio.h> // define printf() & co
#include "config.h"
#include "interruption.h"

/** Raccourci (facultatif) pour �crire un retour � la ligne
 *
 * Exemple :
 * printf("du texte" NL);
 */
#define NL "\r\n"

#define printf(s) interruption_mask_all(); printf(s); interruption_unmask_all()


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
 * @return renvoie TRUE si la lecture a �t� interrompue par une interruption,
 * FALSE sinon
 */
BOOL rs232_read_line(char buffer[64]);

/** Affiche @a length caract�res d'effacement
 */
void rs232_clear_characters(int length);

/** Interrompt la lecture des caract�res (� appeler depuis le code de gestion des interruptions)
 */
void rs232_interrupt_reading(void);

#endif
