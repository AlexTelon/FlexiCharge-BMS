/*
 * bms_charging.c
 *
 *  Created on: Oct 3, 2023
 *      Author: viram
 */

#include "bms_charging.h"

void battery_cell_init(struct battery_cell *cells){

	for(uint8_t i = 0; i < sizeof(cells); i++){
		struct battery_cell cell;
		cell.charging_current = 0;
		cell.voltage = 0;
		cell.is_charging = true;
		cell.relay_pin = cell1_relay_Pin;
		cell.state = no_charge;
		cell.old_state = no_charge;

		cells[i] = cell;
	}
}

//turns off/opens all relays
void open_relays(){

	HAL_GPIO_WritePin(GPIOB, cell1_relay_Pin, GPIO_PIN_SET);//Active low
	HAL_GPIO_WritePin(GPIOB, cell2_relay_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, pc_relay_Pin, GPIO_PIN_SET); //pre charge relay
	HAL_GPIO_WritePin(GPIOB, cc_relay_Pin, GPIO_PIN_SET); //constant current
	HAL_GPIO_WritePin(GPIOB, cv_relay_Pin, GPIO_PIN_SET); //constant voltage
}

//check charging current to individual cell, needs to know which cell is currently
//being charged, currently only one cell should be checked
void get_cells_charging_current(struct battery_cell *cell, uint32_t *adc){

	for(int8_t i = 0; i < 1; i++){
		if(cell[i].is_charging){
			HAL_GPIO_WritePin(GPIOB, cell[i].relay_pin, GPIO_PIN_RESET);
			HAL_Delay(3);

			uint16_t voltage_drop = adc_resistor_drop(adc[2], adc[3]); //Ugly
			cell[i].charging_current = convert_adc_to_mAmp(voltage_drop) * CURRENT_MULTIPLIER;
		}
		else cell[i].charging_current = 0;
	}
}

void get_cells_voltage(struct battery_cell *cell, uint32_t *adc){
	for(int8_t i = 0; i < 1; i++){
		cell[i].voltage = convert_rawADC_to_voltage(adc[0]);//Ugly
	}
}

void get_cells_state(struct battery_cell *cell){

	for(int8_t i = 0; i < sizeof(cell); i++){

		if(cell[i].voltage >= CONSTANT_VOLTAGE && cell[i].charging_current <= FULL_CHARGE_CURRENT){
			if(cell[i].state == constant_voltage)
				cell[i].state = fully_charged;

			else if(cell[i].state == no_charge){
				//Assign safe charging current to unlock measurement
				cell[i].charging_current = ALMOST_FULL_CHARGE_CURRENT;
			}
		}

		else if(cell[i].voltage < PRE_CHARGE_VOLTAGE)
			cell[i].state = pre_charge;

		else if(cell[i].voltage >= PRE_CHARGE_VOLTAGE && cell[i].voltage < CONSTANT_VOLTAGE)
			cell[i].state = constant_current;

		else if (cell[i].voltage >= CONSTANT_VOLTAGE)
			cell[i].state = constant_voltage;

		else cell[i].state = no_charge; //Something wrong
	}
}

void choose_charging_cells(struct battery_cell *cell);

void switch_charging_state(struct battery_cell *cell){

	for(uint8_t i = 0; i < sizeof(cell); i++){
		if(cell[i].state != cell[i].old_state && cell[i].is_charging){
			switch (cell[i].state)
			{
				case pre_charge:
					battery_pre_charge(cell[i]);
					cell[i].old_state = cell[i].state;
					break;

				case constant_current:
					battery_constant_current(cell[i]);
					cell[i].old_state = cell[i].state;
					break;

				case constant_voltage:
					battery_constant_voltage(cell[i]);
					cell[i].old_state = cell[i].state;
					break;

				case fully_charged:
					open_relays();
					cell[i].old_state = cell[i].state;
					break;

				case no_charge:
					open_relays();
					cell[i].old_state = cell[i].state;
					break;

				default:
					open_relays();
			}
		}
	}
}

void battery_pre_charge(struct battery_cell cell){
	open_relays();
	HAL_GPIO_WritePin(GPIOA, pc_relay_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, cell.relay_pin, GPIO_PIN_RESET);
}

void battery_constant_current(struct battery_cell cell){
	open_relays();
	HAL_GPIO_WritePin(GPIOB, cc_relay_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, cell.relay_pin, GPIO_PIN_RESET);
}

void battery_constant_voltage(struct battery_cell cell){
	open_relays();
	HAL_GPIO_WritePin(GPIOB, cv_relay_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, cell.relay_pin, GPIO_PIN_RESET);
}

void charge_loop(struct battery_cell *cells, uint32_t *adc){//Ugly to only use one array for both voltage and current
	get_cells_voltage(cells, adc);
	get_cells_charging_current(cells, adc);
	get_cells_state(cells);
	switch_charging_state(cells);
}

