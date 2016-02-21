/*
 * motor_control.h
 *
 *  Created on: Feb 20, 2016
 *      Author: steve-kim
 */

#ifndef INC_MOTOR_CONTROL_H_
#define INC_MOTOR_CONTROL_H_

static void state_phase_AlBh();
static void state_phase_BhCl();
static void state_phase_AhCl();
static void state_phase_AhBl();
static void state_phase_BlCh();
static void state_phase_AlCh();

void initializePWM();
void configurePWM();
void disablePWM();
void enablePWM();
void switchState();

#endif /* INC_MOTOR_CONTROL_H_ */
