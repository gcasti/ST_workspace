/*
 * stm32f767_indicador_v1.c
 *
 *  Created on: 1 dic. 2021
 *      Author: gcasti
 */

#include "stm32f767_indicador_v1.h"

//extern TIM_HandleTypeDef htim4; /* Timer Buzzer off */
extern SPI_HandleTypeDef hspi2;
volatile uint8_t dato_temp[3];

static void MX_SPI2_Init(void);

/*
void BSP_Buzzer_Init()
{
	 GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOC_CLK_ENABLE();

	HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
//	/*Configure GPIO pin : BUZZER */
/*	GPIO_InitStruct.Pin = BUZZER_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);

}



/*
 * Función que prende el buzzer durante 'period' mili-segundos.
 */
/*void BSP_BuzzerBeep(uint32_t period)
{
	htim4.Init.Period = period;
	if (HAL_TIM_Base_Init(&htim4) != HAL_OK) {
		return;
	}
	//if (1) {
		HAL_TIM_Base_Start_IT(&htim4);
		HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_SET);
	//}
}

inline void BSP_BuzzerStop()
{
	HAL_GPIO_WritePin(BUZZER_PORT, BUZZER_PIN, GPIO_PIN_RESET);
	HAL_TIM_Base_Stop(&htim4);
}*/

void BSP_AdcInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(AD_TEMP_GPIO_PORT, AD_TEMP_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AD_A0_GPIO_PORT, AD_A0_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AD_PDWN_GPIO_PORT, AD_PDWN_PIN, GPIO_PIN_SET);
	HAL_GPIO_WritePin(AD_SPEED_GPIO_PORT,AD_SPEED_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AD_GAIN0_GPIO_PORT,AD_GAIN0_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AD_GAIN1_GPIO_PORT,AD_GAIN1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AD_EXTCLK_GPIO_PORT,AD_EXTCLK_PIN, GPIO_PIN_RESET);

	/*Configure GPIO pin : AD_TEMP_Pin */
	GPIO_InitStruct.Pin = AD_TEMP_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(AD_TEMP_GPIO_PORT, &GPIO_InitStruct);

	/*Configure GPIO pins : AD_A0_Pin AD_PDWN_Pin */
	GPIO_InitStruct.Pin = AD_A0_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(AD_A0_GPIO_PORT, &GPIO_InitStruct);

	/*Configure GPIO pins :AD_PDWN_Pin */
	GPIO_InitStruct.Pin = AD_PDWN_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(AD_PDWN_GPIO_PORT, &GPIO_InitStruct);

	/*Configure GPIO pins : AD_SPEED_Pin  */
	GPIO_InitStruct.Pin = AD_SPEED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(AD_SPEED_GPIO_PORT, &GPIO_InitStruct);

	/*Configure GPIO pins : AD_GAIN0_Pin  */
	GPIO_InitStruct.Pin = AD_GAIN0_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(AD_GAIN0_GPIO_PORT, &GPIO_InitStruct);

	/*Configure GPIO pins : AD_GAIN1_Pin  */
	GPIO_InitStruct.Pin = AD_GAIN1_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(AD_GAIN1_GPIO_PORT, &GPIO_InitStruct);

	/*Configure GPIO pin : AD_EXTCLK_Pin */
	GPIO_InitStruct.Pin = AD_EXTCLK_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(AD_EXTCLK_GPIO_PORT, &GPIO_InitStruct);

	/*Configure GPIO pin : DRDY_Pin */
/*	GPIO_InitStruct.Pin = AD_DRDY_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(AD_DRDY_GPIO_PORT, &GPIO_InitStruct);

	/* EXTI interrupt init*/
//	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	MX_SPI2_Init();

	}


static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}
