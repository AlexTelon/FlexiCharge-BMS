/*
 * bms_current_reader.c
 *
 */

#include "bms_current_reader.h"


uint16_t adc_resistor_drop(uint16_t adc_pre, uint16_t adc_post){
	if(adc_pre > adc_post)
		return adc_pre - adc_post;
	else return 0;
}

uint16_t convert_adc_to_mAmp(uint16_t adc_diff){
	uint16_t voltage = (SYSTEM_VOLTAGE*adc_diff)/ADC_RESOLUTION;
	uint16_t mAmp = (voltage / CHARGING_RESISTANCE) * MILLI;
	return mAmp;
}


