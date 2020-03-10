/*
 * adc.c
 *
 *  Created on: Mar 7, 2020
 *      Author: jonyzhu
 */

function adc_init(){
	//ADC config
	LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_0, adc_data_len);
	LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_0, (uint32_t)(&adc_data[0]));
	LL_DMA_ConfigAddresses(DMA2,LL_DMA_CHANNEL_0,LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA),(uint32_t)&adc_data[0],LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	LL_DMA_EnableIT_TC(DMA2, LL_DMA_STREAM_0);
	LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_0);
}
function adc_start(){
	LL_ADC_Enable(ADC1);

	LL_TIM_EnableCounter(TIM8);
	HAL_TIM_OC_Start(&htim8, TIM_CHANNEL_3);
}
