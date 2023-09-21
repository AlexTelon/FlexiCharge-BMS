

#ifndef INC_BMS_CELL_VOLTAGE_READER_H_
#define INC_BMS_CELL_VOLTAGE_READER_H_

#include "stm32f4xx_hal.h"

#define ADC_RESOLUTION 4095 // The MCU has a 12 bit adc.
#define SYSTEM_VOLTAGE 3.3 // The MCU runs on 3.3 volt.
#define VOLTAGE_SCALAR 1272 // Since the voltage will be represented as a 16 bit unsigned integer, we need to scale it up to get more accuracy. This scalar also up-scales the voltage read. With this value, the voltage output will represent the voltage at the battery.
#define VOLTAGE_READING_UPDATE_DELAY 300 // A delay, in miliseconds, between voltage readings.


enum battery_pack // An enum to allow users to specify which cell to be read.
{
	Cell_1,
	Cell_2
};

uint16_t read_battery_raw(enum battery_pack, ADC_HandleTypeDef adc);
uint16_t convert_rawADC_to_voltage(uint16_t);

#endif /* INC_BMS_CELL_VOLTAGE_READER_H_ */
