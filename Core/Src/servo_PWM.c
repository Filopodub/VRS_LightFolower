/**
  ******************************************************************************
  * @file           : servo_PWM.c
  * @brief          : Futaba S3151 servo control via TIM3_CH1 (PB4)
  ******************************************************************************
  */

#include "servo_PWM.h"
#include "main.h"

TIM_HandleTypeDef htim3;
static uint8_t current_step = 0;
static Servo_Direction_t current_direction = SERVO_DIR_FORWARD;

static void MX_TIM3_Init(void);
static void Servo_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/**
  * @brief  Initialize servo PWM (TIM3 CH1 on PB4)
  * @retval None
  */
void Servo_Init(void)
{
    MX_TIM3_Init();
 
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    Servo_SetPosition(0);
}

/**
  * @brief  Set servo position by step number (0 to SERVO_STEPS)
  * @param  step: Step number (0 to SERVO_STEPS)
  * @retval None
  */
void Servo_SetPosition(uint8_t step)
{
    if (step > SERVO_STEPS) {
        step = SERVO_STEPS;
    }
    
    current_step = step;
    uint16_t pulse = SERVO_PULSE_MIN + (step * SERVO_STEP_SIZE);
    Servo_SetPulse(pulse);
}

/**
  * @brief  Set servo pulse width directly
  * @param  pulse: Pulse width in timer ticks (typically 1000-2000 for 1-2ms)
  * @retval None
  */
void Servo_SetPulse(uint16_t pulse)
{
    if (pulse < SERVO_PULSE_MIN) {
        pulse = SERVO_PULSE_MIN;
    }
    if (pulse > SERVO_PULSE_MAX) {
        pulse = SERVO_PULSE_MAX;
    }
    
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse);
}

/**
  * @brief  Get current servo step position
  * @retval Current step (0 to SERVO_STEPS)
  */
uint8_t Servo_GetCurrentStep(void)
{
    return current_step;
}

/**
  * @brief  Get current servo direction
  * @retval Current direction
  */
Servo_Direction_t Servo_GetDirection(void)
{
    return current_direction;
}

/**
  * @brief  Perform one step forward (clockwise)
  *         Stops at end position (SERVO_STEPS)
  * @retval None
  */
void Servo_StepForward(void)
{
    if (current_step < SERVO_STEPS) {
        current_step++;
        current_direction = SERVO_DIR_FORWARD;
        Servo_SetPosition(current_step);
    }
}

/**
  * @brief  Perform one step backward (counter-clockwise)
  *         Stops at start position (0)
  * @retval None
  */
void Servo_StepBackward(void)
{
    if (current_step > 0) {
        current_step--;
        current_direction = SERVO_DIR_BACKWARD;
        Servo_SetPosition(current_step);
    }
}

/**
  * @brief  TIM3 Initialization Function (PWM mode)
  * @retval None
  */
static void MX_TIM3_Init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    __HAL_RCC_TIM3_CLK_ENABLE();

    htim3.Instance = TIM3;
    htim3.Init.Prescaler = SERVO_TIM_PRESCALER;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = SERVO_TIM_PERIOD;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    
    if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
        Error_Handler();
    }
    
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    
    if (HAL_TIM_PWM_Init(&htim3) != HAL_OK) {
        Error_Handler();
    }
    
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
    
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = SERVO_PULSE_MIN;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    
    if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }
    
    Servo_TIM_MspPostInit(&htim3);
}

/**
  * @brief  TIM3 MSP Post Initialization - Configure PB4 as TIM3_CH1
  * @param  htim: TIM handle pointer
  * @retval None
  */
static void Servo_TIM_MspPostInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    if (htim->Instance == TIM3) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
        
        GPIO_InitStruct.Pin = GPIO_PIN_4;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
}
