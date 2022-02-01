/*
 * BMP180.h
 *
 *  Created on: Jan 26, 2022
 *      Author:izzet Ozdemir
 *
 */

#ifndef SRC_BMP180_H_
#define SRC_BMP180_H_


#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;


#define BMP180_write_address 0XEE
#define BMP180_Device_Read_REGISTER_Address 0XEF

// BMP180 Calibration Address
#define BMP180_Calibration_START_Address 0xAA


/*BMP180 Calibration Value Length*/

  #define BMP180_Calibration_Value_Length 22



// Calibration Value
int16_t AC1;
int16_t AC2;
int16_t AC3;
int16_t AC4;
int16_t AC5;
int16_t AC6;
int16_t B1;
int16_t B2;
int16_t MB;
int16_t MC;
int16_t MD;

// Temperature Value

int16_t unCompensatedTemperature;
int16_t Temperature;
int16_t tX1,tX2,tB5;
void BMP180_Init(void);
void BMP180_GetCalibration(void);
void BMP180_Get_Calibration_value(void);
void BMP180_Get_Uncompansated_Temperature(void);
void BMP180_Get_Temperature();
void BMP180_Get_Uncompansated_Presure(void);
void BMP180_Get_Presure(void);


#endif /* SRC_BMP180_H_ */
