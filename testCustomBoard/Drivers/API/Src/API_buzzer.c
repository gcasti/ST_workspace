/**
 *  @brief Módulo para manejo del buzzer
 *  @author Ing. Guillermo L. Castiglioni
 *  @date 12/2021
 */

/** =====[Inclusión de dependencia privadas ]==========================*/
#include "API_buzzer.h"
#include "stm32f7xx_hal.h"
#include "stm32f767_indicador_v1.h"

TIM_HandleTypeDef htim4;

void Buzzer_Init()
{
	BSP_Buzzer_Init();
}

void Buzzer_Beep(uint32_t period)
{
	htim4.Init.Period = period;
	if (HAL_TIM_Base_Init(&htim4) !=  HAL_OK) {
		return;
	}
	HAL_TIM_Base_Start_IT(&htim4);
	HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);
}

inline void Buzzer_Stop()
{
	HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
	HAL_TIM_Base_Stop(&htim4);
}
