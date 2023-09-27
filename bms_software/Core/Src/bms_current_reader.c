/*
 * bms_current_reader.c
 *
 */

#include "bms_current_reader.h"

/*
 * Converts the ADC to m amp
 */
float convert_adc_to_mAmp(uint16_t adc_value){
	float voltage = (SYSTEM_VOLTAGE*adc_value)/ADC_RESOLUTION;
	float mAmp = (voltage * CHARGING_RESISTANCE) * MILLI;
	return mAmp;
}


