#ifndef __VEML7700_H
#define __VEML7700_H

#include "stm32f3xx_hal.h"

/* 7-bit I2C address shifted for HAL */
#define VEML7700_ADDR     (0x10 << 1)

/* Registers */
#define VEML_REG_ALS_CONF  0x00
#define VEML_REG_ALS_DATA  0x04

void     VEML_Init(void);
uint16_t VEML_ReadRaw(void);
float    VEML_ReadLux(void);

#endif
