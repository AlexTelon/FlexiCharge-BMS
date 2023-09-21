/*
 * bms_cell_voltage_reader.c
 *
 */

#include "bms_cell_voltage_reader.h"

// Reads the analog value of cell, returns an unsigned 16 bit int, between 0 - 4095.
uint16_t read_battery_raw(enum battery_pack cell, ADC_HandleTypeDef adc)
{
	switch(cell)
	{
	case Cell_1: // Read first cell
		  HAL_ADC_Start(&adc);
		  if(HAL_ADC_PollForConversion(&adc, HAL_MAX_DELAY) == HAL_OK)
		  {
			  return HAL_ADC_GetValue(&adc);
		  }
		  HAL_ADC_Stop(&adc);
		break;
	case Cell_2: // Read second cell
		break;
	}
	return 0;
}

// Takes in a value and converts it to a voltage level. Represents a float as a three or four digit integer.
// This function also scales up the voltage, so it represents the value read at the battery, not the 3.3V the ADC can handle.
uint16_t convert_rawADC_to_voltage(uint16_t raw_adc)
{
	if(raw_adc > 0)
		return (raw_adc / (ADC_RESOLUTION / SYSTEM_VOLTAGE)) * VOLTAGE_SCALAR;
	return 0;
}
