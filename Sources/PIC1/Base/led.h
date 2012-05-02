#ifndef LED_H_INCLUDED
#define LED_H_INCLUDED

/** @brief Allume la LED demandée
 *
 * Les indices de LED acceptés sont compris entre 0 et 7 inclus
 * Si un indice incorrect est donné, led_alert() est appelée.
 *
 * @param i L'indice de la LED à allumer, compris entre 0 et 7 inclus
 */
void led_on(int i);


/** @brief Eteint la LED demandée
 *
 * Les indices de LED acceptés sont compris entre 0 et 7 inclus
 * Si un indice incorrect est donné, led_alert() est appelée.
 *
 * @param i L'indice de la LED à éteindre, compris entre 0 et 7 inclus
 */
void led_off(int i);


/** @brief Lance la séquence 1 sur les LED
 *
 * La séquence 1 allume à la suite l'ensemble des LED pendant 10 tours
 */
void led_sequence1(void);


/** @brief Lance la séquence 2 sur les LED
 *
 * La séquence 2 allume led LED paires puis celles impaires pendant 10 tours
 */
void led_sequence2(void);


/** @brief Affiche la valeur donnée en binaire à l'aide des LED
 *
 * Ex: la valeur 6 allumera la 3e et 4e LED pour former la valeur binaire 6
 *
 * @param valeur La valeur décimale à afficher en binaire
 */
void led_afficher_int(unsigned char valeur);

/** @brief Allume et éteint toutes les LEDs en même temps pendant un nombre
 * infini de tours. Cette fonction ne se termine jamais.
 */
void led_alert(void);

#endif
