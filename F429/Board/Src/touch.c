/*
 * touch.c
 *
 *  Created on: Feb 25, 2020
 *      Author: jonyzhu
 */


#include "../Inc/board.h"
#include "../Inc/touch.h"
#include "i2c.h"

#define I2CADDR 0x82
I2C_HandleTypeDef* DEVICE = &hi2c3;
#define IT_SOURCE (STMPE811_GIT_TOUCH | STMPE811_GIT_FTH |  STMPE811_GIT_FOV | STMPE811_GIT_FF)

uint16_t STMPE811ReadID(){
	uint8_t id[2];
	if(HAL_I2C_Mem_Read(DEVICE, I2CADDR, 0x00, I2C_MEMADD_SIZE_8BIT, id, 2, 100) == HAL_OK){
		return id[0]<<8|id[1];
	}
	return 0;
}
uint8_t STMPE811Read(uint8_t reg){
	uint8_t value = 0;
	HAL_I2C_Mem_Read(DEVICE, I2CADDR, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 100);
	return value;
}
void STMPE811Write(uint8_t reg, uint8_t value){
	HAL_I2C_Mem_Write(DEVICE, I2CADDR, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 100);
}
void STMPE811EnableIT(){
	/* Set the register */
	STMPE811Write(STMPE811_REG_INT_EN, IT_SOURCE);
	/* Write Back the Interrupt Control register */
	STMPE811Write(STMPE811_REG_INT_CTRL, STMPE811_GIT_EN);
}
void STMPE811DisableIT(){
	/* Set the register */
	STMPE811Write(STMPE811_REG_INT_EN, 0);
	/* Write Back the Interrupt Control register */
	STMPE811Write(STMPE811_REG_INT_CTRL, 0);
}
void STMPE811ClearIT()
{
	/* Write 1 to the bits that have to be cleared */
	STMPE811Write(STMPE811_REG_INT_STA, STMPE811_TS_IT);
}
void STMPE811Start()
{
	uint8_t mode;

	/* Get the current register value */
	mode = STMPE811Read(STMPE811_REG_SYS_CTRL2);

	/* Set the Functionalities to be Enabled */
	mode &= ~(STMPE811_IO_FCT);

	/* Write the new register value */
	STMPE811Write(STMPE811_REG_SYS_CTRL2, mode);

	/* Select TSC pins in TSC alternate mode */
	uint8_t tmp = 0;
	/* Get the current register value */
	tmp = STMPE811Read(STMPE811_REG_IO_AF);
	/* Enable the selected pins alternate function */
	tmp &= ~(uint8_t)STMPE811_TOUCH_IO_ALL;
	/* Write back the new register value */
	STMPE811Write(STMPE811_REG_IO_AF, tmp);

	/* Set the Functionalities to be Enabled */
	mode &= ~(STMPE811_TS_FCT | STMPE811_ADC_FCT);

	/* Set the new register value */
	STMPE811Write(STMPE811_REG_SYS_CTRL2, mode);

	/* Select Sample Time, bit number and ADC Reference */
	STMPE811Write(STMPE811_REG_ADC_CTRL1, 0x49);

	/* Wait for 2 ms */
	LL_mDelay(2);

	/* Select the ADC clock speed: 3.25 MHz */
	STMPE811Write(STMPE811_REG_ADC_CTRL2, 0x01);

	/* Select 2 nF filter capacitor */
	/* Configuration:
     - Touch average control    : 4 samples
     - Touch delay time         : 500 uS
     - Panel driver setting time: 500 uS
	 */
	STMPE811Write(STMPE811_REG_TSC_CFG, 0x9A);

	/* Configure the Touch FIFO threshold: single point reading */
	STMPE811Write(STMPE811_REG_FIFO_TH, 0x20);

	/* Clear the FIFO memory content. */
	STMPE811Write(STMPE811_REG_FIFO_STA, 0x01);

	/* Put the FIFO back into operation mode  */
	STMPE811Write(STMPE811_REG_FIFO_STA, 0x00);

	/* Set the range and accuracy pf the pressure measurement (Z) :
     - Fractional part :7
     - Whole part      :1
	 */
	STMPE811Write(STMPE811_REG_TSC_FRACT_XYZ, 0x01);

	/* Set the driving capability (limit) of the device for TSC pins: 50mA */
	STMPE811Write(STMPE811_REG_TSC_I_DRIVE, 0x01);

	/* Touch screen control configuration (enable TSC):
     - No window tracking index
     - XYZ acquisition mode
	 */
	STMPE811Write(STMPE811_REG_TSC_CTRL, 0x01);

	/*  Clear all the status pending bits if any */
	STMPE811Write(STMPE811_REG_INT_STA, 0xFF);

	STMPE811DisableIT();
	/* Wait for 2 ms delay */
	LL_mDelay(2);
}
void STMPE811CoordTrans(__IO uint16_t *x, __IO uint16_t *y, uint16_t width, uint16_t height, uint16_t x_raw, uint16_t y_raw){
	/* Y value first correction */
	y_raw -= 360;

	/* Y value second correction */
	uint16_t yr = y_raw / 11;

	/* Return y position value */
	if(yr <= 0)
	{
		yr = 0;
	}
	else if (yr > height)
	{
		yr = height - 1;
	}
	else
	{}
	*y = height - yr;

	/* X value first correction */
	if(x_raw <= 3000)
	{
		x_raw = 3870 - x_raw;
	}
	else
	{
		x_raw = 3800 - x_raw;
	}

	/* X value second correction */
	uint16_t xr = x_raw / 15;

	/* Return X position value */
	if(xr <= 0)
	{
		xr = 0;
	}
	else if (xr > width)
	{
		xr = width - 1;
	}
	else
	{}
	*x = xr;
}
void STMPE811GetXY(__IO uint16_t *x, __IO uint16_t *y, uint16_t width, uint16_t height){
	//if(!(STMPE811Read(0x0b)&(STMPE811_GIT_FE|STMPE811_GIT_TOUCH))){
	//STMPE811DisableIT();
	while(!(STMPE811Read(STMPE811_REG_FIFO_STA)&0x20)){
		uint8_t dataXYZ[4];//h5e444034e58d7
		if(HAL_I2C_Mem_Read(DEVICE, I2CADDR, STMPE811_REG_TSC_DATA_NON_INC, I2C_MEMADD_SIZE_8BIT, dataXYZ, 4, 100) == HAL_OK){
			uint16_t x_raw = (dataXYZ[0]<<4)|((dataXYZ[1]&0xf0)>>4);
			uint16_t y_raw = ((dataXYZ[1]&0x0f)<<8)|dataXYZ[2];
			//STMPE811CoordTrans(x, y, width, height, x_raw, y_raw);

			if(STMPE811Read(STMPE811_REG_INT_STA)&STMPE811_GIT_TOUCH){
				*x = x_raw;
				*y = y_raw;
			}
		}
	}
	/* Reset FIFO */
	//STMPE811Write(STMPE811_REG_FIFO_STA, 0x01);
	/* Enable the FIFO again */
	//STMPE811Write(STMPE811_REG_FIFO_STA, 0x00);
	//}
	STMPE811ClearIT();
	//STMPE811EnableIT();
}
