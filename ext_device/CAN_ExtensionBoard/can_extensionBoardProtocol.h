#ifndef _CAN_EXTENSIONBOARDPROTOCOL_H
#define _CAN_EXTENSIONBOARDPROTOCOL_H

#include "can.h"
#include "led.h"

typedef struct f4discoveryGyroPacket_t {
	uint16_t ID;
	float GyroZ;
} f4discoveryGyroPacket_t;

extern f4discoveryGyroPacket_t f4discoveryGyroData;



uint16_t CANExtPackageIdentifier(CanRxMsg* RxMessage);
f4discoveryGyroPacket_t CANExt_DiscoveryPacketUnpack(CanRxMsg* RxMessage);


#define MSG_DISCOVERY_TEST 0xFFFF

#endif