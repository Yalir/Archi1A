
#ifndef INTERRUPTION_H
#define INTERRUPTION_H

#include "config.h"

typedef enum {
	Int_RB4ButtonPressed,
	Int_RB5ButtonPressed
} Interruption;	

/** Initialise le syst�me d'enregistrement des interruptions
 */
void interruption_init(void);

/** Renvoie 1 si une interruption a eu lieu et a �t� enregistr�e, 0 sinon
 */
BOOL interruption_did_occur(void);

/** R�cup�re les donn�es de l'interruption enregistr�e (son type et �ventuellement valeur)
 *
 * @a type et @a value ne doivent pas �tre nuls
 *
 * @param type En sortie, le type de l'interrution enregistr�e
 * @param value En sortie, la valeur associ�e � l'interruption
 * @return 0 s'il n'y a pas d'erreur, 1 si l'un des param�tres est nul, 2 s'il n'y avait pas d'interruption
 * sauvegard�e
 */
int interruption_get_data(Interruption *type, BYTE *value);

/** Enregistre une interruption (� appeler depuis le code de gestion des interruptions)
 */
void interruption_save_data(Interruption type, BYTE value);

/** Met toutes les interruptions en attente jusqu'� ce que interruption_unmask_all() soit appel�.
 */
void interruption_mask_all(void);

/** Permet de r�activer les interruptions pr�c�demment mises en attente par interruption_mask_all()
 */
void interruption_unmask_all(void);


#endif

