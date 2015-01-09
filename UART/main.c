#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "led.h" 
#include "systick.h"
#include "usart2.h"



int main(void)
{

	SysTick_Config(SYSTICK_PRESCALER);
	LED_Init();

	Usart2_Init(57600);

	while (1) 
	{
			//LED Toggle
			if(GPIO_ReadOutputDataBit(LED_Port,LED_Pin))
				{LED_OFF();}
			else
				{LED_ON();}
			USART_SendData(USART2,'c');
	}
}
