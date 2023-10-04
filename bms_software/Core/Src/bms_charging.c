/*
 * bms_charging.c
 *
 *  Created on: Oct 3, 2023
 *      Author: viram
 */

#include "bms_charging.h"

void open_realys(){
	//turns off/opens all relays
	HAL_GPIO_WritePin(GPIOB, cell1_relay_Pin, GPIO_PIN_SET);//Active low
	HAL_GPIO_WritePin(GPIOB, cell2_relay_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, pc_relay_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, cc_relay_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, cv_relay_Pin, GPIO_PIN_SET);
}

void get_cells_current(struct battery_cell *cell, uint16_t *adc_current_arr){

	for(int8_t i = 0; i < sizeof(cell); i++){
		cell[i].current = adc_current_arr[i];
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

		if(cell[i].current >= FULL_CHARGE_CURRENT)
			cell[i].state = no_charge;

		else if(cell[i].voltage < PRE_CHARGE_LEVEL)
			cell[i].state = pre_charge;

		else if(cell[i].voltage >= PRE_CHARGE_LEVEL && cell[i].voltage < CONSTANT_VOLTAGE)
			cell[i].state = constant_current;

		else if (cell[i].voltage >= CONSTANT_VOLTAGE)
			cell[i].state = constant_voltage;

		else cell[i].state = no_charge; //Something wrong
	}
}

