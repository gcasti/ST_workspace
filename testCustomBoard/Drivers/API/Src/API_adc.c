/*============= [ API_adc ] =================================================
 * Copyright 2021 Guillermo Luis Castiglioni <guillermo.castiglioni@gmail.com>
 * All rights reserved.
 *
 * Version: 0.1.0
 * Creation Date: 2021/11/01
 */
/*=====[Inclusion of own header]=============================================*/

#include "API_adc.h"
#include "stm32f7xx_hal.h"
#include "stm32f767_indicador_v1.h"

/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of public global variables]==============================*/

volatile bool newdata = false;		// Indica cuando existe un nuevo dato disponible
volatile uint32_t adc_data ;

/*=====[Definitions of external public global variables]=====================*/
/*=====[Definitions of private global variables]=============================*/

static	bool adc_state = false;	// Estado de la adquisición


/*=====[Prototypes (declarations) of private functions]======================*/

static void adc_SetGain(gain_t gain_pga);				// Configura la ganancia del PGA
static void adc_SetInput(analog_input_t analog_input);	// Selecciona el canal de entrada
static void adc_SetSpeed(speed_t speed);				// Configura la velocidad de adquisición
static void adc_SetPowerdown(pwr_t pwr);				// Coloca el ADC en modo de bajo consumo
static void adc_HwConfig(adc_t * adc);					// Configura el hardware

static bool getStatus(void);							// Devuelve el estado de operación
static float temperatureData(uint32_t code);
static float tensionData(uint32_t code);

/*=====[Implementations of public functions]=================================*/

void adc_Init(adc_t * adc){
	BSP_Adc_Init();
	adc_HwConfig(adc);
	adc_Stop(adc);
}

void adc_Start(void){
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
    adc_state = true;
};

void adc_Stop(void){
	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
	adc_state = false;
};

bool adc_newData(void){
	return newdata;
};

float adc_readData(adc_t * adc){
	float retVal=0;

	if(CHANNEL_TEMP == adc->analog_input){
		retVal = temperatureData(adc_data);
	}else{
		retVal = tensionData(adc_data);
	}
	if(adc_newData()){
		newdata = false;
	}
	return retVal;
}

void adc_Config(adc_t * adc){
	if (true == getStatus()){
		adc_Stop();
		}
	adc_HwConfig(adc);
}


/*=====[Implementations of private functions]================================*/
float tensionData(uint32_t code){

	return (float)code*298.023e-9;
}

float temperatureData(uint32_t code){
	float temperature;
	temperature = 379e-6*(tensionData(code)-111.7e-3)+25;

	return temperature;
}


bool getStatus()
{	return adc_state;
	}

void adc_HwConfig(adc_t * adc){
	adc_SetGain(adc->gain);
	adc_SetInput(adc->analog_input);
	adc_SetSpeed(adc->speed);
	adc_SetPowerdown(adc->pwr);
}
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






















