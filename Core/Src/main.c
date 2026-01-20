
#include "main.h"
#include "i2c.h"
#include "gpio.h"
#include "veml.h"

#define VEML_ADDR   (0x10 << 1)

void SystemClock_Config(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();


  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();

  HAL_Delay(100);

  /* Initialize both sensors */
  VEML_Init(&hi2c1, VEML_ADDR);
  VEML_Init(&hi2c2, VEML_ADDR);

  HAL_Delay(10);

  volatile uint16_t raw1 = 0, raw2 = 0;
  volatile float lux1 = 0, lux2 = 0;
  volatile uint16_t id1 = VEML_ReadID(&hi2c1, VEML_ADDR);
  volatile uint16_t id2 = VEML_ReadID(&hi2c2, VEML_ADDR);

  while (1)
  {
	  raw1 = VEML_ReadRaw(&hi2c1, VEML_ADDR);
	  lux1 = VEML_ReadLux(&hi2c1, VEML_ADDR);

	  raw2 = VEML_ReadRaw(&hi2c2, VEML_ADDR);
	  lux2 = VEML_ReadLux(&hi2c2, VEML_ADDR);

	  HAL_Delay(500);
  }






//  if (VEML_Ping(&hi2c2, VEML7700_ADDR) != HAL_OK)
//  {
//	  Error_Handler(); // sensor missing
//  }
//  VEML_Init(&hi2c2, VEML7700_ADDR);
//  volatile float lux1 = 0;
//  volatile float lux2 = 0;
//
//  while (1)
//  {
//	  lux1 = VEML_ReadLux(&hi2c1, VEML7700_ADDR);
//	  lux2 = VEML_ReadLux(&hi2c2, VEML7700_ADDR);
//
//	  HAL_Delay(500);
//  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
