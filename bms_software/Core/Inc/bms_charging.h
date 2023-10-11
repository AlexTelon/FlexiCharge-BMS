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
	fully_charged,
	no_charge,
};

struct battery_cell {
	uint16_t voltage; //Cells voltage
	uint16_t charging_current; //Charging current in mA flowing to the cell
	uint16_t relay_pin;
	bool is_charging;
	enum charging_state state; //The cells charging state
	enum charging_state old_state; //The cells charging state
};

//Open all relays, used for safe switching
void open_realys();

//Initiate cells and their values
void battery_cell_init(struct battery_cell *cells);

//Read the charging current to the cell/s
void get_cells_charging_current(struct battery_cell *cell, uint32_t *adc);

//Read each cells voltage
void get_cells_voltage(struct battery_cell *cell, uint32_t *adc);

//Get which charging state the cells are in
void get_cells_state(struct battery_cell *cell);

//Choose which cell to charge, or both
void choose_charging_cells(struct battery_cell *cell);

//Switch charging states (state machine!)
void switch_charging_state(struct battery_cell *cell);

//Function for pre charging a cell
void battery_pre_charge(struct battery_cell cell);

//Function for charging a cell with constant current
void battery_constant_current(struct battery_cell cell);

//Functiont for charging a cell with constant voltage
void battery_constant_voltage(struct battery_cell cell);

//Function for running the entire charging system
void charge_loop(struct battery_cell *cells, uint32_t *adc);



#endif /* INC_BMS_CHARGING_H_ */
