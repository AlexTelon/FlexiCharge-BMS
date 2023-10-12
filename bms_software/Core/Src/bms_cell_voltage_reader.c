/*
 * bms_cell_voltage_reader.c
 *
 */

#include "bms_cell_voltage_reader.h"

// Takes in a value and converts it to a voltage level. Represents a float as a three or four digit integer.
// This function also scales up the voltage, so it represents the value read at the battery, not the 3.3V the ADC can handle.
uint16_t convert_rawADC_to_voltage(uint16_t raw_adc)
{
	if(raw_adc > 0)
		return (raw_adc / (ADC_RESOLUTION / SYSTEM_VOLTAGE)) * VOLTAGE_SCALAR;
	return 0;
}
