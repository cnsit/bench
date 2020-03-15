/*
 * dac.c
 *
 *  Created on: Mar 7, 2020
 *      Author: jonyzhu
 */

function dac_init(){
	//DAC config
	LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_6, sin_1_len);
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_6, (uint32_t)(&sin_1[0]));
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_STREAM_6, LL_DAC_DMA_GetRegAddr(DAC, LL_DAC_CHANNEL_2, LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED));
	LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_6);

	LL_DAC_EnableDMAReq(DAC, LL_DAC_CHANNEL_2);
	LL_DAC_EnableTrigger(DAC, LL_DAC_CHANNEL_2);
	LL_DAC_Enable(DAC, LL_DAC_CHANNEL_2);
	LL_TIM_EnableCounter(TIM7);

}
