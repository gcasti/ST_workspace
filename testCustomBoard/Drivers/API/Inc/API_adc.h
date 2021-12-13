/**
 *  @brief Módulo para configuración y operación del ADC externo
 *  @author Ing. Guillermo L. Castiglioni
 *  @date 12/2021
 */

#ifndef INC_API_ADC_H_
#define INC_API_ADC_H_

/** =====[Inclusión de dependencia públicas ]==========================*/
#include <stdint.h>
#include <stdbool.h>

/** =====[Definición de tipos de datos públicos ]==========================*/
typedef bool bool_t;

typedef enum {GAIN1 , GAIN2 , GAIN64 , GAIN128 } gain_t;
typedef enum {CHANNEL_IN1 , CHANNEL_IN2 , CHANNEL_TEMP} analog_input_t;

typedef enum {
	LOW_SPEED = 0,
	HIGH_SPEED = 1
} speed_t;

typedef enum {
	PWR_ENABLE = 0,
	PWR_DISABLE = 1
} pwr_t;

/** =====[Inclusión de dependencia públicas ]==========================*/
// Estructura que almacena el estado de configuración del ADC
typedef struct {
	gain_t gain  ;	  				// Indica la ganancia que se encuentra seteada
	analog_input_t analog_input ;	// Indica el canal que se encuentra seleccionado
	speed_t speed;					// Indica la velocidad de adquisición
	pwr_t pwr;						// Indica si el modo de bajo consumo está activado
} adc_t;

/** =====[Declaración de funciones públicas ]==========================*/
/**
 * @brief Inicializa el módulo ADC con la configuración de la estructura
 * @param adc	// Posee el estado de configuración del ADC
 */
void adc_Init(adc_t *adc);

/**
 * @brief Habilita la conversión de datos
 */
void adc_Start();

/**
 * @brief // Detiene la conversion de datos
 */
void adc_Stop();

/**
 * @brief Actualiza el modo de funcionamiento del ADC
 * @param adc 	// Posee el estado de configuración del ADC
 */
void adc_Config(adc_t * adc);

/**
 * @brief Indica si existe un nuevo dato disponible sin leer
 * @return 	true: datos disponible
 * 			false: no hay dato disponible
 */
bool_t adc_newData(void);

/**
 * @brief Lectua de un dato adquirido por el ADC
 * @param adc
 * @return	Dato según la opción de configuración del ADC
 */
float adc_readData(adc_t * adc);

#endif /* INC_API_ADC_H_ */
