/**
 *  Board Support Package
 *  BSP para placa Indicador V1
 *  @author Ing. Guillermo L. Castiglioni
 *  @date 12/2021
 */

#ifndef BSP_STM32F767_INDICADOR_V1_STM32F767_INDICADOR_V1_H_
#define BSP_STM32F767_INDICADOR_V1_STM32F767_INDICADOR_V1_H_

/** =====[Inclusión de dependencias públicas ]==========================*/
#include "stm32f7xx_hal.h"
#include <stdbool.h>

/**
 * Definición de macros para asignación de pines para manejo del Buzzer
 */
#define BUZZER_PORT GPIOA
#define BUZZER_PIN GPIO_PIN_15

/**
 * Definición de macros para asignación de pines para manejo del ADC
 */
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

// Variables públicas
SPI_HandleTypeDef hspi2;
UART_HandleTypeDef UartHandle;

typedef bool bool_t;

/**
 * @brief Inicio módulo UART parámetros predefinidos en el código
 * @return 	true: inicio correcto
 * 			false: error de inicialización
 */
bool_t BSP_UART_Init(void);

/**
 * @brief Inicia todos los periféricos para operación del ADC
 */
void BSP_Adc_Init(void);

/**
 * @brief Inicia los periféricos para manejo del buzzer
 */
void BSP_Buzzer_Init(void);

#endif /* BSP_STM32F767_INDICADOR_V1_STM32F767_INDICADOR_V1_H_ */
