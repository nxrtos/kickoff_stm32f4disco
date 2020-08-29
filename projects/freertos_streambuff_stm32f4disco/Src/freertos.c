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
#include "bsp.h"
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
  BSP_LED_Init(LED4);
  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
    BSP_LED_Toggle(LED4);
  }
}

void GROUPLED_Task(void *argument)
{
  //BSP_LED_Init(LED3);
  BSP_LED_Init(LED5);
  BSP_LED_Init(LED6);
  /* Infinite loop */
  for(;;)
  {
    osDelay(400);
    //BSP_LED_Toggle(LED3);
    BSP_LED_Toggle(LED5);
    BSP_LED_Toggle(LED6);
  }
}

const osThreadAttr_t buttonReadTask_attributes = {
                 .name = "buttonReadTask",
                 .priority = (osPriority_t) osPriorityNormal,
                 .stack_size = 128 * 4
};

StaticSemaphore_t	xSemaButton_cb_mem;

osSemaphoreId_t xSemaButtonStateChanged;

osSemaphoreAttr_t  xSemaButtonStateChanged_attribute = {
                .name = "semaButtonStateChanged",
                .cb_mem = &xSemaButton_cb_mem,    ///< memory for control block
                .cb_size = sizeof(StaticSemaphore_t),   ///< size of provided memory for control block
};

void ButtonRead_Task(void *argument)
{
  char buff[10] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', ' '};
  xSemaButtonStateChanged = osSemaphoreNew (1, 0 , &xSemaButtonStateChanged_attribute);
  uint32_t BSP_PB1_State = 0xffff;

  if( xSemaButtonStateChanged != NULL )
  {	//BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
    /* EXTI interrupt init*/
    // the preemption priority for EXTI0_IRQn has to be above or equal to
    // configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY in order to invoke syscall
    // from EXTI0_ISR
    HAL_NVIC_SetPriority(EXTI0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY +1, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
  }

  for(;;)
  {
    if( osSemaphoreAcquire( xSemaButtonStateChanged, 8000 ) == osOK )
    {
      uint32_t tCount = osKernelGetTickCount();
      uint32_t BSP_PB_Read = BSP_PB_GetState(BUTTON_KEY);

      if(BSP_PB1_State == BSP_PB_Read)
	  {
        osDelay(10);
        HAL_NVIC_EnableIRQ(EXTI0_IRQn);
      }
      else
      {
    	HAL_UART_StateTypeDef  uart2_state;

        BSP_PB1_State = BSP_PB_Read;
        sprintf ( buff, "%8ld", tCount);
        do
        {
          uart2_state = HAL_UART_GetState(&huart2);
          osDelay(10);
        } while( HAL_UART_STATE_BUSY_TX == uart2_state ||
        		HAL_UART_STATE_BUSY == uart2_state) ;
        HAL_UART_Transmit_IT(&huart2, (uint8_t *)buff, 10);
        BSP_LED_Toggle(LED3);
        osDelay(10);
        HAL_NVIC_EnableIRQ(EXTI0_IRQn);
        //osDelay(100);
        do
        {
          osDelay(10);
          uart2_state = HAL_UART_GetState(&huart2);
        } while( HAL_UART_STATE_BUSY_TX == uart2_state ||
        		HAL_UART_STATE_BUSY == uart2_state) ;
        if(BSP_PB1_State)
        {
          HAL_UART_Transmit_IT(&huart2, (uint8_t *)"button state high\n\r", sizeof("button state high\n\r"));
        }
        else
        {
          HAL_UART_Transmit_IT(&huart2, (uint8_t *)"button state low\n\r", sizeof("button state low\n\r"));
        }
      }
    }
    else
    {
      // timeout to acquire xSema
      HAL_UART_Transmit_IT(&huart2, (uint8_t *)"time expired to wait for button\r\n", sizeof("time expired to wait for button\r\n"));
    }
  }
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
