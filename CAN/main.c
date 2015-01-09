#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "led.h" 
#include "myprintf.h"
#include "usart2.h"
#include "pwm.h"
#include "systick.h"
#include "can.h"

int main(void)
{
	uint16_t loop_cnt = 0;
	uint16_t max6675_cycle = 0;

 	CanTxMsg TxMessage;

	SysTick_Config(SYSTICK_PRESCALER);
	LED_Init();
	Usart2_Init(115200);
	Myprintf_Init(0x00,myputc);
	PWM_Init(65535,71); //1us as unit
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS1_8tq,CAN_BS2_7tq,5,CAN_Mode_Normal);//CAN初始化环回模式,波特率450Kbps

  TxMessage.StdId=0x12;
  TxMessage.ExtId=0x12;
  TxMessage.IDE=0;		
  TxMessage.RTR=0;		
  TxMessage.DLC=4;		
  
  TxMessage.Data[0]= 0x01;
  TxMessage.Data[1]= 0x01;
  TxMessage.Data[2]= 0x01;
  TxMessage.Data[3]= 0x01;
  TxMessage.Data[4]= 0x01;		        
  CAN_Transmit(CAN1, &TxMessage);   

	while (1) 
	{
			//LED Toggle
			if(GPIO_ReadOutputDataBit(LED_Port,LED_Pin))
				{LED_OFF();}
			else
				{LED_ON();}
			loop_cnt++;
		     
  CAN_Transmit(CAN1, &TxMessage); 
			
	}
}
