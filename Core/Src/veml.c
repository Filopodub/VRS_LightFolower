#include "veml.h"
#include "i2c.h"
#include "main.h"

/* Initialize VEML7700 sensor */
void VEML_Init(void)
{
    uint8_t buf[2];

    /* ALS_CONF register (0x00)
     * Gain 1x
     * Integration Time 100ms
     * Shutdown = 0
     */
    buf[0] = 0x00; // LSB
    buf[1] = 0x00; // MSB

    if (HAL_I2C_Mem_Write(&hi2c1, VEML7700_ADDR, VEML_REG_ALS_CONF,
                          I2C_MEMADD_SIZE_8BIT, buf, 2, HAL_MAX_DELAY) != HAL_OK)
    {
        Error_Handler();
    }

    HAL_Delay(100); // wait for first conversion
}

/* Read raw ALS value */
uint16_t VEML_ReadRaw(void)
{
    uint8_t data[2];

    if (HAL_I2C_Mem_Read(&hi2c1, VEML7700_ADDR, VEML_REG_ALS_DATA,
                         I2C_MEMADD_SIZE_8BIT, data, 2, HAL_MAX_DELAY) != HAL_OK)
    {
        Error_Handler();
    }

    return (data[1] << 8) | data[0];
}

/* Convert raw value to lux */
float VEML_ReadLux(void)
{
    uint16_t raw = VEML_ReadRaw();
    return raw * 0.0576f; // gain 1x, IT 100ms
}

/* Read device ID */
uint16_t VEML_ReadID(void)
{
    uint8_t data[2];

    if (HAL_I2C_Mem_Read(&hi2c1, VEML7700_ADDR, 0x07,
                         I2C_MEMADD_SIZE_8BIT, data, 2, HAL_MAX_DELAY) != HAL_OK)
    {
        Error_Handler();
    }

    return (data[1] << 8) | data[0];
}
