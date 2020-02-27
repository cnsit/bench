#ifndef __BOARD_H__
#define __BOARD_H__

#include "fmc.h"
#include "../../CNSIT/Inc/LCD.h"
#include "../../CNSIT/Inc/COLOR.h"

extern LCDTypeDef lcd;
void board_init(uint32_t);
void board_demo(void);
void SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command);
uint16_t read_id();

#endif
