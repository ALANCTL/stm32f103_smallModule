#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"
#include "stm32f10x_conf.h"

/*LED Pin Definition*/
#define LED_Port		GPIOB
#define LED_CLK			RCC_APB2Periph_GPIOB
#define LED_Pin			GPIO_Pin_3
#define LED_ON()		GPIO_SetBits( LED_Port, LED_Pin );  
#define LED_OFF()		GPIO_ResetBits( LED_Port, LED_Pin );
#define LED_TOGGLE()	if(GPIO_ReadOutputDataBit(LED_Port,LED_Pin)){LED_OFF();}else{LED_ON();}
		     
/*Function Prototype*/
//LED Initial 
void LED_Init(void);

#endif