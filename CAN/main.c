#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "led.h" 
#include "myprintf.h"
#include "usart2.h"
#include "pwm.h"
#include "systick.h"
#include "can.h"


uint8_t CANBufIsNotEmpty(void)
{
	uint8_t i=0;
	Can_Receive_Msg(canbuf);
	for(i=0;i<8;i++)
	{
		if(canbuf[i]!=0x00) return 1;
	}
	return 0;
}

void ClearCANBuf(void)
{
	uint8_t i=0;

	for(i=0;i<8;i++)
	{
		canbuf[i]=0x00;
	}
}

uint8_t CANBufIsThrottleCut(void)
{
	uint8_t i =0;
	Can_Receive_Msg(canbuf);
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case 0: if(canbuf[i]!=0x21) return 0;
			break;
			case 1: if(canbuf[i]!=0x22) return 0;
			break;
			case 2: if(canbuf[i]!=0x23) return 0;
			break;
			case 3: if(canbuf[i]!=0x24) return 0;
			break;
			case 4: if(canbuf[i]!=0x31) return 0;
			break;
			case 5: if(canbuf[i]!=0x41) return 0;
			break;
			case 6: if(canbuf[i]!=0x51) return 0;
			break;
			case 7: if(canbuf[i]!=0x61) return 0;
			break;
			default:
			break;
		}
	}
	return 1;
}

uint8_t CANBufIsThrottleRelease(void)
{
	uint8_t i =0;

	Can_Receive_Msg(canbuf);
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case 0: if(canbuf[i]!=0x51) return 0;
			break;
			case 1: if(canbuf[i]!=0x52) return 0;
			break;
			case 2: if(canbuf[i]!=0x53) return 0;
			break;
			case 3: if(canbuf[i]!=0x54) return 0;
			break;
			case 4: if(canbuf[i]!=0x51) return 0;
			break;
			case 5: if(canbuf[i]!=0x61) return 0;
			break;
			case 6: if(canbuf[i]!=0x71) return 0;
			break;
			case 7: if(canbuf[i]!=0x81) return 0;
			break;
			default:
			break;
		}
	}
	return 1;
}

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
  
  TxMessage.Data[0];
  TxMessage.Data[1];
  TxMessage.Data[2];
  TxMessage.Data[3];
  TxMessage.Data[4];		        
  CAN_Transmit(CAN1, &TxMessage);   
  // while((CAN_TransmitStatus(CAN1, 0)!=CAN_TxStatus_Failed)&&(i<0XFFF));	


	while (1) 
	{
			//LED Toggle
			if(GPIO_ReadOutputDataBit(LED_Port,LED_Pin))
				{LED_OFF();}
			else
				{LED_ON();}
			loop_cnt++;
		
			
	}
}
