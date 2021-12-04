/*=====[Module Name]===========================================================
 * Copyright 2019 Esteban Daniel VOLENTINI <evolentini@gmail.com>
 * All rights reserved.
 * License: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.1.0
 * Creation Date: 2019/03/01
 */

/*=====[Inclusion of own header]=============================================*/

#include "API_adc.h"
#include "stm32f7xx_hal.h"
#include "stm32f767_indicador_v1.h"

/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/


/*=====[Prototypes (declarations) of private functions]======================*/

void adc_SetGain(gain_t gain_pga);	// Configura la ganancia del PGA
void adc_SetInput(analog_input_t analog_input);	// Selecciona el canal de entrada
void adc_SetSpeed(speed_t speed);	// Configura la velocidad de adquisición
void adc_SetPowerdown(pwr_t pwr);		// Coloca el ADC en modo de bajo consumo


/*=====[Implementations of private functions]=================================*/

void adc_SetGain(gain_t gain_pga)
{
	switch(gain_pga){
		case GAIN1:
			HAL_GPIO_WritePin(AD_GAIN0_GPIO_PORT,AD_GAIN0_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(AD_GAIN1_GPIO_PORT,AD_GAIN1_PIN, GPIO_PIN_RESET);
			break;
		case GAIN2:
			HAL_GPIO_WritePin(AD_GAIN0_GPIO_PORT,AD_GAIN0_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(AD_GAIN1_GPIO_PORT,AD_GAIN1_PIN, GPIO_PIN_RESET);
			break;
		case GAIN64:
			HAL_GPIO_WritePin(AD_GAIN0_GPIO_PORT,AD_GAIN0_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(AD_GAIN1_GPIO_PORT,AD_GAIN1_PIN, GPIO_PIN_SET);
			break;
		case GAIN128:
			HAL_GPIO_WritePin(AD_GAIN0_GPIO_PORT,AD_GAIN0_PIN, GPIO_PIN_SET);
			HAL_GPIO_WritePin(AD_GAIN1_GPIO_PORT,AD_GAIN1_PIN, GPIO_PIN_SET);
			break;
		default:
			HAL_GPIO_WritePin(AD_GAIN0_GPIO_PORT,AD_GAIN0_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(AD_GAIN1_GPIO_PORT,AD_GAIN1_PIN, GPIO_PIN_RESET);
			break;
	}
}

void adc_SetInput(analog_input_t analog_input)
{
	switch(analog_input){
		case CHANNEL_IN1:
			HAL_GPIO_WritePin(AD_TEMP_GPIO_PORT,AD_TEMP_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(AD_A0_GPIO_PORT,AD_A0_PIN, GPIO_PIN_RESET);
			break;
		case CHANNEL_IN2:
			HAL_GPIO_WritePin(AD_TEMP_GPIO_PORT,AD_TEMP_PIN, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(AD_A0_GPIO_PORT,AD_A0_PIN, GPIO_PIN_SET);
			break;
		case CHANNEL_TEMP:
			HAL_GPIO_WritePin(AD_TEMP_GPIO_PORT,AD_TEMP_PIN, GPIO_PIN_SET);
			break;
		default:
			break;
	}
}

void adc_SetSpeed(speed_t speed)
{
	HAL_GPIO_WritePin(AD_SPEED_GPIO_PORT,AD_SPEED_PIN, speed);
}

void adc_SetPowerdown(pwr_t pwr)
{
	HAL_GPIO_WritePin(AD_PDWN_GPIO_PORT, AD_PDWN_PIN, pwr);
}


/*=====[Implementations of public functions]=================================*/

void adcInit(adc_t * init_adc){
	BSP_AdcInit();
	adc_SetGain(init_adc->gain);
	adc_SetInput(init_adc->analog_input);
	adc_SetSpeed(init_adc->speed);
	adc_SetPowerdown(init_adc->pwr);
}

// Habilita la conversion de datos
void adc_Go(void){
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
};

// Detiene la conversion de datos
void adc_Stop(void){
	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
};


/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/

























