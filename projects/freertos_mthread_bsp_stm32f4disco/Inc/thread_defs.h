/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : thread_defs.h
  * @brief          : Header
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __THREAD_DEFS_H
#define __THREAD_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cmsis_os2.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "semphr.h"
#include "stm32f4xx_hal.h"
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

void SINGLELED_Task(void *argument);
void GROUPLED_Task(void *argument);
void ButtonRead_Task(void *argument);
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
extern const osThreadAttr_t singleLedTask_attributes;
extern const osThreadAttr_t groupLedTask_attributes;
extern const osThreadAttr_t buttonReadTask_attributes;

extern osSemaphoreId_t xSemaButtonStateChanged;

extern UART_HandleTypeDef huart2;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __THREAD_DEFS_H */

/************************ (C) COPYRIGHT *****END OF FILE****/
