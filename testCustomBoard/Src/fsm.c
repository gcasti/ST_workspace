/**
 *  @brief Máquina de estado
 *  @author Ing. Guillermo L. Castiglioni
 *  @date 12/2021
 */

/** =====[Inclusión de dependencia privadas ]==========================*/
#include "fsm.h"
#include "API_cmdUART.h"
#include "API_adc.h"
#include "API_buzzer.h"
#include <stdio.h>

/** =====[Definición de constantes privadas ]==========================*/
const char estadoIdle[] = "En espera \n\r";
const char estadoConfig[] = "Modo configuración \n\r";
const char estadoAQ[] = "Adquiriendo datos \n\r";

/** =====[Definición de tipos de datos provados ]==========================*/
typedef enum {
	IDLE, CONFIG, ACQUIRE
} fsmLoggState_t;

/** =====[ Definición de variables privadas]=============================*/
static adc_t adc1;
static fsmLoggState_t fsmLoggState;
static uint8_t *command;
static float data = 0;

/** =====[Definición de funciones privadas ]==========================*/
static bool receiveParameters(cmd_t param, adc_t *adc);
static void send_Status(adc_t *adc);
static void fsmError(void);

/** =====[Implementación de funciones públicas ]==========================*/

void fsmInit(void) {
	adc1.analog_input = CHANNEL_TEMP;
	adc1.gain = GAIN1;
	adc1.speed = LOW_SPEED;
	adc1.pwr = PWR_DISABLE;
	adc_Init(&adc1);
	uartSendString("\n\r");
	uartSendString((char*) estadoIdle);
	Buzzer_Beep(10);
	fsmLoggState = IDLE;
}

void fsmUpdate(void) {
	switch (fsmLoggState) {
	case IDLE:
		if (true == cmdUart_Receive(command)) {
			Buzzer_Beep(10);
			switch (*command) {
			case configAQ:
				uartSendString((char*) estadoConfig);
				fsmLoggState = CONFIG;
				break;
			case startAQ:
				uartSendString((char*) estadoAQ);
				adc_Start();
				fsmLoggState = ACQUIRE;
				break;
			default:
				Buzzer_Beep(300);
				uartSendString("COMANDO NO VALIDO \n\r");
				break;
			}
		}
		break;

	case CONFIG:
		if (true == cmdUart_Receive(command)) {
			Buzzer_Beep(10);
			if (exitCONFIG == *command) {
				send_Status(&adc1);
				uartSendString((char*) estadoIdle);
				fsmLoggState = IDLE;
			} else {
				if (true == receiveParameters(*command, &adc1)) {
					uartSendString("Parámetro recibido \n\r");
					adc_Config(&adc1);
				} else {
					Buzzer_Beep(300);
					uartSendString("COMANDO NO VALIDO \n\r");
				}
			}
		}
		break;

	case ACQUIRE:
		if (true == cmdUart_Receive(command)) {
			Buzzer_Beep(10);
			switch (*command) {
			case stopAQ:
				adc_Stop();
				uartSendString((char*) estadoIdle);
				fsmLoggState = IDLE;
				break;
			case configAQ:
				uartSendString((char*) estadoConfig);
				fsmLoggState = CONFIG;
				break;
			default:
				Buzzer_Beep(300);
				uartSendString("COMANDO NO VALIDO \n\r");
				break;
			}
		}
		if (true == adc_newData()) {
			data = adc_readData(&adc1);
			printf("%f \n\r", data);
		}
		break;

	default:
		fsmError();
		break;
	}
}

/** =====[Implementación de funciones privadas ]==========================*/

/**
 * @brief Verifica si el dato recibido es un parámetro de configuración válido
 * y actualiza la estructura de configuración del ADC
 * @param param 	Dato recibido
 * @param adc		Estructura de configuración del ADC
 * @return			true = parámetro válido
 *					false = el dato no es un parámetro válido
 */
bool_t receiveParameters(cmd_t param, adc_t *adc) {
	bool_t retVal = true;
	switch (param) {
	case cmdGAIN1:
		adc->gain = GAIN1;
		break;
	case cmdGAIN2:
		adc->gain = GAIN2;
		break;
	case cmdGAIN64:
		adc->gain = GAIN64;
		break;
	case cmdGAIN128:
		adc->gain = GAIN128;
		break;
	case cmdCHANNEL_IN1:
		adc->analog_input = CHANNEL_IN1;
		break;
	case cmdCHANNEL_IN2:
		adc->analog_input = CHANNEL_IN2;
		break;
	case cmdCHANNEL_TEMP:
		adc->analog_input = CHANNEL_TEMP;
		break;
	case cmdLOW_SPEED:
		adc->speed = LOW_SPEED;
		break;
	case cmdHIGH_SPEED:
		adc->speed = HIGH_SPEED;
		break;
	case cmdPWR_ENABLE:
		adc->pwr = PWR_ENABLE;
		break;
	case cmdPWR_DISABLE:
		adc->pwr = PWR_DISABLE;
		break;
	default:
		retVal = false;
		break;
	}
	return retVal;
}

/**
 * @brief Envía por la UAR el estado de configuración del módulo ADC
 * @param adc		Estructura de configuración del ADC
 */
void send_Status(adc_t *adc) {
	printf("************ CONFIGURACION ***************** \n\r");
	printf("POWER: %d \n\r", adc->pwr);
	printf("Ganancia: %d \n\r", adc->gain);
	printf("Velocidad de adquisición: %d  \n\r", adc->speed);
	printf("Canal de entrada: %d \n\r", adc->analog_input);
	printf("******************************************** \n\r");
}

void fsmError(void) {

}

