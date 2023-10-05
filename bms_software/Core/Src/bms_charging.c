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
	HAL_GPIO_WritePin(GPIOA, pc_relay_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, cc_relay_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, cv_relay_Pin, GPIO_PIN_SET);
}

//check charging current to individual cell, needs to know which cell is currently
//being charged
void get_cells_charging_current(struct battery_cell *cell, uint16_t read_current){

	read_current /= nbr_charging_cells;

	for(int8_t i = 0; i < sizeof(cell); i++){
		if(cell[i].is_charging) //should only read charging current if the cell i charging
			cell[i].charging_current = read_current;
		else cell[i].charging_current = 0;
	}
}

void get_cells_voltage(struct battery_cell *cell, uint16_t *adc_voltage_arr){

	//turn off relay
	HAL_GPIO_WritePin(GPIOB, cell1_relay_Pin, GPIO_PIN_SET);//Active low
	HAL_GPIO_WritePin(GPIOB, cell2_relay_Pin, GPIO_PIN_SET);

	for(int8_t i = 0; i < sizeof(cell); i++){
		cell[i].voltage = adc_voltage_arr[i];
	}

	//turn on relay
	HAL_GPIO_WritePin(GPIOB, cell1_relay_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, cell2_relay_Pin, GPIO_PIN_RESET);
}

void get_cells_state(struct battery_cell *cell){

	for(int8_t i = 0; i < sizeof(cell); i++){

		if(cell[i].voltage >= CONSTANT_VOLTAGE && cell[i].charging_current <= FULL_CHARGE_CURRENT) //This will result in faulty behavior for now
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

void choose_charging_cells(struct battery_cell *cell){
	uint8_t charging_cell = 99;
	for(uint8_t i = 0; i < sizeof(cell) - 1; i++){
		if(cell[i].state < cell[i + 1].state){
			charging_cell = i;
		}
		else if (cell[i].state > cell[i + 1].state){
			charging_cell = i+1;
		}
		else if (cell[i].voltage < cell[i+1].voltage){ //the cells are in the same state
			charging_cell = i;
		}
		else if (cell[i].voltage > cell[i+1].voltage){
			charging_cell = i+1;
		}
		else charging_cell = 99;
	}
}

