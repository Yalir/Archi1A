
#ifndef COMMANDS_H
#define COMMANDS_H

/** Initialise les commandes
 */
void commands_init(void);

/** Affiche un message d'aide
 */
void command_help(void);

/** Efface l'écran de l'hyperterminal
 */
void command_clear(void);

/** Demande à l'utilisateur de combien de case il veut avancer
 * et sur quel PIC, et avance.
 */
void command_avancer(void);

/** Demande à l'utilisateur de combien de case il veut reculer
 * et sur quel PIC, et recule.
 */
void command_reculer(void);

/** Affiche la séquence d'alerte
 */
void command_alert(void);

#endif
