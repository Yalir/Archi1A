

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



typedef enum {
	CAN_NoData = 0,				// No data available on CAN buffer
	CAN_DidReceiveData = 1,		// Data correctly received
	CAN_InvalidParameter = 2	// c is null or param is null
} CANResult;

/** Vérifie si des données ont été reçues et les place aux adresses données
 * le cas échéant.
 *
 * @param c L'adresse à laquelle sera placée la commande reçue
 * @param param L'adresse à laquelle sera placé le paramètre associé à la commande
 * @return TRUE si des données ont été reçues, FALSE sinon
 */
CANResult can_receive(Command *c, BYTE *param);

#endif
