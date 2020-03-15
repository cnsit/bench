/*
 * DS18B20.c
 *
 *  Created on: Feb 26, 2020
 *      Author: jonyzhu
 */
#include "gpio.h"
#include "cmsis_os.h"

static void nop(uint16_t count){
	for(uint16_t i=0;i<count;i++){
		for(uint8_t j=0;j<13;j++){ //5 count takes 0.8us @72MHz sysclk
			__ASM ("nop");
		}
	}
}
static void output(GPIO_TypeDef* gpio, uint32_t pin){
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	LL_GPIO_Init(gpio, &GPIO_InitStruct);
}
static void input(GPIO_TypeDef* gpio, uint32_t pin){
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	LL_GPIO_Init(gpio, &GPIO_InitStruct);
}
static uint8_t reset(GPIO_TypeDef* gpio, uint32_t pin){
	LL_GPIO_ResetOutputPin(gpio, pin);
	nop(650);
	input(gpio, pin);
	nop(125);
	uint8_t r = (LL_GPIO_IsInputPinSet(gpio, pin)==0);
	nop(500);
	return r;
}
static void write(GPIO_TypeDef* gpio, uint32_t pin, uint8_t v){
	output(gpio, pin);
	for(uint8_t i=0;i<8;i++){
		if(v&0x01){
			LL_GPIO_ResetOutputPin(gpio, pin);
			nop(3);
			LL_GPIO_SetOutputPin(gpio, pin);
			nop(100);
		}else{
			LL_GPIO_ResetOutputPin(gpio, pin);
			nop(100);
			LL_GPIO_SetOutputPin(gpio, pin);
			nop(3);
		}
		v>>=1;
	}
}
static uint8_t read(GPIO_TypeDef* gpio, uint32_t pin){
	uint8_t v=0x00;
	for(uint8_t i=0;i<8;i++){
		output(gpio, pin);
		LL_GPIO_ResetOutputPin(gpio, pin);
		nop(2);
		input(gpio, pin);
		nop(8);
		if(LL_GPIO_IsInputPinSet(gpio, pin)){
			v|=0x80;
		}
		if(i!=7){
			v>>=1;
		}
		nop(80);
		output(gpio, pin);
		LL_GPIO_SetOutputPin(gpio, pin);
		nop(3);
	}
	return v;
}
float DS18B20Convert(GPIO_TypeDef* gpio, uint32_t pin){
	uint8_t r = reset(gpio, pin);
	float temp_float = 0;
	if(r>0){
		uint8_t rom[8], data[10];
		write(gpio, pin, 0x33);
		for(int8_t i=7; i>=0; i--){
			rom[i] = read(gpio, pin);
		}
		write(gpio, pin, 0x44);
		osDelay(1000);
		reset(gpio, pin);
		write(gpio, pin, 0xcc);
		write(gpio, pin, 0xbe);
		for(uint8_t i=0; i<9; i++){
			data[i] = read(gpio, pin);
		}
		uint8_t sign = data[1]&0xf8;
		uint16_t temp_data = (data[1]&0x07)<<8 | data[0];
		temp_float = temp_data * 0.0625;
		if(sign)temp_float=0-temp_float;
	}else{
		output(gpio, pin);
	}
	return temp_float;
}
