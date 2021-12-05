/*
 * stm32f767_indicador_v1.h
 *
 *  Created on: 1 dic. 2021
 *      Author: gcasti
 */

#ifndef BSP_STM32F767_INDICADOR_V1_STM32F767_INDICADOR_V1_H_
#define BSP_STM32F767_INDICADOR_V1_STM32F767_INDICADOR_V1_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include <stdbool.h>


#define BUZZER_PORT GPIOC
#define BUZZER_PIN GPIO_PIN_10

#define AD_TEMP_PIN GPIO_PIN_15
#define AD_TEMP_GPIO_PORT GPIOB
#define AD_A0_PIN GPIO_PIN_12
#define AD_A0_GPIO_PORT GPIOB
#define AD_PDWN_PIN GPIO_PIN_15
#define AD_PDWN_GPIO_PORT GPIOD
#define AD_SPEED_PIN GPIO_PIN_2
#define AD_SPEED_GPIO_PORT GPIOG
#define AD_GAIN0_PIN GPIO_PIN_3
#define AD_GAIN0_GPIO_PORT GPIOG
#define AD_GAIN1_PIN GPIO_PIN_4
#define AD_GAIN1_GPIO_PORT GPIOG
#define AD_EXTCLK_PIN GPIO_PIN_9
#define AD_EXTCLK_GPIO_PORT GPIOC
#define AD_DRDY_PIN GPIO_PIN_14
#define AD_DRDY_GPIO_PORT GPIOB



SPI_HandleTypeDef hspi2;
UART_HandleTypeDef huart;

void BSP_Buzzer_Init(void);
void BSP_BuzzerBeep(uint32_t period);
extern void BSP_BuzzerStop();

void BSP_UART_Init(void);

// Configura el ADC
void BSP_Adc_Init(void);

#endif /* BSP_STM32F767_INDICADOR_V1_STM32F767_INDICADOR_V1_H_ */
