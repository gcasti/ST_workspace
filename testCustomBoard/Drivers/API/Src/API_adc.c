/**
 *  @brief Módulo para configuración y operación del ADC externo
 *  @author Ing. Guillermo L. Castiglioni
 *  @date 12/2021
 */

/** =====[Inclusión de dependencia privadas ]==========================*/
#include "API_adc.h"
#include "stm32f7xx_hal.h"
#include "stm32f767_indicador_v1.h"

/** =====[Varibles publicas que serán actualizada por la rutina de interrupción ]==========================*/

// TODO: Implementar la rutina de interrupción como una función de callbak
// para limitar la visibilidad de estas variables
volatile bool_t newdata = false;		// Indica cuando existe un nuevo dato disponible
volatile uint32_t adc_data ;

/** =====[Definición de varibles privadas]==========================*/
static	bool_t adc_state = false;	// Estado de la adquisición


/** =====[Definición de funciones privadas ]==========================*/
static void adc_SetGain(gain_t gain_pga);				// Configura la ganancia del PGA
static void adc_SetInput(analog_input_t analog_input);	// Selecciona el canal de entrada
static void adc_SetSpeed(speed_t speed);				// Configura la velocidad de adquisición
static void adc_SetPowerdown(pwr_t pwr);				// Coloca el ADC en modo de bajo consumo
static void adc_HwConfig(adc_t * adc);					// Configura el hardware

static bool_t getStatus(void);							// Devuelve el estado de operación
static float temperatureData(uint32_t code);
static float tensionData(uint32_t code);

/** =====[Implementación de funciones públicas ]==========================*/

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

bool_t adc_newData(void){
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

/** =====[Implementación de funciones privadas ]==========================*/
static float tensionData(uint32_t code){
	return (float)code*298.023e-9;
}

static float temperatureData(uint32_t code){
	float temperature;
	temperature = 379e-6*(tensionData(code)-111.7e-3)+25;

	return temperature;
}

static bool_t getStatus()
{	return adc_state;
	}

static void adc_HwConfig(adc_t * adc){
	adc_SetGain(adc->gain);
	adc_SetInput(adc->analog_input);
	adc_SetSpeed(adc->speed);
	adc_SetPowerdown(adc->pwr);
}

static void adc_SetGain(gain_t gain_pga)
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

static void adc_SetInput(analog_input_t analog_input)
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

static void adc_SetSpeed(speed_t speed)
{
	HAL_GPIO_WritePin(AD_SPEED_GPIO_PORT,AD_SPEED_PIN, speed);
}

static void adc_SetPowerdown(pwr_t pwr)
{
	HAL_GPIO_WritePin(AD_PDWN_GPIO_PORT, AD_PDWN_PIN, pwr);
}






















