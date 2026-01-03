#include "veml.h"
#include "i2c.h"
#include "main.h"

void VEML_Init(void)
{
    uint8_t buf[3];

    /* ALS_CONF register (0x00)
     * Gain 1x
     * IT 100ms
     * Shutdown = 0
     */
    buf[0] = VEML_REG_ALS_CONF;
    buf[1] = 0x00;   // LSB
    buf[2] = 0x00;   // MSB

    if (HAL_I2C_Master_Transmit(&hi2c1, VEML7700_ADDR, buf, 3, HAL_MAX_DELAY) != HAL_OK)
    {
        Error_Handler();
    }

    HAL_Delay(100); // wait for first conversion
}

uint16_t VEML_ReadRaw(void)
{
    uint8_t reg = VEML_REG_ALS_DATA;
    uint8_t data[2];

    if (HAL_I2C_Master_Transmit(&hi2c1, VEML7700_ADDR, &reg, 1, HAL_MAX_DELAY) != HAL_OK)
        Error_Handler();

    if (HAL_I2C_Master_Receive(&hi2c1, VEML7700_ADDR, data, 2, HAL_MAX_DELAY) != HAL_OK)
        Error_Handler();

    return (data[1] << 8) | data[0];
}

float VEML_ReadLux(void)
{
    uint16_t raw = VEML_ReadRaw();

    /* Datasheet: 0.0576 lux per count (Gain 1x, IT 100ms) */
    return raw * 0.0576f;
}
