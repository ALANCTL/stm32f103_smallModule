#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "stm32f10x.h"
#include "stm32f10x_conf.h"

#define SYS_LOOP 1 
#define LOOP_FREQ 100 //Hz
#define SYSTICK_PRESCALER (72*1000*1000/LOOP_FREQ)

extern uint32_t SYS_CNT;

/*Function Prototype*/
void SysTick_Handler(void);

#endif