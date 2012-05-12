

#ifndef CAN_H
#define CAN_H

#include <GenericTypeDefs.h>

/** Constantes définissant les commandes possibles de can_send()
 */
typedef enum Command {
	Avancer = 1,
	Reculer = 2,
	Degree = 7,
	BoutonRB4 = 8,
	BoutonRB5 = 9,
	Reset = 10
} Command;	

/** Initialisation du module CAN
 */
void can_init(void);

/** Envoyer la commande @a c de paramètre @a param à l'autre PIC via CAN
 */
void can_send(Command c, BYTE param);

/** Reception de données via le bus CAN
 *
 * Résultat :
 * 0 s'il n'y a aucune donnée reçue sur le bus CAN
 * 1 si des données ont été correctement reçues
 * 2 si c est nul ou param est nul
 */
int can_receive(Command *c, BYTE *param);


#endif
