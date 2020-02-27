/**
  ******************************************************************************
  * File Name          : DMA2D.c
  * Description        : This file provides code for the configuration
  *                      of the DMA2D instances.
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

/* Includes ------------------------------------------------------------------*/
#include "dma2d.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* DMA2D init function */
void MX_DMA2D_Init(void)
{

  /* Peripheral clock enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2D);

  /* DMA2D interrupt Init */
  NVIC_SetPriority(DMA2D_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5, 0));
  NVIC_EnableIRQ(DMA2D_IRQn);

  LL_DMA2D_SetMode(DMA2D, LL_DMA2D_MODE_M2M);
  LL_DMA2D_SetOutputColorMode(DMA2D, LL_DMA2D_OUTPUT_MODE_ARGB8888);
  LL_DMA2D_SetLineOffset(DMA2D, 0);
  LL_DMA2D_FGND_SetColorMode(DMA2D, LL_DMA2D_INPUT_MODE_ARGB8888);
  LL_DMA2D_FGND_SetAlphaMode(DMA2D, LL_DMA2D_ALPHA_MODE_NO_MODIF);
  LL_DMA2D_FGND_SetAlpha(DMA2D, 0);
  LL_DMA2D_FGND_SetLineOffset(DMA2D, 0);

}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
