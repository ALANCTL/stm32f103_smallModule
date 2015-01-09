#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "led.h" 
#include "systick.h"



int main(void)
{

	SysTick_Config(SYSTICK_PRESCALER);
	LED_Init();


	while (1) 
	{
			//LED Toggle
			if(GPIO_ReadOutputDataBit(LED_Port,LED_Pin))
				{LED_OFF();}
			else
				{LED_ON();}

	}
}
