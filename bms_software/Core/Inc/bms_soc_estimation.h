/*
 * bms_soc_estimation.h
 *
 * Estimate SoC using the current voltage level using the formula found in an answer here:
 * https://electronics.stackexchange.com/questions/401414/calculate-battery-state-of-charge-percentage
 */

#include "main.h"

#ifndef INC_BMS_SOC_ESTIMATION_H_
#define INC_BMS_SOC_ESTIMATION_H_

// Two constants to be used in the calculation
#define VOLTAGE_HIGH 4000 // Dummy
#define VOLTAGE_LOW 3000 // Dummy

// Function prototypes
uint8_t soc_estimation(uint16_t current_voltage_level);

#endif /* INC_BMS_SOC_ESTIMATION_H_ */
