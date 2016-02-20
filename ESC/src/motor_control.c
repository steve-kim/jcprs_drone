/*
 * motor_control.c
 *
 *  Created on: Feb 20, 2016
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

void initializePWM() {
    // Set the PWM clock to the system clock.
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    //
    // The PWM peripheral must be enabled for use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

    // Controlled by PWM Generator 0
    GPIOPinConfigure(GPIO_PB6_M0PWM0);
    GPIOPinConfigure(GPIO_PB7_M0PWM1);
    // Controlled by PWM Generator 1
    GPIOPinConfigure(GPIO_PB5_M0PWM3);
    GPIOPinConfigure(GPIO_PB4_M0PWM2);
    // Controlled by PWM Generator 2
    GPIOPinConfigure(GPIO_PE5_M0PWM5);
	GPIOPinConfigure(GPIO_PE4_M0PWM4);

    //
    // Configure the GPIO pad for PWM function on pins PB6 and PB7.  Consult
    // the data sheet to see which functions are allocated per pin.
    //
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_5);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
    GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_5);
    GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);
}

void configurePWM() {
    //
    // Configure the PWM0 to count up/down without synchronization.
    // Note: Enabling the dead-band generator automatically couples the 2
    // outputs from the PWM block so we don't use the PWM synchronization.
    //
    PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN |
                    PWM_GEN_MODE_NO_SYNC);

    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN |
                        PWM_GEN_MODE_NO_SYNC);

    PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN |
                            PWM_GEN_MODE_NO_SYNC);
    //
    // Set the PWM period to 250Hz.  To calculate the appropriate parameter
    // use the following equation: N = (1 / f) * SysClk.  Where N is the
    // function parameter, f is the desired frequency, and SysClk is the
    // system clock frequency.
    // In this case you get: (1 / 250Hz) * 16MHz = 64000 cycles.  Note that
    // the maximum period you can set is 2^16 - 1.
    // TODO: modify this calculation to use the clock frequency that you are
    // using.
    //
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 64000);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, 64000);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, 64000);

    //
    // Set PWM0 PD0 to a duty cycle of 25%.  You set the duty cycle as a
    // function of the period.  Since the period was set above, you can use the
    // PWMGenPeriodGet() function.  For this example the PWM will be high for
    // 25% of the time or 16000 clock cycles (64000 / 4).
    //
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,
                     PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 4);

    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1,
                         PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 2);

    // Outputs on PB5 and PB4
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2,
                         PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1) / 4);

    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3,
                         PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1) / 2);

    // Outputs on PE5 and PE4
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4,
                             PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1) / 4);

	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5,
						 PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1) / 2);
}


