/*
 * BMP180.c
 *
 *  Created on: Jan 26, 2022
 *      Author:izzet Ozdemir
 */


#include "BMP180.h"

void BMP180_Init()
{
if(HAL_I2C_IsDeviceReady(&hi2c1, BMP180_write_address, 1, 10000) == HAL_OK)

	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_SET);


	BMP180_Get_Calibration_value();

}
void BMP180_Get_Calibration_value()
{
	int a=0;
	uint8_t calibBuff[BMP180_Calibration_Value_Length] = {0};

	HAL_I2C_Mem_Read(&hi2c1,BMP180_Device_Read_REGISTER_Address, BMP180_Calibration_START_Address, 1, calibBuff,BMP180_Calibration_Value_Length, 10000);

	AC1 =(uint16_t*)(calibBuff[a] << 8 | calibBuff[a+1]); a+=2;
	AC2= (uint16_t*)(calibBuff[a] << 8 | calibBuff[a+1]); a+=2;
	AC3 =(uint16_t*)(calibBuff[a] << 8 | calibBuff[a+1]); a+=2;
	AC4 =(uint16_t*)(calibBuff[a] << 8 | calibBuff[a+1]); a+=2;
	AC5 =(uint16_t*)(calibBuff[a] << 8 | calibBuff[a+1]); a+=2;
	AC6 =(uint16_t*)(calibBuff[a] << 8 | calibBuff[a+1]); a+=2;
	B1 =(uint16_t*)(calibBuff[a] << 8 | calibBuff[a+1]); a+=2;
	B2 =(uint16_t*)(calibBuff[a] << 8 | calibBuff[a+1]); a+=2;
	MB =(uint16_t*)(calibBuff[a] << 8 | calibBuff[a+1]); a+=2;
	MC =(uint16_t*)(calibBuff[a] << 8 | calibBuff[a+1]); a+=2;
	MD =(uint16_t*)(calibBuff[a] << 8 | calibBuff[a+1]); a+=2;

}

void BMP180_Get_Temperature()
{
	tX1 = (((int32_t)unCompensatedTemperature -(int32_t)AC6) *(int32_t)AC5) / 32768;
	tX2 = ((int32_t) MC *2048) / (tX1 + (int32_t)MD);
	tB5 = tX1+tX2;

	Temperature =(float)(tB5 +8) /16 *0.1;

}

void BMP180_Get_Uncompansated_Temperature(void)
{
	uint8_t wData[1];
	uint8_t rData[2]={0};


	wData[0] =0x2E;
	HAL_I2C_Mem_Write(&hi2c1,BMP180_Device_Read_REGISTER_Address, 0xF4, 1,wData, 1, 100000);
	HAL_Delay(5);

	HAL_I2C_Mem_Read(&hi2c1, BMP180_Device_Read_REGISTER_Address, 0xF6,1,rData, 2, 100000);
	unCompensatedTemperature = (int16_t)(rData[0] << 8 ) | rData[1];
}




