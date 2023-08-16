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

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern CAN_TxHeaderTypeDef txHeader;
extern uint8_t txData[8];
extern uint32_t txMailbox;
extern CAN_RxHeaderTypeDef rxHeader;
extern CAN_FilterTypeDef  sFilterConfig; // Rx filtering config
extern uint8_t rxData[8];
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
#define TIM10_PIN_Pin GPIO_PIN_6
#define TIM10_PIN_GPIO_Port GPIOF
#define CS_PIN_Pin GPIO_PIN_1
#define CS_PIN_GPIO_Port GPIOC
#define LCD_CSX_Pin GPIO_PIN_2
#define LCD_CSX_GPIO_Port GPIOC
#define TIM1_PIN_Pin GPIO_PIN_9
#define TIM1_PIN_GPIO_Port GPIOE
#define LCD_RDX_Pin GPIO_PIN_12
#define LCD_RDX_GPIO_Port GPIOD
#define LCD_WRX_Pin GPIO_PIN_13
#define LCD_WRX_GPIO_Port GPIOD
#define SDA_Pin GPIO_PIN_9
#define SDA_GPIO_Port GPIOC
#define SCL_Pin GPIO_PIN_8
#define SCL_GPIO_Port GPIOA
#define LD3_Pin GPIO_PIN_13
#define LD3_GPIO_Port GPIOG
#define LD4_Pin GPIO_PIN_14
#define LD4_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
