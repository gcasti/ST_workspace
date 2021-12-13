/**
 *  @brief Módulo para recepción de comandos por la UART
 *  @author Ing. Guillermo L. Castiglioni
 *  @date 12/2021
 */

#ifndef API_INC_API_CMDUART_H_
#define API_INC_API_CMDUART_H_

/** =====[Inclusión de dependencia públicas ]==========================*/
#include <stdbool.h>
#include <stdint.h>


/**
 * @brief	Definición de comandos para operación y configuración del ADC
 */
typedef enum{
	configAQ 		= 0x00,     /**< configAQ */
	exitCONFIG 		= 0x01,   	/**< exitCONFIG */
	startAQ			= 0x02,     /**< startAQ */
	stopAQ			= 0x03,     /**< stopAQ */
	cmdGAIN1		= 0x04,     /**< cmdGAIN1 */
	cmdGAIN2		= 0x05,     /**< cmdGAIN2 */
	cmdGAIN64		= 0x06,     /**< cmdGAIN64 */
	cmdGAIN128		= 0x07,    	/**< cmdGAIN128 */
	cmdCHANNEL_IN1	= 0x08, 	/**< cmdCHANNEL_IN1 */
	cmdCHANNEL_IN2	= 0x09, 	/**< cmdCHANNEL_IN2 */
	cmdCHANNEL_TEMP = 0x10,		/**< cmdCHANNEL_TEMP */
	cmdLOW_SPEED	= 0x11,   	/**< cmdLOW_SPEED */
	cmdHIGH_SPEED	= 0x12,  	/**< cmdHIGH_SPEED */
	cmdPWR_ENABLE	= 0x13,  	/**< cmdPWR_ENABLE */
	cmdPWR_DISABLE	= 0x14, 	/**< cmdPWR_DISABLE */
	cmdLAST                		/**< cmdLAST */
} cmd_t;

typedef bool bool_t;


/**
 * @brief Inicializa el módulo UART para recepción de comandos y envío de datos
 */
void cmdUart_Init(void);

/**
 * @brief Lee un dato recibido y verifica si es un comando válido
 * @param cmd		// Byte que se lee desde la UART
 * @return			// True: Comando válido
 * 					// False: Comando inválido
 */
bool_t cmdUart_Receive(uint8_t * cmd);

/**
 * @brief Envía una cadena de carácteres mediante el módulo UART
 * @param pstring 	// Puntero a la cadena de cáracteres
 */
void uartSendString(char * pstring);


#endif /* API_INC_API_CMDUART_H_ */
