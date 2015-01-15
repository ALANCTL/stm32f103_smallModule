// ADS1246_MPX6115A.c
#include "ADS1246_MPX6115A.h"


void ads1246_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE );	

	/* Enable START, RESET DRDY pins */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10| GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void ads1246_SPI1_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

   	//開啟Poart_A與SPI1時鐘
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE );	
	
   	 //SPI1腳位初始化
	/* 設置 SPI1 pins: SCK, MISO and MOSI */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //復用推挽輸出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//將SCK,MISO腳位拉高
	// GPIO_SetBits(GPIOA,GPIO_Pin_5);
	// GPIO_SetBits(GPIOA,GPIO_Pin_6);

	/* SPI1 設置 */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //設置SPI單向或是雙向的數據傳輸模式→SPI1設定為雙向雙向雙全工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;						//設置SPI為主SPI,Mater
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;					//設置SPI數據傳輸大小→SPI發送與接收8bit的Byte結構
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;							//設置SPI在閒置時SCK狀態
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;						//設置SPI在第一個SCK上升/下降或是第二個SCK上升/下降時傳送/讀取資料
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;							//NSS訊號由硬體或是軟體控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//設置SPI使用BaudRate預分頻
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;					//設置數據傳輸是MSB→LSB或是LSB→MSB :設定為MSB開始
	SPI_InitStructure.SPI_CRCPolynomial = 7;							//CRC值計算的多項式
	SPI_Init(SPI1, &SPI_InitStructure);  								//根據SPI_IniStruct指定的參數寫入SPIx寄存器

	/* 開啟 SPI1  */
	SPI_Cmd(SPI1, ENABLE); 

	SPI1_ReadWriteByte(0xff);//啟動傳輸	
}  
 

int32_t mpx6115A_tare_value;

void ads1246_delay(volatile uint32_t count)
{
	count = count/5;

	while (count--) {

	}
}
void ads1246_reset(void){

ADS1246_RESET_HIGH();
ads1246_delay(100000);
ADS1246_RESET_LOW();
ads1246_delay(100000);
ADS1246_RESET_HIGH();
ads1246_delay(100000);
ads1246_delay(100000);
}

uint8_t ads1246_read1byte(uint8_t addr){

	uint8_t output=0;

	SPI_xfer(ADS1246_MPX6115A_SPI,0x20|addr);
	SPI_xfer(ADS1246_MPX6115A_SPI,0x00);
	output = SPI_xfer(ADS1246_MPX6115A_SPI,0xFF);
	return output;

}

void ads1246_write1byte(uint8_t addr, uint8_t data){

	SPI_xfer(ADS1246_MPX6115A_SPI,0x40|addr);
	SPI_xfer(ADS1246_MPX6115A_SPI,0x00);
	SPI_xfer(ADS1246_MPX6115A_SPI,data);

}

int32_t ads1246_readADCconversion(void){

	uint8_t rxdat1=0,rxdat2=0,rxdat3=0;


	rxdat1 = SPI_xfer(ADS1246_MPX6115A_SPI,0xFF);
	rxdat2 = SPI_xfer(ADS1246_MPX6115A_SPI,0xFF);
	rxdat3 = SPI_xfer(ADS1246_MPX6115A_SPI,0xFF);

	return  (uint32_t)rxdat1<<16 | (uint32_t)rxdat2<<8 |  (uint32_t)rxdat3;
}

void ads1246_initialize(void){

	ads1246_reset();
	ADS1246_CS_HIGH(); // Deselect the chip to reset SPI
	ads1246_delay(100000);
	ADS1246_CS_LOW(); // Select the chip to initiate transmission
	ADS1246_START_HIGH(); // Set start high to initiate communication
	ads1246_write1byte(0x03,0b00001000); // Write sampling configuration at 0x03 register 
	ads1246_delay(1000);

	/* There should be one spi_xfer ( 0x14 ) here (read_continous command). But not sure if it needs or not */

	while(ADS1246_DRDY_PIN_STATE()){
	}

	mpx6115A_tare_value = ads1246_readADCconversion();

}

float MPX6115_get_raw_altitude(int32_t adc_data){


	return (float)((mpx6115A_tare_value)-adc_data)*ALT_PER_LSB ;

}


void MPX6115_update_tare_value(void){

	while(ADS1246_DRDY_PIN_STATE()){
	}

	mpx6115A_tare_value = ads1246_readADCconversion();


}