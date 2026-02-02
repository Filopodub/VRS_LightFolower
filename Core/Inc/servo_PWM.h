/**
  ******************************************************************************
  * @file           : servo_PWM.h
  * @brief          : Header for servo_PWM.c file.
  ******************************************************************************
  */

#ifndef __SERVO_PWM_H
#define __SERVO_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l1xx_hal.h"

#define SERVO_STEPS         30  


#define SERVO_TIM_PRESCALER     31      /* (32-1) for 1MHz timer clock */
#define SERVO_TIM_PERIOD        19999   /* (20000-1) for 20ms period */
#define SERVO_PULSE_MIN         1000    /* 1ms pulse - min position */
#define SERVO_PULSE_MAX         2000    /* 2ms pulse - max position */

#define SERVO_STEP_SIZE         ((SERVO_PULSE_MAX - SERVO_PULSE_MIN) / SERVO_STEPS)

typedef enum {
    SERVO_DIR_FORWARD = 0,
    SERVO_DIR_BACKWARD = 1
} Servo_Direction_t;

extern TIM_HandleTypeDef htim3;

void Servo_Init(void);
void Servo_SetPosition(uint8_t step);
void Servo_SetPulse(uint16_t pulse);
uint8_t Servo_GetCurrentStep(void);
Servo_Direction_t Servo_GetDirection(void);
void Servo_StepForward(void);
void Servo_StepBackward(void);

#ifdef __cplusplus
}
#endif

#endif 