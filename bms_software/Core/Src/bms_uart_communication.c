/*
 * bms_uart_communication.c
 *
 */

#include "bms_uart_communication.h"

	// All the commands that will be sent to and from the BMS.
const uint8_t* ok = "ok";
const uint8_t* voltage = "voltage:";
const uint8_t* begin = "begin";
const uint8_t* end = "end";
const uint8_t* charge = "charge";
const uint8_t* temp = "temp";
const uint8_t* connect = "connect";
const uint8_t* beep = "beep";

// Function to send a string over UART.
void uart_send_string(const uint8_t* command, UART_HandleTypeDef uart, uint8_t length)
{
	for(int i = 0; i <= length; i++)
	{
		HAL_UART_Transmit(&uart, &command[i], 1, 200);
	}
}

void uart_send_number(uint8_t n, UART_HandleTypeDef uart)
{
	  const uint8_t buff_size = 4;
	  char out[buff_size];
	  int length = snprintf(out, buff_size, "%hu", n);

	  uart_send_string(out, uart, length);
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

// Function to establish connection. Sends the "connect" command and returns the response.
uint8_t uart_establish_connection(UART_HandleTypeDef uart)
{
	uart_send_string(connect, uart, sizeof(connect));

	return uart_receive_ok(uart);
}

uint8_t uart_handshake(uint8_t voltage, UART_HandleTypeDef uart)
{
	uint8_t result = 0;
	result = uart_establish_connection(uart);
	if(result == 1)
		uart_send_number(voltage, uart);
	return result;
}

uint8_t uart_init_power(UART_HandleTypeDef uart)
{
	uart_send_string(begin, uart, sizeof(begin));

	return uart_receive_ok(uart);
}

uint8_t uart_terminate_power(UART_HandleTypeDef uart)
{
	uart_send_string(end, uart, sizeof(end));

	return uart_receive_ok(uart);
}

uint8_t uart_data_temp(UART_HandleTypeDef uart, uint8_t data)
{
	uart_send_string(temp, uart, sizeof(temp));
	uart_send_number(data, uart);

	return uart_receive_ok(uart);
}

uint8_t uart_data_charge(UART_HandleTypeDef uart, uint8_t data)
{
	uart_send_string(charge, uart, sizeof(charge));
	uart_send_number(data, uart);

	return uart_receive_ok(uart);
}

uint8_t uart_heartbeat(UART_HandleTypeDef uart)
{
	uart_send_string(beep, uart, sizeof(beep));

	return uart_receive_ok(uart);
}
