/*
 * bms_charging.h
 *
 *  Created on: Oct 3, 2023
 *      Author: viram
 */

#ifndef INC_BMS_CHARGING_H_
#define INC_BMS_CHARGING_H_

#include "bms_cell_voltage_reader.h"
#include "bms_current_reader.h"

enum charging_state{
	pre_charge,
	constant_current,
	constant_volatage,
	no_charge
};

struct battery_cell {
	uint16_t voltage;
	uint16_t current;
	enum charging_state state;
};

void open_realys();

void get_cells_current(struct battery_cell *cell, uint16_t *adc_current_arr);

void get_cells_voltage(struct battery_cell *cell, uint16_t *adc_voltage_arr);

void get_cells_state(struct battery_cell *cell);

void choose_charging_cells(struct battery_cell *cell);

void switch_charging_state(enum charging_state state);

void battery_pre_charge(struct battery_cell *cell);

void battery_constant_current(struct battery_cell *cell);

void battery_constant_voltage(struct battery_cell *cell);



#endif /* INC_BMS_CHARGING_H_ */
