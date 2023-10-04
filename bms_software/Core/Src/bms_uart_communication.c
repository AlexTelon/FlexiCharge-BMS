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

// This function checks for a response fromt the charger, and returns a 1 if the expected "ok" command was received.
// Otherwise it returns a 0. A 0 should be seen as a failed response.
uint8_t uart_receive_ok(UART_HandleTypeDef uart)
{
	uint8_t response[2];

	if(HAL_UART_Receive(&uart, response, 2, 300) == HAL_OK)
		if((char)response[0] == 'o' && (char)response[1] == 'k')
			return 1;
	return 0;
}

// Function to establish connection. Sends the "connect" command and reads the response.
uint8_t uart_establish_connection(UART_HandleTypeDef uart)
{
	uart_send_string("connect", uart, 7);

	return uart_receive_ok(uart);
}
