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
	STMPE811Write(STMPE811_REG_FIFO_TH, 0x01);

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

	  /* Read the Interrupt Control register  */
	  tmp = STMPE811Read(STMPE811_REG_INT_CTRL);
	  /* Set the global interrupts to be Enabled */
	  tmp |= (uint8_t)STMPE811_GIT_EN;
	  /* Write Back the Interrupt Control register */
	  STMPE811Write(STMPE811_REG_INT_CTRL, tmp);
	  tmp = STMPE811Read(STMPE811_REG_INT_EN);
	    /* Set the interrupts to be Enabled */
	    tmp |=STMPE811_GIT_TOUCH ;
	    /* Set the register */
	    STMPE811Write(STMPE811_REG_INT_EN, tmp);

	/* Wait for 2 ms delay */
	LL_mDelay(2);
}
void STMPE811ClearTouchIT()
{
  /* Write 1 to the bits that have to be cleared */
  STMPE811Write(STMPE811_REG_INT_STA, STMPE811_GIT_TOUCH);
}
void STMPE811GetXY(uint16_t *x, uint16_t *y){
	uint8_t dataXYZ[4];//h5e444034e58d7
	if(HAL_I2C_Mem_Read(DEVICE, I2CADDR, STMPE811_REG_TSC_DATA_NON_INC, I2C_MEMADD_SIZE_8BIT, dataXYZ, 4, 100) == HAL_OK){
		  *x= dataXYZ[0]<<4|(dataXYZ[1]>>4);
		  *y= dataXYZ[1]&0x0f|dataXYZ[2];
	}
}
