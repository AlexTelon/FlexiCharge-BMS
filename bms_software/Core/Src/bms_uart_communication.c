/*
 * bms_uart_communication.c
 *
 */

#include "bms_uart_communication.h"

// All the commands that will be sent to and from the BMS.
const char* ok = "ok";
const char* voltage = "voltage:"; // No newline character since the uart_send_number function adds one after the number.
const char* begin = "begin\n";
const char* end = "end\n";
const char* charge = "charge:";
const char* temp = "temp:";
const char* connect = "connect\n";
const char* beep = "beep\n";

// Function to send a string over UART.
void uart_send_string(const char* command, UART_HandleTypeDef uart, uint8_t length)
{
	for(int i = 0; i <= length; i++)
	{
		HAL_UART_Transmit(&uart, &command[i], 1, 200);
	}
}

// A function to send numbers over uart. Can handle negative numbers.
// Apends a newline character to each number for easier extraction.
void uart_send_number(int n, UART_HandleTypeDef uart)
{
	  const uint8_t buff_size = 5;
	  char out[buff_size];
	  uint8_t length = snprintf(out, buff_size, "%i\n", n);

	  uart_send_string(out, uart, length); // Apend a \n after a number has been sent.
}

// This function checks for a response fromt the charger, and returns a 1 if the expected "ok" command was received.
// Otherwise it returns a 0. A 0 should be seen as a failed response.
uint8_t uart_receive_ok(UART_HandleTypeDef uart)
{
	uint8_t response[2];

	if(HAL_UART_Receive(&uart, response, 2, RESPONSE_DELAY) == HAL_OK)
		if((char)response[0] == 'o' && (char)response[1] == 'k')
			return 1;
	return 0;
}

// Function to establish connection. Sends the "connect" command and returns the response.
uint8_t uart_establish_connection(UART_HandleTypeDef uart)
{
	uart_send_string(connect, uart, strlen(connect));

	return uart_receive_ok(uart);
}

// Function to establish connection and negotiate voltage levels.
uint8_t uart_handshake(uint8_t n, UART_HandleTypeDef uart) // Rewrite so it can handle taking in negative numbers.
{
	uint8_t result = 0;
	result = uart_establish_connection(uart);
	if(result == 1)
	{
		uart_send_string(voltage, uart, strlen(voltage));
		uart_send_number(n, uart);
	}
	return result;
}

// Initialize the power delivery.
uint8_t uart_init_power(UART_HandleTypeDef uart)
{
	uart_send_string(begin, uart, strlen(begin));

	return uart_receive_ok(uart);
}

// Terminate power delivery.
uint8_t uart_terminate_power(UART_HandleTypeDef uart)
{
	uart_send_string(end, uart, strlen(end));

	return uart_receive_ok(uart);
}

// Send updates about temperature.
uint8_t uart_data_temp(UART_HandleTypeDef uart, uint8_t data)
{
	uart_send_string(temp, uart, strlen(temp));
	uart_send_number(data, uart);

	return uart_receive_ok(uart);
}

// Send updates about state of charge.
uint8_t uart_data_charge(UART_HandleTypeDef uart, uint8_t data)
{
	uart_send_string(charge, uart, strlen(charge));
	uart_send_number(data, uart);

	return uart_receive_ok(uart);
}

// Ensure the charger is connected.
uint8_t uart_heartbeat(UART_HandleTypeDef uart)
{
	uart_send_string(beep, uart, strlen(beep));

	return uart_receive_ok(uart);
}
