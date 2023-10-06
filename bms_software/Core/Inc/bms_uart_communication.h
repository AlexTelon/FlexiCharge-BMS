/*
 * bms_uart_communication.h
 *
 */

#ifndef INC_BMS_UART_COMMUNICATION_H_
#define INC_BMS_UART_COMMUNICATION_H_

#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "string.h"
#include "bms_constats.h"

// Enum for the different states of connection.
enum CONNECTION_STATE
{
	HANDSHAKE, // Await connection and negotiate voltage level
	BEGIN, // Charger sends power
	UPDATE_DATA, // BMS updates Charger with data as it changes
	END // Battery is fully charged
};

// Function prototypes
void uart_send_string(const char* command, UART_HandleTypeDef uart, uint8_t length);

void uart_send_number(int n, UART_HandleTypeDef uart);

uint8_t uart_establish_connection(UART_HandleTypeDef uart);

uint8_t uart_receive_ok(UART_HandleTypeDef uart);

uint8_t uart_handshake(uint8_t voltage, UART_HandleTypeDef uart);

uint8_t uart_init_power(UART_HandleTypeDef uart);

uint8_t uart_terminate_power(UART_HandleTypeDef uart);

uint8_t uart_data_temp(UART_HandleTypeDef uart, uint8_t data);

uint8_t uart_data_charge(UART_HandleTypeDef uart, uint8_t data);

uint8_t uart_heartbeat(UART_HandleTypeDef uart);


#endif /* INC_BMS_UART_COMMUNICATION_H_ */
