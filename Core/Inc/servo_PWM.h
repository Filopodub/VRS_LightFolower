/**
  ******************************************************************************
  * @file           : servo_PWM.h
  * @brief          : Header for servo_PWM.c file.
  *                   Futaba S3151 servo control via TIM3_CH1 (PB4)
  *                   Note: STM32L152RE does not have TIM1, using TIM3 instead
  ******************************************************************************
  */

#ifndef __SERVO_PWM_H
#define __SERVO_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l1xx_hal.h"

/* Servo configuration defines */
#define SERVO_STEPS         30      /* Number of steps across full range */

/* PWM timing for 50Hz (20ms period) with 32MHz clock
 * Prescaler = 32 -> Timer clock = 1MHz
 * Period = 20000 -> 20ms period (50Hz)
 * Pulse range: 1000 (1ms) to 2000 (2ms) for typical servo
 */
#define SERVO_TIM_PRESCALER     31      /* (32-1) for 1MHz timer clock */
#define SERVO_TIM_PERIOD        19999   /* (20000-1) for 20ms period */
#define SERVO_PULSE_MIN         1000    /* 1ms pulse - min position */
#define SERVO_PULSE_MAX         2000    /* 2ms pulse - max position */

/* Calculate step size */
#define SERVO_STEP_SIZE         ((SERVO_PULSE_MAX - SERVO_PULSE_MIN) / SERVO_STEPS)

/* Exported types */
typedef enum {
    SERVO_DIR_FORWARD = 0,
    SERVO_DIR_BACKWARD = 1
} Servo_Direction_t;

/* Exported variables */
extern TIM_HandleTypeDef htim3;

/* Exported functions prototypes */
void Servo_Init(void);
void Servo_SetPosition(uint8_t step);
void Servo_SetPulse(uint16_t pulse);
uint8_t Servo_GetCurrentStep(void);
Servo_Direction_t Servo_GetDirection(void);
void Servo_StepForward(void);   /* One step clockwise, stops at end */
void Servo_StepBackward(void);  /* One step counter-clockwise, stops at start */

#ifdef __cplusplus
}
#endif

#endif /* __SERVO_PWM_H */
