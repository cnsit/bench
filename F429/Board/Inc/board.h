#ifndef __BOARD_H__
#define __BOARD_H__

#include "fmc.h"
#include "../../CNSIT/Inc/LCD.h"
#include "../../CNSIT/Inc/COLOR.h"

extern LCDTypeDef lcd;
void board_init(uint32_t);
void board_demo(void);
void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command);
uint16_t STMPE811ReadID();
void STMPE811Start();
void STMPE811ClearTouchIT();
void STMPE811GetXY(__IO uint16_t *x, __IO uint16_t *y, uint16_t width, uint16_t height);
uint8_t STMPE811Read(uint8_t reg);

#endif
