/*
 * bms_uart_communication.c
 *
 */

#include "bms_uart_communication.h"

// Function to send a string over UART.
void uart_send_string(const uint8_t* command, UART_HandleTypeDef uart, uint8_t length)
{
	for(int i = 0; i <= length; i++)
	{
		HAL_UART_Transmit(&uart, &command[i], 1, 200);
	}
}
