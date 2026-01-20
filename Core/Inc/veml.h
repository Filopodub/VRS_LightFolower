#ifndef __VEML_H
#define __VEML_H

#include "stm32l1xx_hal.h"

#define VEML_REG_ALS_CONF 0x00
#define VEML_REG_ALS_DATA 0x04
#define VEML_REG_ID       0x07

void  		VEML_Init(I2C_HandleTypeDef *hi2c,uint16_t address);
uint16_t 	VEML_ReadRaw(I2C_HandleTypeDef *hi2c,uint16_t address);
float 		VEML_ReadLux(I2C_HandleTypeDef *hi2c,uint16_t address);
uint16_t 	VEML_ReadID(I2C_HandleTypeDef *hi2c,uint16_t address);

#endif
