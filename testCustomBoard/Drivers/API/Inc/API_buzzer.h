/*============= [ API_adc ] =================================================
 * Copyright 2021 Guillermo Luis Castiglioni <guillermo.castiglioni@gmail.com>
 * All rights reserved.
 *
 * Version: 0.1.0
 * Creation Date: 2021/11/01
 */
/*=====[Inclusion of own header]=============================================*/


#ifndef API_INC_API_BUZZER_H_
#define API_INC_API_BUZZER_H_

/*=====[Inclusions of public function dependencies]==========================*/
#include <stdint.h>
#include <stdbool.h>

/*=====[Definition macros of public constants]===============================*/

/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Prototypes (declarations) of public functions]=======================*/

void Buzzer_Init(void);
void Buzzer_Beep(uint32_t period);
void Buzzer_Stop();

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C - end]===========================================================*/

#endif /* API_INC_API_BUZZER_H_ */
