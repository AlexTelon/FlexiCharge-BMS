/*
 * bms_current_reader.c
 *
 */

#include "bms_current_reader.h"


uint16_t adc_resistor_drop(uint16_t adc_pre, uint16_t adc_post){
	return adc_pre - adc_post;
}

float convert_adc_to_mAmp(uint16_t adc_diff){
	float voltage = (SYSTEM_VOLTAGE*adc_diff)/ADC_RESOLUTION;
	float mAmp = (voltage * CHARGING_RESISTANCE) * MILLI;
	return mAmp;
}


