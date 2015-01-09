#include "can.h"
#include "led.h"

uint8_t canbuf[8];


u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode)
{

	GPIO_InitTypeDef GPIO_InitStructure; 
	CAN_InitTypeDef        CAN_InitStructure;
 	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
   	NVIC_InitTypeDef  NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	                   											 

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
  GPIO_Init(GPIOA, &GPIO_InitStructure);		
   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
 	//CAN单元设置
 	CAN_InitStructure.CAN_TTCM=DISABLE;			
 	CAN_InitStructure.CAN_ABOM=DISABLE;			
  CAN_InitStructure.CAN_AWUM=DISABLE;			
  CAN_InitStructure.CAN_NART=DISABLE;			
  CAN_InitStructure.CAN_RFLM=DISABLE;			
  CAN_InitStructure.CAN_TXFP=DISABLE;			
  CAN_InitStructure.CAN_Mode= mode;	      
  //设置波特率
  CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;    // For F4@180MHz : 1
  CAN_InitStructure.CAN_BS1=CAN_BS1_4tq;    // For F4@180MHz : 2
  CAN_InitStructure.CAN_BS2=CAN_BS2_4tq;    // For F4@180MHz : 2
  CAN_InitStructure.CAN_Prescaler=4;        // For F4@180MHz : 9
  CAN_Init(CAN1, &CAN_InitStructure);       // For F4@180MHz : 

 	CAN_FilterInitStructure.CAN_FilterNumber=0;	  //过滤器0
 	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
  CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32位 
  CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;////32位ID
  CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32位MASK
  CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//过滤器0关联到FIFO0
 	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //激活过滤器0

  CAN_FilterInit(&CAN_FilterInitStructure);//滤波器初始化
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//FIFO0消息挂号中断允许.		    
  
  NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // 主优先级为1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // 次优先级为0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	return 0;
}   
 
    CanRxMsg CAN1Rx0Message;
    uint8_t can_RX0_received_flag=0;

void USB_LP_CAN1_RX0_IRQHandler(void)
{

    CAN_Receive(CAN1, 0, &CAN1Rx0Message);
    can_RX0_received_flag=1;

}

u8 Can_Send_Msg(u8* msg,u8 len)
{	
  u8 mbox;
  u16 i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=0x12;	
  TxMessage.ExtId=0x12;	
  TxMessage.IDE=0;			
  TxMessage.RTR=0;		 
  TxMessage.DLC=len;		
  for(i=0;i<8;i++)
  TxMessage.Data[i]=msg[i];				 // 第一帧信息          
  mbox= CAN_Transmit(CAN1, &TxMessage);   
  i=0;
  while((CAN_TransmitStatus(CAN1, mbox)!=CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//等待发送结束
  if(i>=0XFFF)return 1;
  return 0;		

}

u8 Can_Receive_Msg(u8 *buf)
{		   		   
 	u32 i;
	CanRxMsg RxMessage;
    if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;		//没有接收到数据,直接退出 
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//读取数据	
    for(i=0;i<8;i++)
    buf[i]=RxMessage.Data[i];  
	return RxMessage.DLC;	
}
