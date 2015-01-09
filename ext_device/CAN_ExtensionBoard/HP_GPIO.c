#include "HP_GPIO.h"


void HP_PWM_Init(u16 period, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能TIM4時鐘
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//使能TIM1時鐘
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO時鐘

	TIM_DeInit(TIM2);

	//PWM output
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;  //PA1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Timer 2	 
	TIM_TimeBaseStructure.TIM_Period = period; //設定計數器自動重裝值 
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 	//預分頻器 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上計數模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根據TIM_TimeBaseInitStruct中指定的參數初始化TIMx的時間基數單位

	TIM_Cmd(TIM2, ENABLE); 		//使能計時器1
    //TPWM on TIM2_CH2 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_Pulse = 20000;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); 
	TIM_ARRPreloadConfig(TIM2, ENABLE);	
	TIM_CtrlPWMOutputs(TIM2,ENABLE);


}

void HP_PWM_PulseSet(uint16_t pulse){

	TIM2->CCR2 = pulse;

}
void HP_GPIOInit(void){


	GPIO_InitTypeDef GPIO_InitStructure;

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