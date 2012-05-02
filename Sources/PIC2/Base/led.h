#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

/** @brief Allume la LED demand�e
 *
 * Les indices de LED accept�s sont compris entre 0 et 7 inclus
 * Si un indice incorrect est donn�, led_alert() est appel�e.
 *
 * @param i L'indice de la LED � allumer, compris entre 0 et 7 inclus
 */
void led_on(int i);


/** @brief Eteint la LED demand�e
 *
 * Les indices de LED accept�s sont compris entre 0 et 7 inclus
 * Si un indice incorrect est donn�, led_alert() est appel�e.
 *
 * @param i L'indice de la LED � �teindre, compris entre 0 et 7 inclus
 */
void led_off(int i);


/** @brief Lance la s�quence 1 sur les LED
 *
 * La s�quence 1 allume � la suite l'ensemble des LED pendant 10 tours
 */
void led_sequence1(void);


/** @brief Lance la s�quence 2 sur les LED
 *
 * La s�quence 2 allume led LED paires puis celles impaires pendant 10 tours
 */
void led_sequence2(void);


/** @brief Affiche la valeur donn�e en binaire � l'aide des LED
 *
 * Ex: la valeur 6 allumera la 3e et 4e LED pour former la valeur binaire 6
 *
 * @param valeur La valeur d�cimale � afficher en binaire
 */
void led_afficher_int(unsigned char valeur);

/** @brief Allume et �teint toutes les LEDs en m�me temps pendant un nombre
 * infini de tours. Cette fonction ne se termine jamais.
 */
void led_alert(void);

#endif
