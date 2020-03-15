/*
 * color.c
 *
 *  Created on: Feb 23, 2020
 *      Author: jonyzhu
 */

#include "../Inc/COLOR.h"

uint16_t RGB(uint8_t r, uint8_t g, uint8_t b){
	return (r>>3)<<11 | (g>>2)<<5 | b>>3;
}
