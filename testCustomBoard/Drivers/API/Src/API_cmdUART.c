/**
 *  @brief Módulo para recepción de comandos por la UART
 *  @author Ing. Guillermo L. Castiglioni
 *  @date 12/2021
 */
/** =====[Inclusión de dependencia privadas ]==========================*/

#include "API_cmdUART.h"
#include "stm32f7xx_hal.h"
#include "stm32f767_indicador_v1.h"
#include <stdio.h>
#include <string.h>

/** =====[Definición de funciones privadas ]==========================*/
static void sendParameters(void);

#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
 set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/** =====[Definición de funciones públicas ]==========================*/
void cmdUart_Init(void) {
	BSP_UART_Init();
	sendParameters();
}

bool_t cmdUart_Receive(uint8_t *cmd) {
	bool_t retVal = false;
	uint8_t cmd_temp = 0;

	if (HAL_UART_Receive(&UartHandle, &cmd_temp, 1, 10) == HAL_OK) {
		if (cmdLAST > cmd_temp) {
			*cmd = cmd_temp;
			retVal = true;
		} else
			uartSendString("\n\r Dato no valido \n\r");
	}
	return retVal;
}

void uartSendString(char *pstring) {
	HAL_UART_Transmit(&UartHandle, (uint8_t*) pstring,
			strlen(pstring) / sizeof(char), 1000);
}

/** =====[Implementación de funciones privadas]==========================*/

static void sendParameters() {
	uartSendString("\n\r **************************** \r");
	uartSendString("\n\r * Modulo UART inicializado   \r");
	uartSendString("\n\r * Baud Rate: ");
	uartSendString("115200");
	if (UART_STOPBITS_1 == UartHandle.Init.StopBits) {
		uartSendString("\n\r * Stop bit: 1");
	} else {
		uartSendString("\n\r * Stop bit: 2");
	}
	uartSendString("\n\r * Flow control:");
	switch (UartHandle.Init.HwFlowCtl) {
	case UART_HWCONTROL_NONE:
		uartSendString("NONE ");
		break;
	case UART_HWCONTROL_RTS:
		uartSendString("RTS ");
		break;
	case UART_HWCONTROL_CTS:
		uartSendString("CTS ");
		break;
	case UART_HWCONTROL_RTS_CTS:
		uartSendString("RTS/CTS ");
		break;
	default:
		break;
	}

	uartSendString("\n\r * Parity:");
	switch (UartHandle.Init.Parity) {
	case UART_PARITY_NONE:
		uartSendString("NONE ");
		break;
	case UART_PARITY_EVEN:
		uartSendString("EVEN ");
		break;
	case UART_PARITY_ODD:
		uartSendString("ODD ");
		break;
	default:
		break;
	}
	uartSendString("\n\r **************************** \n\r");

}



PUTCHAR_PROTOTYPE {
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART3 and Loop until the end of transmission */
	HAL_UART_Transmit(&UartHandle, (uint8_t*) &ch, 1, 0xFFFF);

	return ch;
}

