

#ifndef INC_BMS_CELL_VOLTAGE_READER_H_
#define INC_BMS_CELL_VOLTAGE_READER_H_

#include "stm32f4xx_hal.h"
#include "bms_constats.h"

enum battery_pack // An enum to allow users to specify which cell to be read.
{
	Cell_1,
	Cell_2
};

uint16_t read_battery_raw(enum battery_pack, ADC_HandleTypeDef adc);
uint16_t convert_rawADC_to_voltage(uint16_t);

#endif /* INC_BMS_CELL_VOLTAGE_READER_H_ */
