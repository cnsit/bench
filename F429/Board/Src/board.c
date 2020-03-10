/*
 * board.c
 *
 *  Created on: Feb 23, 2020
 *      Author: jonyzhu
 */

#include "../Inc/board.h"
#include "../../CNSIT/Inc/GRAPHICS.h"
#include "tim.h"
uint16_t YELLOW, BLACK, RED, BLUE, GREEN, WHITE;

void board_init(uint32_t lcd_buffer_addr){
	LL_GPIO_SetOutputPin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin);
	LL_GPIO_SetOutputPin(ENABLE_GPIO_Port, ENABLE_Pin);
	LL_SPI_Enable(SPI5);
	lcd.Init(lcd_buffer_addr);
	YELLOW = RGB(0xff,0xff,0x00);
	RED = RGB(0xff,0x00,0x00);
	BLUE = RGB(0x00,0x00,0xff);
	GREEN = RGB(0x00,0xff,0x00);
	BLACK = 0;
	WHITE = 0xff;
}

void board_demo(void){
	uint16_t w = HAL_GetTick() % 80;
	uint16_t h = HAL_GetTick() % 120;
	uint16_t x = HAL_GetTick() % (lcd.GetWidth() - w + 1);
	uint16_t y = HAL_GetTick() % (lcd.GetHeight() - h + 1);
	lcd.Fill(x, y, x+w, y+h, RGB(HAL_GetTick() % 0xf0, HAL_GetTick() % 0x6f,HAL_GetTick() % 0x22));
}
