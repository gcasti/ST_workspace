/*============= [ API_adc ] =================================================
 * Copyright 2021 Guillermo Luis Castiglioni <guillermo.castiglioni@gmail.com>
 * All rights reserved.
 *
 * Version: 0.1.0
 * Creation Date: 2021/11/01
 */
/*=====[Inclusion of own header]=============================================*/


#ifndef INC_API_ADC_H_
#define INC_API_ADC_H_

/*=====[Inclusions of public function dependencies]==========================*/
#include <stdint.h>
#include <stdbool.h>

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

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

typedef struct {
	gain_t gain  ;	  				// Indica la ganancia que se encuentra setea
	analog_input_t analog_input ;	// Indica el canal que se encuentra seleccionado
	speed_t speed;					// Indica la velocidad de adquisición
	pwr_t pwr;						// Indica si el modo de bajo consumo está activado
	float data;						// último dato adquirido
} adc_t;


/*=====[Definitions of public global variables]==============================*/


/*=====[Prototypes (declarations) of public functions]=======================*/

void adc_Init(adc_t *adc);

// Habilita la conversion de datos
void adc_Start();

// Detiene la conversion de datos
void adc_Stop();

// Actualiza el modo de  funcionamiento
void adc_Config(adc_t * adc);

bool_t adc_newData(void);

uint32_t adc_readData(void);

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

#endif /* INC_API_ADC_H_ */
