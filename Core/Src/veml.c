#include "veml.h"
#include "i2c.h"
#include "main.h"

#define VEML_ADDR (0x10 << 1)  // 7-bit address shifted for HAL

void VEML_Init(I2C_HandleTypeDef *hi2c, uint16_t address)
{
    uint8_t buf[2] = {0x00, 0x00}; // Gain 1x, IT 100ms, ALS enabled

    if (HAL_I2C_Mem_Write(hi2c, address, VEML_REG_ALS_CONF,
                          I2C_MEMADD_SIZE_8BIT, buf, 2, HAL_MAX_DELAY) != HAL_OK)
    {
        Error_Handler();
    }

    HAL_Delay(100);
}

uint16_t VEML_ReadRaw(I2C_HandleTypeDef *hi2c, uint16_t address)
{
    uint8_t data[2];

    if (HAL_I2C_Mem_Read(hi2c, address, VEML_REG_ALS_DATA,
                         I2C_MEMADD_SIZE_8BIT, data, 2, HAL_MAX_DELAY) != HAL_OK)
    {
        Error_Handler();
    }

    return (data[1] << 8) | data[0];
}

float VEML_ReadLux(I2C_HandleTypeDef *hi2c, uint16_t address)
{
    return VEML_ReadRaw(hi2c, address) * 0.0576f;
}

uint16_t VEML_ReadID(I2C_HandleTypeDef *hi2c, uint16_t address)
{
    uint8_t data[2];

    if (HAL_I2C_Mem_Read(hi2c, address, VEML_REG_ID,
                         I2C_MEMADD_SIZE_8BIT, data, 2, HAL_MAX_DELAY) != HAL_OK)
    {
        Error_Handler();
    }

    return (data[1] << 8) | data[0];
}
