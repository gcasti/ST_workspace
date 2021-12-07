/*==========[Maquina de estado finito]========================================
 * Copyright 2021 Guillermo Luis Castiglioni <guillermo.castiglioni@gmail.com>
 * All rights reserved.
 *
 * Version: 0.1.0
 * Creation Date: 2021/11/01
 */
/*=====[Inclusion of own header]=============================================*/
#include "fsm.h"
#include "API_cmdUART.h"
#include "API_adc.h"
#include "API_buzzer.h"
#include <stdio.h>
/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/

const char estadoIdle[] = "En espera \n\r";
const char estadoConfig[] = "Modo configuración \n\r";
const char estadoAQ[] = "Adquiriendo datos \n\r";

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

typedef enum{
	IDLE ,
	CONFIG ,
	ACQUIRE
} fsmLoggState_t;

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/
adc_t adc1;
fsmLoggState_t fsmLoggState;
uint8_t *command;
volatile uint32_t data=0;
extern volatile uint32_t adc_data;

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

bool receiveParameters(cmd_t param, adc_t * adc);
void send_Status(adc_t * adc);
void fsmError( void );


/*=====[Implementations of public functions]=================================*/

void fsmInit( void )
{
	adc1.analog_input = CHANNEL_TEMP;
	adc1.gain = GAIN1;
	adc1.speed = LOW_SPEED;
	adc1.pwr = PWR_DISABLE;
	adc_Init(&adc1);
	printf("\n\r");
	printf("%s",estadoIdle);
	Buzzer_Beep(10);
   	fsmLoggState = IDLE;
}

void fsmUpdate(void)
{
	switch(fsmLoggState){
		case IDLE:
			if(true == cmdUart_Receive(command)){
				Buzzer_Beep(10);
				switch(*command){
					case configAQ:
						printf("%s",estadoConfig);
						fsmLoggState = CONFIG;
						break;
					case startAQ:
						printf("%s",estadoAQ);
						adc_Start();
						fsmLoggState = ACQUIRE;
						break;
					default:
						Buzzer_Beep(300);
						printf("COMANDO NO VALIDO \n\r");
						break;
					}
				}
			break;

		case CONFIG:
			if(true == cmdUart_Receive(command)){
				Buzzer_Beep(10);
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
						Buzzer_Beep(300);
						printf("COMANDO NO VALIDO \n\r");
						}
				}
			}
			break;

		case ACQUIRE:
			if(true == cmdUart_Receive(command)){
				Buzzer_Beep(10);
				switch(*command){
					case stopAQ:
						adc_Stop();
						printf("%s",estadoIdle);
						fsmLoggState = IDLE;
						break;
					case configAQ:
						printf("%s",estadoConfig);
						fsmLoggState = CONFIG;
						break;
					default:
						Buzzer_Beep(300);
						printf("COMANDO NO VALIDO \n\r");
						break;
				}
			}
			if(true == adc_newData())
			{
				data=adc_readData();
				printf("%x \n\r",adc_data);
			}
			break;

		default:
			fsmError();
			break;
	}
}

/*=====[Implementations of private functions]================================*/

bool receiveParameters(cmd_t param, adc_t * adc){
	bool retVal = true;
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
	printf("POWER: %d \n\r",adc->pwr);
	printf("Ganancia: %d \n\r",adc->gain);
	printf("Velocidad de adquisición: %d  \n\r", adc->speed);
	printf("Canal de entrada: %d \n\r", adc->analog_input);
	printf("******************************************** \n\r");
}

void fsmError( void ){

}

/*=====[Implementations of interrupt functions]==============================*/

