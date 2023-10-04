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

uint8_t charging_cell = 0;

struct battery_cell {
	uint16_t voltage;
	uint16_t current;
	charging_state state;
};

void get_cells_charge(battery_cell cell_1, battery_cell cell_2);

void get_cells_state(battery_cell cell_1, battery_cell cell_2);

void choose_charging_cells(battery_cell cell_1, battery_cell cell_2);

void switch_charging_state();

void charge_individual_cell(uint8_t cell_nbr);

void charge_both_cells();

void charge();



#endif /* INC_BMS_CHARGING_H_ */
