/*
 * bms_charging.c
 *
 *  Created on: Oct 3, 2023
 *      Author: viram
 */

#include "bms_charging.h"

uint8_t nbr_charging_cells = 0;

void open_realys(){
	//turns off/opens all relays
	HAL_GPIO_WritePin(GPIOB, cell1_relay_Pin, GPIO_PIN_SET);//Active low
	HAL_GPIO_WritePin(GPIOB, cell2_relay_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, pc_relay_Pin, GPIO_PIN_SET); //pre charge relay
	HAL_GPIO_WritePin(GPIOB, cc_relay_Pin, GPIO_PIN_SET); //constant current
	HAL_GPIO_WritePin(GPIOB, cv_relay_Pin, GPIO_PIN_SET); //constant voltage
}

//check charging current to individual cell, needs to know which cell is currently
//being charged
void get_cells_charging_current(struct battery_cell *cell, uint16_t read_current){

	read_current /= nbr_charging_cells;

	for(int8_t i = 0; i < sizeof(cell); i++){
		if(cell[i].is_charging){ //should only read charging current if the cell i charging
			HAL_GPIO_WritePin(GPIOB, cell[i].relay_pin, GPIO_PIN_RESET);//Active low
			cell[i].charging_current = read_current;
		}
		else cell[i].charging_current = 0;
	}
}

void get_cells_voltage(struct battery_cell *cell, uint16_t *adc_voltage_arr){
	for(int8_t i = 0; i < sizeof(cell); i++){
		HAL_GPIO_WritePin(GPIOB, cell[i].relay_pin, GPIO_PIN_SET);//Active low
		cell[i].voltage = adc_voltage_arr[i];
	}
}

void get_cells_state(struct battery_cell *cell){

	for(int8_t i = 0; i < sizeof(cell); i++){

		if(cell[i].voltage >= CONSTANT_VOLTAGE && cell[i].charging_current <= FULL_CHARGE_CURRENT)
			cell[i].state = no_charge;

		else if(cell[i].voltage < PRE_CHARGE_VOLTAGE)
			cell[i].state = pre_charge;

		else if(cell[i].voltage >= PRE_CHARGE_VOLTAGE && cell[i].voltage < CONSTANT_VOLTAGE)
			cell[i].state = constant_current;

		else if (cell[i].voltage >= CONSTANT_VOLTAGE)
			cell[i].state = constant_voltage;

		else cell[i].state = no_charge; //Something wrong
	}
}

void choose_charging_cells(struct battery_cell *cell){//Not finished
	uint8_t charging_cell = 99;
	for(uint8_t i = 0; i < sizeof(cell) - 1; i++){
		if(cell[i].state < cell[i + 1].state){
			charging_cell = i;
		}
		else if (cell[i].state > cell[i + 1].state){
			charging_cell = i+1;
		}
		//else the cells are in the same state

		else charging_cell = 99;
	}
}

void switch_charging_state(struct battery_cell *cell){

	for(uint8_t i = 0; i < sizeof(cell); i++){
		switch (cell[i].state)
		{
			case pre_charge:
				battery_pre_charge(cell[i]);
				break;

			case constant_current:
				battery_constant_current(cell[i]);
				break;

			case constant_voltage:
				battery_constant_voltage(cell[i]);
				break;

			case no_charge:
				open_relays();
				break;

			default:
				open_relays();
		}
	}
}

void battery_pre_charge(struct battery_cell cell){
	open_realys(); //For safe switching
	HAL_GPIO_WritePin(GPIOA, pc_relay_Pin, GPIO_PIN_RESET);//Close pre charge relay
	HAL_GPIO_WritePin(GPIOB, cell.relay_pin, GPIO_PIN_RESET);//Close relay for cell
}

void battery_constant_current(struct battery_cell cell){
	open_realys();
	HAL_GPIO_WritePin(GPIOB, cc_relay_Pin, GPIO_PIN_RESET);//Close cc charge relay
	HAL_GPIO_WritePin(GPIOB, cell.relay_pin, GPIO_PIN_RESET);//Close relay for cell
}

void battery_constant_voltage(struct battery_cell cell){
	open_realys();
	HAL_GPIO_WritePin(GPIOB, cv_relay_Pin, GPIO_PIN_RESET);//Close cv charge relay
	HAL_GPIO_WritePin(GPIOB, cell.relay_pin, GPIO_PIN_RESET);//Close relay for cell
}

