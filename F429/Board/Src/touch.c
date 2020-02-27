/*
 * touch.c
 *
 *  Created on: Feb 25, 2020
 *      Author: jonyzhu
 */


#include "../Inc/board.h"
#include "i2c.h"

#define DEVICE 0x82
uint16_t read_id(){
	uint8_t id[2];
	if(HAL_I2C_Mem_Read(&hi2c3, DEVICE, 0x00, I2C_MEMADD_SIZE_8BIT, id, 2, 100) == HAL_OK){
		return id[0]<<8|id[1];
	}
	return 0;
}
