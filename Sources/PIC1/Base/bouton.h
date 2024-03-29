
#ifndef BOUTON_H_INCLUDED
#define BOUTON_H_INCLUDED

/** @brief Indique si le bouton RB4 (1e bouton apr�s le reset du PIC#1) est enfonc�
 *
 * @return 1 si le bouton RB4 est enfonc�, 0 sinon
 */
int bouton_RB4_on(void);

/** @brief Indique si le bouton RB5 (2e bouton apr�s le reset du PIC#1) est enfonc�
 *
 * @return 1 si le bouton RB5 est enfonc�, 0 sinon
 */
int bouton_RB5_on(void);

/** @brief Indique si le bouton a �t� enfonc� alors qu'il �tait relach�.
 * Cette fonction renvoie FALSE si le bouton n'a pas �t� relach� depuis le
 * dernier appel � cette fonction.
 *
 * @return 0 si le bouton n'a pas �t� enfonc�, !0 sinon
 */
int bouton_RB4_pressed(void);
int bouton_RB5_pressed(void);

#endif
