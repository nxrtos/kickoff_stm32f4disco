/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "thread_defs.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

const osThreadAttr_t singleLedTask_attributes = {
                 .name = "singleLedTask",
                 .priority = (osPriority_t) osPriorityNormal,
                 .stack_size = 128 * 4
};
const osThreadAttr_t groupLedTask_attributes = {
                 .name = "groupLedTask",
                 .priority = (osPriority_t) osPriorityNormal,
                 .stack_size = 128 * 4
};

/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void SINGLELED_Task(void *argument)
{
	  HAL_GPIO_WritePin(GPIOD, LD4_Pin, GPIO_PIN_SET);
	  /* Infinite loop */
	  for(;;)
	  {
	    osDelay(100);
	    HAL_GPIO_TogglePin(GPIOD, LD4_Pin);
	  }

}
void GROUPLED_Task(void *argument)
{
	  HAL_GPIO_WritePin(GPIOD, LD3_Pin|LD6_Pin, GPIO_PIN_SET);
	  /* Infinite loop */
	  for(;;)
	  {
	    osDelay(400);
	    HAL_GPIO_TogglePin(GPIOD, LD5_Pin|LD6_Pin);
	    HAL_GPIO_TogglePin(GPIOD, LD3_Pin);
	  }
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
