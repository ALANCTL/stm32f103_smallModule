#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "led.h" 
#include "myprintf.h"
#include "uart.h"
#include "pwm.h"
#include "systick.h"
#include "can.h"
#include "can_extensionBoardProtocol.h"
#include "hmc5983.h"
#include "HP_GPIO.h"

#include "math.h"

static inline void Delay(uint32_t nCnt_1us)
{

      while(nCnt_1us--);
}

int main(void)
{

  MagnetoDataPacket_t MagDataPacket;
  uint16_t package_type=0;
	SysTick_Config(SYSTICK_PRESCALER);
	LED_Init();
	//Usart2_Init(115200);
	Myprintf_Init(0x00,myputc);


  SPI1_Init();
  HP_GPIOInit();
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS1_8tq,CAN_BS2_7tq,5,CAN_Mode_Normal);//CAN初始化环回模式,波特率450Kbps

  //CAN_Transmit(CAN1, &TxMessage);   
      Delay(100000);

    hmc5983_initialize_config();
    hmc5983_GPIODRDYInitialization();

    MagDataPacket.ID = 0x01;
    MagDataPacket.Data[0] = 0;
    MagDataPacket.Data[1] = 0;
    MagDataPacket.Data[2] = 0;
    MagDataPacket.Data[3] = 0;
    MagDataPacket.Data[4] = 0;
    MagDataPacket.Data[5] = 0;


	while (1) 
	{


    if(hmc5983_DRDY_Check()==1){


         hmc5983_update();
         LED_TOGGLE();

         {
            uint8_t i=0;

            for(i=0;i<6;i++){
                MagDataPacket.Data[i] = hmc5983_buffer[i];

            }


         }


        CANExt_MagnetometerTransmitData(&MagDataPacket);
    }






    // while( !hmc5983_DRDY_Check() ){


    // }
    // hmc5983_update();
    // LED_TOGGLE();

  //CAN_Transmit(CAN1, &TxMessage); 
			
	}
}
