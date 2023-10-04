/*
 * bms_uart_communication.h
 *
 */

#ifndef INC_BMS_UART_COMMUNICATION_H_
#define INC_BMS_UART_COMMUNICATION_H_

#include "stm32f4xx_hal.h"


// Function prototypes
void uart_send_string(const char* command, UART_HandleTypeDef uart);



#endif /* INC_BMS_UART_COMMUNICATION_H_ */
