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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "tim.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../Board/Inc/board.h"
#include "../../CNSIT/Inc/GRAPHICS.h"
#include "../../CNSIT/Inc/DS18B20.h"
#include "../../CNSIT/Font/FONT_FIRACODE_24PT.h"
#include "../../CNSIT/Font/FONT_OCR_A_24PT.h"
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
__IO uint32_t freq_count;
__IO float temperature;
/* USER CODE END Variables */
osThreadId tskIdelHandle;
osThreadId tskDisplayHandle;
osThreadId tskTemperatureHandle;
osMessageQId queFrameHandle;
osMessageQId queFreqCountHandle;
osTimerId timKeyDownHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void fnIdel(void const * argument);
void fnDisplay(void const * argument);
void fnTemperature(void const * argument);
void cbKeyDown(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
__weak void vApplicationMallocFailedHook(void)
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];
  
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )  
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}                   
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of timKeyDown */
  osTimerDef(timKeyDown, cbKeyDown);
  timKeyDownHandle = osTimerCreate(osTimer(timKeyDown), osTimerOnce, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of queFrame */
  osMessageQDef(queFrame, 1, uint16_t);
  queFrameHandle = osMessageCreate(osMessageQ(queFrame), NULL);

  /* definition and creation of queFreqCount */
  osMessageQDef(queFreqCount, 1, uint32_t);
  queFreqCountHandle = osMessageCreate(osMessageQ(queFreqCount), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of tskIdel */
  osThreadDef(tskIdel, fnIdel, osPriorityLow, 0, 128);
  tskIdelHandle = osThreadCreate(osThread(tskIdel), NULL);

  /* definition and creation of tskDisplay */
  osThreadDef(tskDisplay, fnDisplay, osPriorityNormal, 0, 1024);
  tskDisplayHandle = osThreadCreate(osThread(tskDisplay), NULL);

  /* definition and creation of tskTemperature */
  osThreadDef(tskTemperature, fnTemperature, osPriorityLow, 0, 128);
  tskTemperatureHandle = osThreadCreate(osThread(tskTemperature), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_fnIdel */
/**
  * @brief  Function implementing the tskIdel thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_fnIdel */
void fnIdel(void const * argument)
{
  /* USER CODE BEGIN fnIdel */
	uint8_t idle_count = 0;
	/* Infinite loop */
	for(;;)
	{
		osDelay(250);
		LL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		idle_count ++;
	}
  /* USER CODE END fnIdel */
}

/* USER CODE BEGIN Header_fnDisplay */
/**
* @brief Function implementing the tskDisplay thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_fnDisplay */
void fnDisplay(void const * argument)
{
  /* USER CODE BEGIN fnDisplay */
	lcd.Fill(0, 0, lcd.GetWidth(), lcd.GetHeight(), 0x0000);
	srand(HAL_GetTick());
	char msg[32];
	uint16_t id = read_id();
	sprintf(msg, "0x%04X", id);
	String(0,80, RGB(0xff,0xff,0x00), RGB(0x00,0x00,0x00), msg, &lcd, &oCRAExtended_24ptDesc);
	LL_TIM_EnableIT_UPDATE(TIM4);
	LL_TIM_EnableCounter(TIM4);
	LL_TIM_EnableIT_UPDATE(TIM5);
	LL_TIM_EnableCounter(TIM5);
	LL_TIM_EnableExternalClock(TIM2);
	LL_TIM_EnableCounter(TIM2);
	/* Infinite loop */
	for(;;)
	{
		osEvent e = osMessageGet(queFrameHandle, 500);
		if(e.status == osEventMessage){
			//board_demo();
			sprintf(msg, "%ld", freq_count);
			String(0,0, RGB(0xff,0xff,0x00), 0x0000, msg, &lcd, &firaCode_24ptDesc);
			if(temperature>=0){
				sprintf(msg, "+%6.3f", temperature);
			}else{
				sprintf(msg, "%7.3f", temperature);
			}
			String(0,40, RGB(0xff,0xff,0x00), 0x0000, msg, &lcd, &firaCode_24ptDesc);
			LL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
		}
	}
  /* USER CODE END fnDisplay */
}

/* USER CODE BEGIN Header_fnTemperature */
/**
* @brief Function implementing the tskTemperature thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_fnTemperature */
void fnTemperature(void const * argument)
{
  /* USER CODE BEGIN fnTemperature */
  /* Infinite loop */
  for(;;)
  {
    osDelay(450);
    temperature = DS18B20Convert(DS18B20_GPIO_Port,DS18B20_Pin);
  }
  /* USER CODE END fnTemperature */
}

/* cbKeyDown function */
void cbKeyDown(void const * argument)
{
  /* USER CODE BEGIN cbKeyDown */
  
  /* USER CODE END cbKeyDown */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
