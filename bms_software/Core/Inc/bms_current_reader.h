/*
 * bms_current_reader.h
 *
 */

#ifndef INC_BMS_CURRENT_READER_H_
#define INC_BMS_CURRENT_READER_H_

#include "stm32f4xx_hal.h"
#include "bms_constats.h"

float convert_adc_to_volt(uint16_t adc_value);

#endif /* INC_BMS_CURRENT_READER_H_ */
