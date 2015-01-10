#include "can_extensionBoardProtocol.h"


uint16_t CANExtPackageIdentifier(CanRxMsg* RxMessage){

	if(((RxMessage-> ExtId) & 0x1FFF0000) == 0x1FFF0000){

		return MSG_DISCOVERY_TEST;

	}

	return 0;

}

f4discoveryGyroPacket_t CANExt_DiscoveryPacketUnpack(CanRxMsg* RxMessage){

f4discoveryGyroPacket_t f4discoveryGyroData;


			uint8_t * ptr = & f4discoveryGyroData.GyroZ;

                ptr[0] = RxMessage -> Data[0];
                ptr[1] = RxMessage -> Data[1];
                ptr[2] = RxMessage -> Data[2];
                ptr[3] = RxMessage -> Data[3];

			f4discoveryGyroData.ID = (RxMessage -> ExtId & 0x00000011);



return f4discoveryGyroData;
}


MagnetoInitializePacket_t CANExt_MagnetometerPacketUnpack(CanRxMsg* RxMessage){

MagnetoInitializePacket_t MagnetoInitializePacket;

        MagnetoInitializePacket.Mode = RxMessage -> Data[0];
        MagnetoInitializePacket.DataRate = RxMessage -> Data[1];

return  MagnetoInitializePacket;
}



  void CANExt_MagnetometerTransmitData(MagnetoDataPacket_t * MagDataPacket){

 	CanTxMsg TxMessage;

  	TxMessage.ExtId=0x00030000 | ((uint32_t)MagDataPacket -> ID)<<8 | 0x000000F1;
  	TxMessage.IDE=0;		
  	TxMessage.RTR=0;		
  	TxMessage.DLC=6;		
  	
  	TxMessage.Data[0]= MagDataPacket -> Data[0];
  	TxMessage.Data[1]= MagDataPacket -> Data[1];
  	TxMessage.Data[2]= MagDataPacket -> Data[2];
  	TxMessage.Data[3]= MagDataPacket -> Data[3];
  	TxMessage.Data[4]= MagDataPacket -> Data[4];	
  	TxMessage.Data[5]= MagDataPacket -> Data[5];
  	
  	CAN_Transmit(CAN1, &TxMessage);  



  }