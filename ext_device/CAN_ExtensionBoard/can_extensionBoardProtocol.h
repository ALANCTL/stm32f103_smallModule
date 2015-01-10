#ifndef _CAN_EXTENSIONBOARDPROTOCOL_H
#define _CAN_EXTENSIONBOARDPROTOCOL_H

#include "can.h"
#include "led.h"

typedef struct f4discoveryGyroPacket_t {
	uint16_t ID;
	float GyroZ;
} f4discoveryGyroPacket_t;

typedef struct MagnetoInitializePacket_t {
	uint8_t Mode;
	float DataRate;
} MagnetoInitializePacket_t;

typedef struct MagnetoDataPacket_t {
	uint8_t ID;
	uint8_t Data[6];
} MagnetoDataPacket_t;



uint16_t CANExtPackageIdentifier(CanRxMsg* RxMessage);
f4discoveryGyroPacket_t CANExt_DiscoveryPacketUnpack(CanRxMsg* RxMessage);
MagnetoInitializePacket_t CANExt_MagnetometerPacketUnpack(CanRxMsg* RxMessage);
  void CANExt_MagnetometerTransmitData(MagnetoDataPacket_t * MagDataPacket);


#define MSG_DISCOVERY_TEST 0xFFFF

#endif