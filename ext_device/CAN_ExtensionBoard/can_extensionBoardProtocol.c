#include "can_extensionBoardProtocol.h"

uint8_t PackageIdentifier(CanRxMsg* RxMessage){

	if(((RxMessage-> ExtId) & 0x1FFF0000) == 0x1FFF0000){

      LED_TOGGLE();

	}

	return 0;

}