/*
 * bms_charging.c
 *
 *  Created on: Oct 3, 2023
 *      Author: viram
 */

#include "bms_charging.h"

void open_realys(){

}

void get_cells_current(struct battery_cell *cell, uint16_t *adc_current_arr){
	//turn off relay

	for(int8_t i = 0; i < sizeof(cell); i++){
		cell[i].current = adc_current_arr[i];
	}

	//turn on relay
}

void get_cells_voltage(struct battery_cell *cell, uint16_t *adc_voltage_arr){

	//turn off relay

	for(int8_t i = 0; i < sizeof(cell); i++){
		cell[i].voltage = adc_voltage_arr[i];
	}

	//turn on relay
}

