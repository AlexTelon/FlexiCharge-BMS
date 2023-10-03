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
	constant_current,
	constant_volatage,
	no_charge
};

void switch_charging_state();

void get_cell_charge();

#endif /* INC_BMS_CHARGING_H_ */
