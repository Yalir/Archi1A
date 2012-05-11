

#ifndef CAN_H
#define CAN_H

#include <GenericTypeDefs.h>

/** Constantes définissant les commandes possibles de can_send()
 */
typedef enum Command {
	Avancer = 1,
	Reculer = 2
} Command;	

/** Initialisation du module CAN
 */
void can_init(void);

/** Envoyer la commande @a c de paramètre @a param à l'autre PIC via CAN
 */
void can_send(Command c, BYTE param);

/*
 * Reception de données via le CAN
 */
void can_recieve(void);
#endif
