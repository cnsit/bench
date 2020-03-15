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
//#include "../../CNSIT/Font/FONT_ENHANCED_DOT_DIGITAL_16PT.h"
//const CNSITFontDescTypeDef* font = &enhancedDotDigital7_16ptDesc;
#include "../../CNSIT/Font/FONT_APPLE_][_12PT.h"
const CNSITFontDescTypeDef* font = &apple_12ptDesc;
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
/* USER CODE END Variables */
osThreadId tskIdelHandle;
osThreadId tskDisplayHandle;
osThreadId tskTemperatureHandle;
osThreadId tskTouchHandle;
osThreadId tskDACHandle;
osThreadId tskFFTHandle;
osMessageQId queFrameHandle;
osMessageQId queFreqCountHandle;
osMessageQId queTouchHandle;
osMessageQId queInfoHandle;
osTimerId timKeyDownHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void fnIdel(void const * argument);
void fnDisplay(void const * argument);
void fnTemperature(void const * argument);
void fnTouch(void const * argument);
void fnDAC(void const * argument);
void fnFFT(void const * argument);
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

	/* definition and creation of queTouch */
	osMessageQDef(queTouch, 1, uint16_t);
	queTouchHandle = osMessageCreate(osMessageQ(queTouch), NULL);

	/* definition and creation of queInfo */
	osMessageQDef(queInfo, 16, uint32_t);
	queInfoHandle = osMessageCreate(osMessageQ(queInfo), NULL);

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of tskIdel */
	osThreadDef(tskIdel, fnIdel, osPriorityLow, 0, 128);
	tskIdelHandle = osThreadCreate(osThread(tskIdel), NULL);

	/* definition and creation of tskDisplay */
	osThreadDef(tskDisplay, fnDisplay, osPriorityAboveNormal, 0, 1024);
	tskDisplayHandle = osThreadCreate(osThread(tskDisplay), NULL);

	/* definition and creation of tskTemperature */
	osThreadDef(tskTemperature, fnTemperature, osPriorityLow, 0, 128);
	tskTemperatureHandle = osThreadCreate(osThread(tskTemperature), NULL);

	/* definition and creation of tskTouch */
	osThreadDef(tskTouch, fnTouch, osPriorityNormal, 0, 128);
	tskTouchHandle = osThreadCreate(osThread(tskTouch), NULL);

	/* definition and creation of tskDAC */
	osThreadDef(tskDAC, fnDAC, osPriorityBelowNormal, 0, 256);
	tskDACHandle = osThreadCreate(osThread(tskDAC), NULL);

	/* definition and creation of tskFFT */
	osThreadDef(tskFFT, fnFFT, osPriorityHigh, 0, 4096);
	tskFFTHandle = osThreadCreate(osThread(tskFFT), NULL);

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
	char msg[32];
	uint16_t bg = BLACK, fg = YELLOW;
	lcd.Fill(0, 0, lcd.GetWidth(), lcd.GetHeight(), bg);

	STMPE811Start();
	LL_TIM_EnableIT_UPDATE(TIM10);
	LL_TIM_EnableCounter(TIM10);

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

			e = osMessageGet(queInfoHandle,0);
			while(e.status == osEventMessage){
				INFO* info = (INFO*)e.value.p;
				uint16_t x,y;
				if(info->src == TOUCH){
					x = 0;
					y = font->Height;

					sprintf(msg, "%s:%5d", info->data[0].label, *(uint16_t*)info->data[0].value.p);
					x = String(x, y, YELLOW, bg, msg, &lcd, font);
					sprintf(msg, "%s:%5d", info->data[1].label, *(uint16_t*)info->data[1].value.p);
					String(x+20, y, YELLOW, bg, msg, &lcd, font);

					x = 0; y = 0;
					sprintf(msg, "%s:%2x", info->data[3].label, *(uint8_t*)info->data[3].value.p);
					x= String(x, y, fg, bg, msg, &lcd, font);
					sprintf(msg, "%s:%2x", info->data[2].label, *(uint8_t*)info->data[2].value.p);
					String(x + 20, y, fg, bg, msg, &lcd, font);
				}else if(info->src == TEMP){
					float temperature = *(float*)info->data[0].value.p;
					if(temperature>=0){
						sprintf(msg, "%s:+%6.3f'C", info->data[0].label, temperature);
					}else{
						sprintf(msg, "%s:%7.3f'C", info->data[0].label, temperature);
					}
					x = 0;
					y = font->Height<<1;
					String(x, y , RED, bg, msg, &lcd, font);
				}else if(info->src==FC){
					x = 0;
					y = font->Height*3;
					sprintf(msg, "%s:%ld", info->data[0].label, info->data[0].value.v);
					String(x,y, GREEN, bg, msg, &lcd, font);
				}
				e = osMessageGet(queInfoHandle,0);
			}
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
	float temperature;
	DATUM data[1] = {
		{"Temp", {.p = (float*)&temperature}}
	};
	INFO info = {
		TEMP,
		data
	};
	/* Infinite loop */
	for(;;)
	{
		osDelay(450);
		temperature = DS18B20Convert(DS18B20_GPIO_Port,DS18B20_Pin);
		osMessagePut(queInfoHandle, (uint32_t)&info, 0);
	}
	/* USER CODE END fnTemperature */
}

/* USER CODE BEGIN Header_fnTouch */
/**
 * @brief Function implementing the tskTouch thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_fnTouch */
void fnTouch(void const * argument)
{
	/* USER CODE BEGIN fnTouch */
	uint16_t touch_x=0, touch_y=0;
	uint8_t touch_int, touch_fifo;
	DATUM data[4] = {
		{"X", {.p=(uint32_t*)&touch_x}},
		{"Y", {.p =(uint32_t*)&touch_y}},
		{"INT", {.p=(uint32_t*)&touch_int}},
		{"FIFO", {.p=(uint32_t*)&touch_fifo}}
	};
	INFO info = {
		TOUCH,
		data
	};
	/* Infinite loop */
	for(;;)
	{
		osEvent e = osMessageGet(queTouchHandle, 700);
		if(e.status == osEventMessage){
			touch_int = STMPE811Read(0x0b);
			touch_fifo = STMPE811Read(0x4b);
			osMessagePut(queInfoHandle, (uint32_t)&info, 0);
			STMPE811GetXY(&touch_x, &touch_y, lcd.GetWidth(), lcd.GetHeight());
		}
	}
	/* USER CODE END fnTouch */
}

/* USER CODE BEGIN Header_fnDAC */
/**
 * @brief Function implementing the tskDAC thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_fnDAC */
void fnDAC(void const * argument)
{
	/* USER CODE BEGIN fnDAC */
	/* Infinite loop */
	for(;;)
	{
		osDelay(1000);
	}
	/* USER CODE END fnDAC */
}

/* USER CODE BEGIN Header_fnFFT */
/**
 * @brief Function implementing the tskFFT thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_fnFFT */
void fnFFT(void const * argument)
{
	/* USER CODE BEGIN fnFFT */
	/* Infinite loop */
	for(;;)
	{
		osDelay(1000);
	}
	/* USER CODE END fnFFT */
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
