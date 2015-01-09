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

void HP_GPIOInit(void){


	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(LED_CLK, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB , ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	//Configure LED Pin
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = 	GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_1 | GPIO_Pin_4; 	
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = 	GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_5; 	
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void HP_DriveHigh(uint8_t port){

	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);


	if(port ==1){



	}else if (port == 2){


	}else if (port == 3){



	}


}

void HP_DriveLow(uint8_t port){

	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);

	if(port ==1){



	}else if (port == 2){


	}else if (port == 3){



	}


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
