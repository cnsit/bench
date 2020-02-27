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
void STMPE811GetXY(uint16_t *x, uint16_t *y);

#endif
