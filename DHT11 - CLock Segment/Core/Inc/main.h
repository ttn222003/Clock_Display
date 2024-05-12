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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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
#define CLK_Pin GPIO_PIN_1
#define CLK_GPIO_Port GPIOA
#define LAT_Pin GPIO_PIN_2
#define LAT_GPIO_Port GPIOA
#define DATA1_Pin GPIO_PIN_3
#define DATA1_GPIO_Port GPIOA
#define B1_Pin GPIO_PIN_4
#define B1_GPIO_Port GPIOA
#define B2_Pin GPIO_PIN_5
#define B2_GPIO_Port GPIOA
#define CLK2_Pin GPIO_PIN_6
#define CLK2_GPIO_Port GPIOA
#define LAT2_Pin GPIO_PIN_7
#define LAT2_GPIO_Port GPIOA
#define STOP_Pin GPIO_PIN_10
#define STOP_GPIO_Port GPIOB
#define LED4_Pin GPIO_PIN_11
#define LED4_GPIO_Port GPIOB
#define LED5_Pin GPIO_PIN_12
#define LED5_GPIO_Port GPIOB
#define DATA2_Pin GPIO_PIN_8
#define DATA2_GPIO_Port GPIOA
#define B3_Pin GPIO_PIN_9
#define B3_GPIO_Port GPIOA
#define B4_Pin GPIO_PIN_10
#define B4_GPIO_Port GPIOA
#define INCREASE_Pin GPIO_PIN_3
#define INCREASE_GPIO_Port GPIOB
#define INCREASE_EXTI_IRQn EXTI3_IRQn
#define DECREASE_Pin GPIO_PIN_4
#define DECREASE_GPIO_Port GPIOB
#define DECREASE_EXTI_IRQn EXTI4_IRQn
#define CHANGE_MODE_Pin GPIO_PIN_5
#define CHANGE_MODE_GPIO_Port GPIOB
#define CHANGE_MODE_EXTI_IRQn EXTI9_5_IRQn
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_7
#define LED2_GPIO_Port GPIOB
#define RUN_Pin GPIO_PIN_9
#define RUN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
