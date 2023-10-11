/*
 * bms_soc_estimation.c
 *
 */
#include "bms_soc_estimation.h"

// Will return a number between 0 and 100, representing the current state of charge.
uint8_t soc_estimation(uint16_t current_voltage_level)
{
	uint8_t state_of_charge = ((current_voltage_level - VOLTAGE_LOW) / (VOLTAGE_HIGH - VOLTAGE_LOW) * 100);
	if(state_of_charge > 100) // State of Charge should never be greater than 100%
		state_of_charge = 100;
	return state_of_charge;
}

