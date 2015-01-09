#include "systick.h"

uint32_t SYS_CNT = 0; //system timer count

void SysTick_Handler(void)
{
  if(SYS_CNT<SYS_LOOP)
      SYS_CNT++;
}
