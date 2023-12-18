/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


#include "tbsAgent.h"
#include "GeneralMath.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef enum {BACKWARD, FORWARD, ESTOP, FREESTOP, STRAFELEFT, STRAFERIGHT} eDirection;
typedef enum {LEFTSIDE, RIGHTSIDE, LEFTFRONT, LEFTBACK, RIGHTFRONT, RIGHTBACK, FRONTSIDE, BACKSIDE} eMOTOR;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USART2_TX_TBS_Pin GPIO_PIN_2
#define USART2_TX_TBS_GPIO_Port GPIOA
#define USART2_RX_TBS_Pin GPIO_PIN_3
#define USART2_RX_TBS_GPIO_Port GPIOA
#define GPIO_Motor_FL_IN1_Pin GPIO_PIN_0
#define GPIO_Motor_FL_IN1_GPIO_Port GPIOB
#define GPIO_Motor_FL_IN2_Pin GPIO_PIN_1
#define GPIO_Motor_FL_IN2_GPIO_Port GPIOB
#define GPIO_Motor_FR_IN3_Pin GPIO_PIN_2
#define GPIO_Motor_FR_IN3_GPIO_Port GPIOB
#define GPIO_Motor_FR_IN4_Pin GPIO_PIN_10
#define GPIO_Motor_FR_IN4_GPIO_Port GPIOB
#define GPIO_Motor_BL_IN1_Pin GPIO_PIN_12
#define GPIO_Motor_BL_IN1_GPIO_Port GPIOB
#define GPIO_Motor_BL_IN2_Pin GPIO_PIN_13
#define GPIO_Motor_BL_IN2_GPIO_Port GPIOB
#define GPIO_Motor_BR_IN3_Pin GPIO_PIN_14
#define GPIO_Motor_BR_IN3_GPIO_Port GPIOB
#define GPIO_Motor_BR_IN4_Pin GPIO_PIN_15
#define GPIO_Motor_BR_IN4_GPIO_Port GPIOB
#define Motor_FL_Enable_Pin GPIO_PIN_8
#define Motor_FL_Enable_GPIO_Port GPIOA
#define Motor_FR_Enable_Pin GPIO_PIN_9
#define Motor_FR_Enable_GPIO_Port GPIOA
#define Motor_BL_Enable_Pin GPIO_PIN_10
#define Motor_BL_Enable_GPIO_Port GPIOA
#define Motor_BR_Enable_Pin GPIO_PIN_11
#define Motor_BR_Enable_GPIO_Port GPIOA
#define USART1_TX_GPS_Pin GPIO_PIN_15
#define USART1_TX_GPS_GPIO_Port GPIOA
#define USART1_RX_GPS_Pin GPIO_PIN_3
#define USART1_RX_GPS_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern bool newPWMValueAvailabe;
extern int16_t centerThrottle;
extern int16_t centerRotate;
extern int16_t centerStrafe;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
