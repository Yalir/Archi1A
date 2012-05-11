

#ifndef CAN_H
#define CAN_H

#include <GenericTypeDefs.h>

/** Constantes d�finissant les commandes possibles de can_send()
 */
typedef enum Command {
	Avancer = 1,
	Reculer = 2
} Command;

/** Initialisation du module CAN
 */
void can_init(void);

/** Envoyer la commande @a c de param�tre @a param � l'autre PIC via CAN
 */
void can_send(Command c, BYTE param);



typedef enum {
	CAN_NoData = 0,				// No data available on CAN buffer
	CAN_DidReceiveData = 1,		// Data correctly received
	CAN_InvalidParameter = 2	// c is null or param is null
} CANResult;

/** V�rifie si des donn�es ont �t� re�ues et les place aux adresses donn�es
 * le cas �ch�ant.
 *
 * @param c L'adresse � laquelle sera plac�e la commande re�ue
 * @param param L'adresse � laquelle sera plac� le param�tre associ� � la commande
 * @return TRUE si des donn�es ont �t� re�ues, FALSE sinon
 */
CANResult can_receive(Command *c, BYTE *param);

#endif
