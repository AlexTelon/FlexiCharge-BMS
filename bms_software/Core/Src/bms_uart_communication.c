/*
 * bms_uart_communication.c
 *
 */

#include "bms_uart_communication.h"

// Function to send a string over UART.
void uart_send_string(const char* command, UART_HandleTypeDef uart)
{
	for(int i = 0; command[i] != 0; i++)
	{
		HAL_UART_Transmit(&uart, command[i], 1, 200);
	}
}
