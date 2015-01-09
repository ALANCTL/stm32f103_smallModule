#ifndef __CAN_H
#define __CAN_H	 

#include "stm32f10x.h"
#include "stm32f10x_conf.h"

extern uint8_t canbuf[8];
extern CanRxMsg CAN1Rx0Message;
extern uint8_t can_RX0_received_flag;
						    
										 							 				    
u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN Initialization
 
u8 Can_Send_Msg(u8* msg,u8 len);						//Tx Data

u8 Can_Receive_Msg(u8 *buf);							//Rx Data
void USB_LP_CAN1_RX0_IRQHandler(void);

#endif

















