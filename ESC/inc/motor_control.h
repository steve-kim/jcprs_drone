/*
 * motor_control.h
 *
 *  Created on: Feb 20, 2016
 *      Author: steve-kim
 */

#ifndef INC_MOTOR_CONTROL_H_
#define INC_MOTOR_CONTROL_H_

typedef void state_fn();

state_fn state_phase_AlBh;
state_fn state_phase_BhCl;
state_fn state_phase_AhCl;
state_fn state_phase_AhBl;
state_fn state_phase_BlCh;
state_fn state_phase_AlCh;

void initializePWM();
void configurePWM();
void enablePWM();

#endif /* INC_MOTOR_CONTROL_H_ */
