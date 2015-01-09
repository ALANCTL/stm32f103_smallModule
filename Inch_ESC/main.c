#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "led.h" 
#include "myprintf.h"
#include "usart2.h"
#include "pwradc.h"
#include "pwm.h"
#include "max6675.h"
#include "systick.h"
#include "can.h"

uint8_t CANBufIsNotEmpty(void);
void ClearCANBuf(void);
uint8_t CANBufIsThrottleCut(void);
uint8_t CANBufIsThrottleRelease(void);

uint16_t throttlecut_pwm = 998; //throttle cut dutycycle

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

	SysTick_Config(SYSTICK_PRESCALER);
	LED_Init();
	Usart2_Init(115200);
	Myprintf_Init(0x00,myputc);
	PWRADC_Init();
	PWM_Init(65535,71); //1us as unit
	MAX6675_Init();
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS1_8tq,CAN_BS2_7tq,5,CAN_Mode_Normal);//CAN初始化环回模式,波特率450Kbps

	max6675_cycle = LOOP_FREQ/5 ;

	while (1) 
	{
		if(SYS_CNT>=SYS_LOOP)
		{
			//Reset loop status
			SYS_CNT = 0;
			//Check if receving CAN bus message
			if(CANBufIsNotEmpty())
			{
				if(CANBufIsThrottleCut()) //throttle cut message
				{
			    	//Throttle Ouput to Servo
			    	Throttle_Output(throttlecut_pwm);
			    	my_printf("throttle cut!!\r\n");
					//waiting for user releasing throttle cut
					while(CANBufIsThrottleRelease()!=1);
					my_printf("throttle released!!\r\n");
					//bypass RC PWM into servo PWM
		    		Throttle_Output(rc_pwm);					
				}
				//clear canbuf[]
				ClearCANBuf();
			}
			else
			{
				//Get power voltage
				dpwr_volt = pwr_adc_Value;
				dpwr_volt = (double)(dpwr_volt*10.0/4095);
				intpwr_volt = (int32_t)(dpwr_volt*1000);
				//Get RPM Input
		    	if(rpm_cycle!=0)
		    		engine_rpm = (60000000/rpm_cycle);
		    	else 
		    		engine_rpm = 0;
				//Get Master PWM Input

		    	//Get Engine Temperature
		    	if(loop_cnt==max6675_cycle)
		    	{
		    		Read_MAX6675(&Engine_Temperature);
		    		loop_cnt = 0;
		    	}
		    	//Throttle Ouput to Servo
		    	Throttle_Output(rc_pwm);

				//my_printf("Power Voltage:%d, Engine RPM:%d, Throttle CMD:%d, Engine Temperature:%d \r\n",intpwr_volt,engine_rpm,rc_pwm,Engine_Temperature);
				//my_printf("Engine RPM=%d, Throttle CMD=%d\r\n",engine_rpm,rc_pwm);
				my_printf("%d\r\n",engine_rpm);
			}
			//LED Toggle
			if(GPIO_ReadOutputDataBit(LED_Port,LED_Pin))
				{LED_OFF();}
			else
				{LED_ON();}
			loop_cnt++;
		}

	}
}
