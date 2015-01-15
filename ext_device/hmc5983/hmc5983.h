#ifndef FILE_HMC5983_H
#define FILE_HMC5983_H

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "spi1.h"

#define HMC5983_CONFIG_REG_A 0x00
#define HMC5983_CONFIG_REG_B 0x01
#define HMC5983_MODE_REG 0x02
#define HMC5983_DATA_OUTOUT_X_H 0x03
#define HMC5983_STATUS_REG 0x09

// Now Using SPI1 with CS pins on HP2 (PA4)
#define HMC5983_SPI SPI1
#define HMC5983_SELECT() 	GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define HMC5983_DESELECT() 	GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define HMC5983_DRDY_READ()  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)


extern uint8_t hmc5983_buffer[6];


uint8_t hmc5983_readByte(uint8_t addr);
void hmc5983_delay(volatile uint32_t );
void hmc5983_initialize_config(void);
void hmc5983_update(void);
uint8_t hmc5983_DRDY_Check(void);
void hmc5983_GPIODRDYInitialization(void);
uint8_t hmc5983_SPIchkDRDY(void);

#endif