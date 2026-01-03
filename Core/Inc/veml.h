#ifndef __VEML7700_H
#define __VEML7700_H

#include "stm32f3xx_hal.h"

/* 7-bit I2C address shifted for HAL */
//#define VEML7700_ADDR     (0x10 << 1)
#define VEML7700_ADDR (0x10 << 1)  // 0x23 = 7-bit adresa


/* Registers */
#define VEML_REG_ALS_CONF  0x00
#define VEML_REG_ALS_DATA  0x04
#define VEML_REG_ID        0x07   // 👈 CHÝBALO

void     VEML_Init(void);
uint16_t VEML_ReadRaw(void);
float    VEML_ReadLux(void);
uint16_t VEML_ReadID(void);

#endif
