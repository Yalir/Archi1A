
#ifndef SYSTEME_H_INCLUDED
#define SYSTEME_H_INCLUDED

/** Initialiser l'ensemble du syst�me et des composants de la carte
 */
void system_init(void);

/** Fonction appel�e par les appels bloquants pour permettre de v�rifier
 * des �tats normalement g�r�s par interruption
 */
void system_perform_states_check(void);

#endif
