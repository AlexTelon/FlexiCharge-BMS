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
#include "bms_constats.h"
#include <stdbool.h>
#include "main.h" // not sure if it should be used this way

enum charging_state{
	pre_charge,
	constant_current,
	constant_voltage,
	no_charge,
};

struct battery_cell {
	uint16_t voltage; //Cells voltage
	uint16_t charging_current; //Charging current in mA flowing to the cell
	uint16_t relay_pin;
	bool is_charging;
	enum charging_state state; //The cells charging state
};

void open_realys();

void battery_cell_init(struct battery_cell *cells);

void get_cells_charging_current(struct battery_cell *cell, uint16_t *pre_adc, uint16_t *post_adc);

void get_cells_voltage(struct battery_cell *cell, uint16_t *adc_voltage_arr);

void get_cells_state(struct battery_cell *cell);

void choose_charging_cells(struct battery_cell *cell);

void switch_charging_state(struct battery_cell *cell);

void battery_pre_charge(struct battery_cell cell);

void battery_constant_current(struct battery_cell cell);

void battery_constant_voltage(struct battery_cell cell);

void monitor_cell_charging();

void charge_loop(struct battery_cell *cells, uint16_t *adc_voltage_arr, uint16_t *adc_current);



#endif /* INC_BMS_CHARGING_H_ */
