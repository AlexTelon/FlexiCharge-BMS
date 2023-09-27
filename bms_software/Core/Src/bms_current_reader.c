/*
 * bms_current_reader.c
 *
 */

#include "bms_current_reader.h"

float convert_adc_to_volt(uint16_t adc_value){
	return (SYSTEM_VOLTAGE*adc_value)/ADC_RESOLUTION;
}


