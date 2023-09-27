/*
 * bms_current_reader.h
 *
 */

#ifndef INC_BMS_CURRENT_READER_H_
#define INC_BMS_CURRENT_READER_H_

#include "stm32f4xx_hal.h"
#include "bms_constats.h"

uint16_t adc_resistor_drop(uint16_t adc_pre, uint16_t adc_post);

//Converts the ADC to m amp
float convert_adc_to_volt(uint16_t adc_diff);

#endif /* INC_BMS_CURRENT_READER_H_ */
