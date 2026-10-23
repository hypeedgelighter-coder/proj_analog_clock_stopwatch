/*
 * AnalogClock.h
 *
 *  Created on: 2026. 10. 23.
 *      Author: kccistc
 */

#ifndef SRC_AP_ANALOGCLOCK_ANALOGCLOCK_H_
#define SRC_AP_ANALOGCLOCK_ANALOGCLOCK_H_

#include "../../driver/stepmotor/stepmotor.h"

void ClockNeedle_ISR(void);
void ClockNeedle_task(void);

#endif /* SRC_AP_ANALOGCLOCK_ANALOGCLOCK_H_ */
