
#ifndef INTERRUPTION_H
#define INTERRUPTION_H

#include "config.h"

typedef enum {
	Int_RB4ButtonPressed,
	Int_RB5ButtonPressed
} Interruption;	

/** Initialise le système d'enregistrement des interruptions
 */
void interruption_init(void);

/** Renvoie 1 si une interruption a eu lieu et a été enregistrée, 0 sinon
 */
BOOL interruption_did_occur(void);

/** Récupère les données de l'interruption enregistrée (son type et éventuellement valeur)
 *
 * @a type et @a value ne doivent pas être nuls
 *
 * @param type En sortie, le type de l'interrution enregistrée
 * @param value En sortie, la valeur associée à l'interruption
 * @return 0 s'il n'y a pas d'erreur, 1 si l'un des paramètres est nul, 2 s'il n'y avait pas d'interruption
 * sauvegardée
 */
int interruption_get_data(Interruption *type, BYTE *value);

/** Enregistre une interruption (à appeler depuis le code de gestion des interruptions)
 */
void interruption_save_data(Interruption type, BYTE value);

/** Met toutes les interruptions en attente jusqu'à ce que interruption_unmask_all() soit appelé.
 */
void interruption_mask_all(void);

/** Permet de réactiver les interruptions précédemment mises en attente par interruption_mask_all()
 */
void interruption_unmask_all(void);


#endif

