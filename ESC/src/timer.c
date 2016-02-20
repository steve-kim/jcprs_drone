/*
 * timer.c
 *
 *  Created on: Feb 19, 2016
 *      Author: steve-kim
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

static unsigned char interrupt_counter = 0;

void Timer0IntHandler(void) {
	TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);

	interrupt_counter++;;

	if (interrupt_counter == 255) {
		interrupt_counter = 0;
	}
}

void initializeTimer() {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	// Configure the timer for 16-bit periodic interrupt
	TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);

	// Interrupt every 500ms
	TimerLoadSet(TIMER0_BASE, TIMER_B, SysCtlClockGet() / 2);

	// Enable timer interrupts
	TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
	IntEnable(INT_TIMER0B);
}

void enableTimer() {
	TimerEnable(TIMER0_BASE, TIMER_B);
}
