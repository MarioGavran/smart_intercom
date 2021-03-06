/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#define MCP73831_STAT_Pin GPIO_PIN_2
#define MCP73831_STAT_GPIO_Port GPIOE
#define MCP73831_PROG_Pin GPIO_PIN_3
#define MCP73831_PROG_GPIO_Port GPIOE
#define OV7670_D0_Pin GPIO_PIN_0
#define OV7670_D0_GPIO_Port GPIOF
#define OV7670_D1_Pin GPIO_PIN_1
#define OV7670_D1_GPIO_Port GPIOF
#define OV7670_D2_Pin GPIO_PIN_2
#define OV7670_D2_GPIO_Port GPIOF
#define OV7670_D3_Pin GPIO_PIN_3
#define OV7670_D3_GPIO_Port GPIOF
#define OV7670_D4_Pin GPIO_PIN_4
#define OV7670_D4_GPIO_Port GPIOF
#define OV7670_D5_Pin GPIO_PIN_5
#define OV7670_D5_GPIO_Port GPIOF
#define OV7670_D6_Pin GPIO_PIN_6
#define OV7670_D6_GPIO_Port GPIOF
#define OV7670_D7_Pin GPIO_PIN_7
#define OV7670_D7_GPIO_Port GPIOF
#define OV7670_PWDN_Pin GPIO_PIN_0
#define OV7670_PWDN_GPIO_Port GPIOC
#define OV7670_NRST_Pin GPIO_PIN_1
#define OV7670_NRST_GPIO_Port GPIOC
#define MIC5357_2V8_EN_Pin GPIO_PIN_2
#define MIC5357_2V8_EN_GPIO_Port GPIOC
#define USER_LED_Pin GPIO_PIN_1
#define USER_LED_GPIO_Port GPIOA
#define TOUCH_XR_Pin GPIO_PIN_2
#define TOUCH_XR_GPIO_Port GPIOA
#define TOUCH_YU_Pin GPIO_PIN_3
#define TOUCH_YU_GPIO_Port GPIOA
#define TOUCH_YU_EXTI_IRQn EXTI3_IRQn
#define TOUCH_YD_Pin GPIO_PIN_4
#define TOUCH_YD_GPIO_Port GPIOA
#define TOUCH_XL_Pin GPIO_PIN_5
#define TOUCH_XL_GPIO_Port GPIOA
#define BOOT0_EN_Pin GPIO_PIN_1
#define BOOT0_EN_GPIO_Port GPIOB
#define OV7670_HREF_Pin GPIO_PIN_0
#define OV7670_HREF_GPIO_Port GPIOG
#define OV7670_HREF_EXTI_IRQn EXTI0_IRQn
#define OV7670_VSYNC_Pin GPIO_PIN_1
#define OV7670_VSYNC_GPIO_Port GPIOG
#define OV7670_VSYNC_EXTI_IRQn EXTI1_IRQn
#define FSMC_NRST_Pin GPIO_PIN_6
#define FSMC_NRST_GPIO_Port GPIOC
#define LCD_BL_PWM_Pin GPIO_PIN_7
#define LCD_BL_PWM_GPIO_Port GPIOC
#define OV7670_XCLK_Pin GPIO_PIN_9
#define OV7670_XCLK_GPIO_Port GPIOC
#define OV7670_PCLK_Pin GPIO_PIN_9
#define OV7670_PCLK_GPIO_Port GPIOA
#define PB5_GPIO_Pin GPIO_PIN_5
#define PB5_GPIO_GPIO_Port GPIOB
#define OV7670_SIOC_Pin GPIO_PIN_8
#define OV7670_SIOC_GPIO_Port GPIOB
#define OV7670_SIOD_Pin GPIO_PIN_9
#define OV7670_SIOD_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define TOUCH_YU_ADC_CHANNEL ADC_CHANNEL_3
#define TOUCH_XR_ADC_CHANNEL ADC_CHANNEL_2
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
