#ifndef _HP_GPIO_H
#define _HP_GPIO_H

#include "stm32f10x.h"
#include "stm32f10x_conf.h"


void HP_GPIOInit(void);
void HP_DriveHigh(uint8_t port);
void HP_DriveLow(uint8_t port);

void HP_PWM_Init(u16 period, u16 psc);
void HP_PWM_PulseSet(uint16_t pulse);
#endif