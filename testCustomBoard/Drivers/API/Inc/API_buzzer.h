/**
 *  @brief Módulo para manejo del buzzer
 *  @author Ing. Guillermo L. Castiglioni
 *  @date 12/2021
 */

#ifndef API_INC_API_BUZZER_H_
#define API_INC_API_BUZZER_H_

/** =====[Inclusión de dependencia públicas ]==========================*/
#include <stdint.h>
#include <stdbool.h>

/** =====[Definición de funciones públicas ]==========================*/
/**
 * @brief Inicializa los periféricos para control del buzzer
 */
void Buzzer_Init(void);

/**
 * @brief Activa el buzzer por un determinado tiempo
 * @param period 		Tiempo en milisegundos
 */
void Buzzer_Beep(uint32_t period);

void Buzzer_Stop();


#endif /* API_INC_API_BUZZER_H_ */
