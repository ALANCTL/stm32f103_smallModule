#include "can_extensionBoardProtocol.h"

f4discoveryGyroPacket_t f4discoveryGyroData;
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