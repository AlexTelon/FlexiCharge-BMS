/*
 * bms_uart_communication.h
 *
 */

#ifndef INC_BMS_UART_COMMUNICATION_H_
#define INC_BMS_UART_COMMUNICATION_H_

#include "main.h"

// All the commands that will be sent to and from the BMS.
const char* ok = "ok";
const char* voltage = "voltage";
const char* begin = "begin";
const char* end = "end";
const char* charge = "charge";
const char* temp = "temp";
const char* connect = "connect";
const char* beep = "beep";

// Function prototypes
void uart_send_string(const char* command, UART_HandleTypeDef uart);



#endif /* INC_BMS_UART_COMMUNICATION_H_ */
