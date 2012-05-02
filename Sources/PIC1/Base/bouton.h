#ifndef BOUTON_H_INCLUDED
#define BOUTON_H_INCLUDED

/** @brief Indique si le bouton RB4 (1e bouton après le reset du PIC#1) est enfoncé
 *
 * @return 1 si le bouton RB4 est enfoncé, 0 sinon
 */
int bouton_RB4_on(void);

/** @brief Indique si le bouton RB5 (2e bouton après le reset du PIC#1) est enfoncé
 *
 * @return 1 si le bouton RB5 est enfoncé, 0 sinon
 */
int bouton_RB5_on(void);

#endif
