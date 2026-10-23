/*
 * AnalogClock.c
 *
 *  Created on: 2026. 10. 23.
 *      Author: kccistc
 */
#include "AnalogClock.h"

stepMotor_pin_t stepMotorSecPins[4] = { { GPIOA, GPIO_PIN_0 }, // orange
		{ GPIOA, GPIO_PIN_1 }, // yellow
		{ GPIOA, GPIO_PIN_4 }, // pink
		{ GPIOB, GPIO_PIN_0 }  // blue
};

stepMotor_pin_t stepMotorMinPins[4] = { { GPIOA, GPIO_PIN_0 }, // orange
		{ GPIOA, GPIO_PIN_1 }, // yellow
		{ GPIOA, GPIO_PIN_4 }, // pink
		{ GPIOB, GPIO_PIN_0 }  // blue
};

stepMotor_pin_t stepMotorHourPins[4] = { { GPIOA, GPIO_PIN_0 }, // orange
		{ GPIOA, GPIO_PIN_1 }, // yellow
		{ GPIOA, GPIO_PIN_4 }, // pink
		{ GPIOB, GPIO_PIN_0 }  // blue
};

stepMotor_t stepMotors[3] = { { stepMotorSecPins, 0 }, { stepMotorMinPins, 0 },
		{ stepMotorHourPins, 0 } };

volatile uint8_t isrFlag = 0;

void ClockNeedle_setFlag(void) {
	isrFlag = 1;

}

void ClockNeedle_clearFlag(void) {
	isrFlag = 0;

}

void ClockNeedle_ISR(void) {
	ClockNeedle_setFlag();
}

void ClockNeedle_task(void) {
	if (!isrFlag) {
		return;
	}
	ClockNeedle_clearFlag();
	StepMotor_stepPhase(&stepMotors[SEC], STEPMOTOR_DIR_CW);
}
