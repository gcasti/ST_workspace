/*=====[Module Name]===========================================================
 * Copyright 2019 Esteban Daniel VOLENTINI <evolentini@gmail.com>
 * All rights reserved.
 * License: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.1.0
 * Creation Date: 2019/03/01
 */

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef API_INC_API_CMDUART_H_
#define API_INC_API_CMDUART_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/
typedef bool bool_t;

typedef enum{
	configAQ 		= 0x00,
	exitCONFIG 		= 0x01,
	startAQ			= 0x02,
	stopAQ			= 0x03,
	cmdGAIN1		= 0x04,
	cmdGAIN2		= 0x05,
	cmdGAIN64		= 0x06,
	cmdGAIN128		= 0x07,
	cmdCHANNEL_IN1	= 0x08,
	cmdCHANNEL_IN2	= 0x09,
	cmdCHANNEL_TEMP = 0x10,
	cmdLOW_SPEED	= 0x11,
	cmdHIGH_SPEED	= 0x12,
	cmdPWR_ENABLE	= 0x13,
	cmdPWR_DISABLE	= 0x14,
	cmdLAST
} cmd_t;

/*=====[Definitions of public global variables]==============================*/

/*=====[Prototypes (declarations) of public functions]=======================*/

// Inicializa la uart
void cmdUart_Init(void);

// Recibe un comando desde la uart
bool_t cmdUart_Receive(uint8_t * cmd);

void sendData(void);



#endif /* API_INC_API_CMDUART_H_ */
