/*=====[Module Name]===========================================================
 * Copyright 2019 Esteban Daniel VOLENTINI <evolentini@gmail.com>
 * All rights reserved.
 * License: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.1.0
 * Creation Date: 2019/03/01
 */

/*=====[Inclusion of own header]=============================================*/

#include "API_cmdUART.h"
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

/*=====[Implementations of public functions]=================================*/

/*=====[Implementations of interrupt functions]==============================*/

#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


void cmdUart_Init(void){
	BSP_UART_Init();
}


cmd_t cmdUart_ReadCommand(void){
}

bool_t cmdUart_Receive(uint8_t* cmd){
	bool_t retVal = true;
	uint8_t cmd_temp[3];

	if(HAL_UART_Receive(&huart, cmd_temp , 1, 10) == HAL_OK){
		switch(cmd_temp[0]){
			case configAQ:
			case exitCONFIG:
			case startAQ:
			case stopAQ:
				*cmd=cmd_temp[0];
				retVal = true;
				break;
			default:
				retVal = false;
				break;
			}
	}
	else{retVal = false;
		}

	return retVal;
}


PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART3 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}


