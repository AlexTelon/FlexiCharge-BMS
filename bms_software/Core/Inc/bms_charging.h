/*
 * bms_charging.h
 *
 *  Created on: Oct 3, 2023
 *      Author: viram
 */

#ifndef INC_BMS_CHARGING_H_
#define INC_BMS_CHARGING_H_

enum charging_state{
	pre_charge,
	constant_current_one_cell,
	constat_current_all_cells,
	constant_volatage,
	no_charge
};

struct battery_cell {
	uint16_t voltage;
	uint16_t current;
	charging_state state;
};

void open_realys();

void get_cells_charge(battery_cell *cell);

void get_cells_state(battery_cell *cell);

void choose_charging_cells(battery_cell *cell);

void switch_charging_state(charging_state state);

void pre_charge(battery_cell *cell);

void constant_current(battery_cell *cell);

void constant_voltage(battery_cell *cell);



#endif /* INC_BMS_CHARGING_H_ */
