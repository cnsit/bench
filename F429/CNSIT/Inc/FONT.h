/*
 * FONT.h
 *
 *  Created on: Feb 24, 2020
 *      Author: jonyzhu
 */

#ifndef __CNSIT_FONT_H__
#define __CNSIT_FONT_H__

#include <stdint.h>

typedef struct {
	const uint8_t Width;
	const uint8_t Height;
	const uint16_t Index;
} CNSITFontIndexMapTypeDef;

typedef struct {
	const uint8_t Height;
	const uint16_t Start;
	const uint16_t End;
	const CNSITFontIndexMapTypeDef* IndexMap;
	const uint8_t* Data;
} CNSITFontDescTypeDef ;
#endif
