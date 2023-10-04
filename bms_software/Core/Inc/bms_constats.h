/*
 * bms_constats.h
 *
 * This header file is used for storing common constants
 */

#ifndef INC_BMS_CONSTATS_H_
#define INC_BMS_CONSTATS_H_

#define ADC_RESOLUTION 4095 // The MCU has a 12 bit adc.
#define SYSTEM_VOLTAGE 3.3 // The MCU runs on 3.3 volt.

/* Since the voltage will be represented as a 16 bit unsigned integer, we need
 * to scale it up to get more accuracy. This scalar also up-scales the voltage
 * read.With this value, the voltage output will represent the voltage at the
 * battery.
*/
#define VOLTAGE_SCALAR 1272

// The resistance in the charging circuit for reading the current to the batteries
#define CHARGING_RESISTANCE 5.4
#define MILLI 1000

//Charging levels
#define PRE_CHARGE_LEVEL 2.8
#define CONSTANT_VOLTAGE 4.1
#define FULL_CHARGE_CURRENT 75 //The current in mA going to the cell at full charge

#endif /* INC_BMS_CONSTATS_H_ */
