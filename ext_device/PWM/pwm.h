#ifndef _PWM_H
#define _PWM_H

#include "stm32f10x.h"
#include "stm32f10x_conf.h"

extern int rpm_cycle; //rpm cycle(us)
extern int rc_pwm; //RC pwm input duty cycle(us)
extern int32_t engine_rpm; //engine rpm

void PWM_Init(u16 arr, u16 psc);
void Throttle_Output(uint16_t dutycyle);

#endif