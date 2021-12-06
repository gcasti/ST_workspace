/*
 * fsm.c
 *
 *  Created on: Dec 5, 2021
 *      Author: gcasti
 */
#include "fsm.h"
#include "API_cmdUART.h"
#include "API_adc.h"

typedef enum{
	IDLE ,
	CONFIG ,
	ACQUIRE
} fsmLoggState_t;

adc_t adc1;
const char estadoIdle[] = "\n\rEn espera \n\r";
const char estadoConfig [] = "Modo configuración \n\r";
const char estadoAQ[] = "ADquiriendo datos \n\r";

void fsmError( void );
fsmLoggState_t fsmLoggState;
uint8_t *command;

// Funcion privada de FSM
bool_t receiveParameters(cmd_t param, adc_t * adc){
	bool_t retVal = true;
	switch(param){
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

void send_Status(adc_t * adc){
	printf("************ CONFIGURACION ***************** \n\r");
	printf("POWER: %d \n\r",adc->gain);
	printf("Ganancia: %d \n\r",adc->gain);
	printf("Velocidad de adquisición: %d  \n\r", adc->speed);
	printf("Canal de entrada: %d \n\r", adc->analog_input);
	printf("******************************************** \n\r");
}

void fsmInit( void )
{
	adc1.analog_input = CHANNEL_TEMP;
	adc1.gain = GAIN1;
	adc1.speed = LOW_SPEED;
	adc1.pwr = PWR_DISABLE;
	adc_Init(&adc1);

	#ifdef NUCLEO
		BSP_LED_Init(LED1);
		BSP_LED_Init(LED2);
		BSP_LED_Init(LED3);
		BSP_LED_Off(LED1);
		BSP_LED_Off(LED2);
		BSP_LED_Off(LED3);
	#endif

	printf("%s",estadoIdle);
   	fsmLoggState = IDLE;   // Set initial state
}

void fsmUpdate(void)
{
	switch(fsmLoggState){
		case IDLE:
			// Verifico estado
			BSP_LED_On(LED1);
			BSP_LED_Off(LED2);
			BSP_LED_Off(LED3);

			if(true == cmdUart_Receive(command)){
				switch(*command){
					case configAQ:
						printf("%s",estadoConfig);
						fsmLoggState = CONFIG;
						break;
					case startAQ:
						printf("%s",estadoAQ);
						fsmLoggState = ACQUIRE;
						break;
					default:
						printf("COMANDO NO VALIDO \n\r");
						break;
					}
				}
			break;

		case CONFIG:
			// Verifico estado
			BSP_LED_Off(LED1);
			BSP_LED_On(LED2);
			BSP_LED_Off(LED3);

			if(true == cmdUart_Receive(command)){
				if(exitCONFIG == *command){
					send_Status(&adc1);
					printf("%s",estadoIdle);
					fsmLoggState = IDLE;
				}else{
					if(true == receiveParameters(*command,&adc1))
					{
						printf("Parámetro recibido \n\r");
						adc_Config(&adc1);
						}else{
						printf("COMANDO NO VALIDO \n\r");
						}
				}
			}
			break;

		case ACQUIRE:
			// Verifico estado
			BSP_LED_Off(LED1);
			BSP_LED_Off(LED2);
			BSP_LED_On(LED3);
			// Adquisición

			// Chequeo UART
			if(true == cmdUart_Receive(command)){
				switch(*command){
					case stopAQ:
						printf("%s",estadoIdle);
						fsmLoggState = IDLE;
						break;
					case configAQ:
						printf("%s",estadoConfig);
						fsmLoggState = CONFIG;
						break;
					default:
						printf("COMANDO NO VALIDO \n\r");
						break;
				}
			}
			if(true == adc_newData(&adc1))
			{
				//Lectura y envío de datos por la UART
			}
			break;

		default:
			fsmError();
			break;
	}
}


void fsmError( void ){

}
