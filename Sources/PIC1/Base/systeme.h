
#ifndef SYSTEME_H_INCLUDED
#define SYSTEME_H_INCLUDED

/** Initialiser l'ensemble du système et des composants de la carte
 */
void system_init(void);

/** Fonction appelée par les appels bloquants pour permettre de vérifier
 * des états normalement gérés par interruption
 */
void system_perform_states_check(void);

#endif
