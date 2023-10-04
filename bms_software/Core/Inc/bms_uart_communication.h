/*
 * bms_uart_communication.h
 *
 */

#ifndef INC_BMS_UART_COMMUNICATION_H_
#define INC_BMS_UART_COMMUNICATION_H_

#include "stm32f4xx_hal.h"


// Function prototypes
void uart_send_string(const uint8_t* command, UART_HandleTypeDef uart, uint8_t length);

uint8_t uart_establish_connection(UART_HandleTypeDef uart);

uint8_t uart_receive_ok(UART_HandleTypeDef uart);



#endif /* INC_BMS_UART_COMMUNICATION_H_ */
