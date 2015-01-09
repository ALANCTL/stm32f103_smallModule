#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "led.h" 
#include "systick.h"

static inline void Delay_1us(uint32_t nCnt_1us)
{
  volatile uint32_t nCnt;

  for (; nCnt_1us != 0; nCnt_1us--)
    for (nCnt = 13; nCnt != 0; nCnt--);
}

static inline void Delay(uint32_t nCnt_1us)
{

			while(nCnt_1us--);
}

#define REPEAT_CNT 10
int main(void)
{
	uint16_t runner = 0;
	uint8_t dir=1;
	uint8_t cnt_delay = REPEAT_CNT;
	SysTick_Config(SYSTICK_PRESCALER);
	LED_Init();
	HP_GPIOInit();

	while (1) 
	{

			 HP_DriveHigh(0);

	Delay(runner);

	if(dir==1){
		if(cnt_delay--){


		}else{


		cnt_delay = REPEAT_CNT;
		runner++;


		}

	}else{

		if(cnt_delay--){


		}else{

		
		cnt_delay = REPEAT_CNT;
		runner--;


		}

	}

	if(runner > 2900) dir=0;
	else if (runner < 100) dir=1;
			// HP_DriveLow(0);
	Delay(3000 - runner);
			//LED Toggle
			if(GPIO_ReadOutputDataBit(LED_Port,LED_Pin))
				{LED_OFF();}
			else
				{LED_ON();}

	}
}
