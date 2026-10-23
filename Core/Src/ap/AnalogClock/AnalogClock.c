/*
 * AnalogClock.c
 *
 *  Created on: 2026. 10. 23.
 *      Author: kccistc
 */
#include "AnalogClock.h"

#define MAX_STEP	4096

stepMotor_pin_t stepMotorSecPins[4] = { { GPIOA, GPIO_PIN_0 }, // orange
		{ GPIOA, GPIO_PIN_1 }, // yellow
		{ GPIOA, GPIO_PIN_4 }, // pink
		{ GPIOB, GPIO_PIN_0 }  // blue
};

stepMotor_pin_t stepMotorMinPins[4] = { { GPIOC, GPIO_PIN_10 }, // orange
		{ GPIOC, GPIO_PIN_11 }, // yellow
		{ GPIOC, GPIO_PIN_12 }, // pink
		{ GPIOD, GPIO_PIN_2 }  // blue
};

stepMotor_pin_t stepMotorHourPins[4] = { { GPIOC, GPIO_PIN_5 }, // orange
		{ GPIOC, GPIO_PIN_6 }, // yellow
		{ GPIOC, GPIO_PIN_8 }, // pink
		{ GPIOC, GPIO_PIN_9 }  // blue
};

typedef struct {
	volatile stepMotor_t motor;
	volatile uint8_t isrFlag;
	volatile uint16_t curStepCounter;
} clockNeedle_t;

clockNeedle_t clockNeedles[3] = { { stepMotorSecPins, 0, 0 }, {
		stepMotorMinPins, 0, 0 }, { stepMotorHourPins, 0, 0 } };

void ClockNeedle_setFlag(int idx) {
	clockNeedles[idx].isrFlag = 1;
}

void ClockNeedle_clearFlag(int idx) {
	clockNeedles[idx].isrFlag = 0;
}

void ClockNeedle_ISR(void) {
	ClockNeedle_setFlag();
}

void ClockNeedle_addStepCount(int idx) {
	if (clockNeedles[idx].curStepCounter == MAX_STEP - 1) {
		clockNeedles[idx].curStepCounter = 0;
	} else {
		clockNeedles[idx].curStepCounter++;
	}
}

void ClockNeedle_task(void) {
	for (int i = 0; i < 3; i++) {
		if (!clockNeedles[i].isrFlag) {
			return;
		}
		ClockNeedle_clearFlag(i);
		StepMotor_stepPhase(&clockNeedles[i].motor, STEPMOTOR_DIR_CW);
		ClockNeedle_addStepCount(i);
	}
}

void ClockNeedle_init(void) {
	for (int i =0; i<3;i++) {
		clockNeedles[i].isrFlag = 0;
		clockNeedles[i].curStepCounter = 0;
	}
}
