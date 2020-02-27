/*
 * GRAPHICS.h
 *
 *  Created on: Feb 23, 2020
 *      Author: jonyzhu
 */

#ifndef __CNSIT_GRAPHICS_H__
#define __CNSIT_GRAPHICS_H__

#include <stdint.h>
#include "../Inc/LCD.h"
#include "../Inc/FONT.h"

void Line(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color, LCDTypeDef* lcd);
uint16_t Char(uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, char v, LCDTypeDef *lcd, const CNSITFontDescTypeDef *font );
uint16_t String(uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, char* v, LCDTypeDef *lcd, const CNSITFontDescTypeDef *font );

#endif
