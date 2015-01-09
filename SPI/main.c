#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "led.h" 
#include "systick.h"
#include "uart.h"
#include "spi1.h"



int main(void)
{

	SysTick_Config(SYSTICK_PRESCALER);
	LED_Init();

	Usart1_Init(57600);
	Usart2_Init(57600);
	SPI1_Init();
	while (1) 
	{
			//LED Toggle
			if(GPIO_ReadOutputDataBit(LED_Port,LED_Pin))
				{LED_OFF();}
			else
				{LED_ON();}
			USART_SendData(USART2,'c');
			USART_SendData(USART1,'c');
			SPI1_ReadWriteByte(0xAA);
	}
}
