/*
 * main.c
 *
 *  Created on: Feb 19, 2016
 *      Author: steve-kim
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"

#include "timer.h"
#include "motor_control.h"

static void initializeGPIO() {
    //
	// For this example PWM0 is used with PortB Pins 6 and 7.  The actual port
	// and pins used may be different on your part, consult the data sheet for
	// more information.  GPIO port B needs to be enabled so these pins can be
	// used.
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	// M0PWM4 and M0PWM5 are mapped to GPIO Port E
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
}

int main(void) {
	// Set up system clock
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
            SYSCTL_XTAL_16MHZ);

	initializeGPIO();
	initializePWM();
	initializeTimer();

	configurePWM();

	// Enable processor wide interrupts
	IntMasterEnable();

    //
    // Enable the PWM0 all PWM signals
    //
    PWMOutputState(PWM0_BASE,
    		PWM_OUT_5_BIT | PWM_OUT_4_BIT | PWM_OUT_3_BIT | PWM_OUT_2_BIT | PWM_OUT_1_BIT | PWM_OUT_0_BIT,
			true);

    //
    // Enables the counter for a PWM generator block.
    //
    PWMGenEnable(PWM0_BASE, PWM_GEN_0);
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
    PWMGenEnable(PWM0_BASE, PWM_GEN_2);

    enableTimer();

    while(true) {}

}
