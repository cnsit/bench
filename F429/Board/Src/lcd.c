/*
 * lcd.c
 *
 *  Created on: Feb 22, 2020
 *      Author: jonyzhu
 */

/* Includes ------------------------------------------------------------------*/
#include "../Inc/board.h"
#include "../Inc/lcd.h"
#include "../../CNSIT/Inc/LCD.h"
#include "../../CNSIT/Inc/Graphics.h"
#include "spi.h"

static uint32_t buffer_addr;
/**
  * @brief  Writes register value.
  */
void LCD_IO_WriteData(uint16_t RegValue)
{
  /* Set WRX to send data */
  LCD_WRX_HIGH();

  /* Reset LCD control line(/CS) and Send data */
  LCD_CS_LOW();
  while(!LL_SPI_IsActiveFlag_TXE(SPI5)){}
  LL_SPI_TransmitData16(SPI5, RegValue);
  while(LL_SPI_IsActiveFlag_BSY(SPI5)){}

  /* Deselect: Chip Select high */
  LCD_CS_HIGH();
}

/**
  * @brief  Writes register address.
  */
void LCD_IO_WriteReg(uint8_t Reg)
{
  /* Reset WRX to send command */
  LCD_WRX_LOW();

  /* Reset LCD control line(/CS) and Send command */
  LCD_CS_LOW();
  while(!LL_SPI_IsActiveFlag_TXE(SPI5)){}
  LL_SPI_TransmitData8(SPI5, Reg);
  while(LL_SPI_IsActiveFlag_BSY(SPI5)){}
  /* Deselect: Chip Select high */
  LCD_CS_HIGH();
}

/**
  * @brief  Reads register value.
  * @param  RegValue Address of the register to read
  * @param  ReadSize Number of bytes to read
  * @retval Content of the register value
  */
uint32_t LCD_IO_ReadData(uint16_t RegValue, uint8_t ReadSize)
{
  uint32_t readvalue = 0;

  /* Select: Chip Select low */
  LCD_CS_LOW();

  /* Reset WRX to send command */
  LCD_WRX_LOW();

  LL_SPI_TransmitData16(SPI5, RegValue);

  readvalue = LL_SPI_ReceiveData16(SPI5);

  /* Set WRX to send data */
  LCD_WRX_HIGH();

  /* Deselect: Chip Select high */
  LCD_CS_HIGH();

  return readvalue;
}

/**
  * @brief  Wait for loop in ms.
  * @param  Delay in ms.
  */
void LCD_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/**
 * @brief  Writes  to the selected LCD register.
 * @param  LCD_Reg: address of the selected register.
 * @retval None
 */
void ili9341_WriteReg(uint8_t LCD_Reg)
{
	LCD_IO_WriteReg(LCD_Reg);
}

/**
 * @brief  Writes data to the selected LCD register.
 * @param  LCD_Reg: address of the selected register.
 * @retval None
 */
void ili9341_WriteData(uint16_t RegValue)
{
	LCD_IO_WriteData(RegValue);
}

/**
 * @brief  Reads the selected LCD Register.
 * @param  RegValue: Address of the register to read
 * @param  ReadSize: Number of bytes to read
 * @retval LCD Register Value.
 */
uint32_t ili9341_ReadData(uint16_t RegValue, uint8_t ReadSize)
{
	/* Read a max of 4 bytes */
	return (LCD_IO_ReadData(RegValue, ReadSize));
}
/**
 * @brief  Power on the LCD.
 * @param  None
 * @retval None
 */
void ili9341_Init(uint32_t buffer)
{
	buffer_addr = buffer;
	/* Initialize ILI9341 low level bus layer ----------------------------------*/
    LCD_CS_LOW();
    LCD_CS_HIGH();

	/* Configure LCD */
	ili9341_WriteReg(0xCA);
	ili9341_WriteData(0xC3);
	ili9341_WriteData(0x08);
	ili9341_WriteData(0x50);
	ili9341_WriteReg(LCD_POWERB);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0xC1);
	ili9341_WriteData(0x30);
	ili9341_WriteReg(LCD_POWER_SEQ);
	ili9341_WriteData(0x64);
	ili9341_WriteData(0x03);
	ili9341_WriteData(0x12);
	ili9341_WriteData(0x81);
	ili9341_WriteReg(LCD_DTCA);
	ili9341_WriteData(0x85);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x78);
	ili9341_WriteReg(LCD_POWERA);
	ili9341_WriteData(0x39);
	ili9341_WriteData(0x2C);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x34);
	ili9341_WriteData(0x02);
	ili9341_WriteReg(LCD_PRC);
	ili9341_WriteData(0x20);
	ili9341_WriteReg(LCD_DTCB);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x00);
	ili9341_WriteReg(LCD_FRMCTR1);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x1B);
	ili9341_WriteReg(LCD_DFC);
	ili9341_WriteData(0x0A);
	ili9341_WriteData(0xA2);
	ili9341_WriteReg(LCD_POWER1);
	ili9341_WriteData(0x10);
	ili9341_WriteReg(LCD_POWER2);
	ili9341_WriteData(0x10);
	ili9341_WriteReg(LCD_VCOM1);
	ili9341_WriteData(0x45);
	ili9341_WriteData(0x15);
	ili9341_WriteReg(LCD_VCOM2);
	ili9341_WriteData(0x90);
	ili9341_WriteReg(LCD_MAC);
	ili9341_WriteData(0x48);
	ili9341_WriteReg(LCD_3GAMMA_EN);
	ili9341_WriteData(0x00);
	ili9341_WriteReg(LCD_RGB_INTERFACE);
	ili9341_WriteData(0xC2);
	ili9341_WriteReg(LCD_DFC);
	ili9341_WriteData(0x0A);
	ili9341_WriteData(0xA7);
	ili9341_WriteData(0x27);
	ili9341_WriteData(0x04);

	/* Colomn address set */
	ili9341_WriteReg(LCD_COLUMN_ADDR);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0xEF);
	/* Page address set */
	ili9341_WriteReg(LCD_PAGE_ADDR);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x01);
	ili9341_WriteData(0x3F);
	ili9341_WriteReg(LCD_INTERFACE);
	ili9341_WriteData(0x01);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x06);

	ili9341_WriteReg(LCD_GRAM);
	LCD_Delay(200);

	ili9341_WriteReg(LCD_GAMMA);
	ili9341_WriteData(0x01);

	ili9341_WriteReg(LCD_PGAMMA);
	ili9341_WriteData(0x0F);
	ili9341_WriteData(0x29);
	ili9341_WriteData(0x24);
	ili9341_WriteData(0x0C);
	ili9341_WriteData(0x0E);
	ili9341_WriteData(0x09);
	ili9341_WriteData(0x4E);
	ili9341_WriteData(0x78);
	ili9341_WriteData(0x3C);
	ili9341_WriteData(0x09);
	ili9341_WriteData(0x13);
	ili9341_WriteData(0x05);
	ili9341_WriteData(0x17);
	ili9341_WriteData(0x11);
	ili9341_WriteData(0x00);
	ili9341_WriteReg(LCD_NGAMMA);
	ili9341_WriteData(0x00);
	ili9341_WriteData(0x16);
	ili9341_WriteData(0x1B);
	ili9341_WriteData(0x04);
	ili9341_WriteData(0x11);
	ili9341_WriteData(0x07);
	ili9341_WriteData(0x31);
	ili9341_WriteData(0x33);
	ili9341_WriteData(0x42);
	ili9341_WriteData(0x05);
	ili9341_WriteData(0x0C);
	ili9341_WriteData(0x0A);
	ili9341_WriteData(0x28);
	ili9341_WriteData(0x2F);
	ili9341_WriteData(0x0F);

	ili9341_WriteReg(LCD_SLEEP_OUT);
	LCD_Delay(200);
	ili9341_WriteReg(LCD_DISPLAY_ON);
	/* GRAM start writing */
	ili9341_WriteReg(LCD_GRAM);
	LCD_Delay(100);
}

/**
 * @brief  Disables the Display.
 * @param  None
 * @retval LCD Register Value.
 */
uint16_t ili9341_ReadID(void)
{
	return ((uint16_t)ili9341_ReadData(LCD_READ_ID4, LCD_READ_ID4_SIZE));
}

/**
 * @brief  Enables the Display.
 * @param  None
 * @retval None
 */
void ili9341_DisplayOn(void)
{
	/* Display On */
	ili9341_WriteReg(LCD_DISPLAY_ON);
}

/**
 * @brief  Disables the Display.
 * @param  None
 * @retval None
 */
void ili9341_DisplayOff(void)
{
	/* Display Off */
	ili9341_WriteReg(LCD_DISPLAY_OFF);
}


/**
 * @brief  Get LCD PIXEL WIDTH.
 * @param  None
 * @retval LCD PIXEL WIDTH.
 */
uint16_t ili9341_GetLcdPixelWidth(void)
{
	/* Return LCD PIXEL WIDTH */
	return ILI9341_LCD_PIXEL_WIDTH;
}

/**
 * @brief  Get LCD PIXEL HEIGHT.
 * @param  None
 * @retval LCD PIXEL HEIGHT.
 */
uint16_t ili9341_GetLcdPixelHeight(void)
{
	/* Return LCD PIXEL HEIGHT */
	return ILI9341_LCD_PIXEL_HEIGHT;
}

void ili9341_WritePixel(uint16_t x, uint16_t y, uint16_t color){
	uint32_t offset = (x + y * lcd.GetWidth()) * 2;
	*(__IO uint16_t*)(buffer_addr + offset) = color;
}
void ili9341_Fill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color){
	for(uint16_t x=x0; x<x1;x++){
		for(uint16_t y=y0;y<y1;y++){
			ili9341_WritePixel(x, y, color);
		}
	}
}

LCDTypeDef lcd =
{
		ili9341_Init,
		ili9341_ReadID,
		ili9341_DisplayOn,
		ili9341_DisplayOff,
		0, //SetCursor
		ili9341_WritePixel,
		0, //ReadPixel
		ili9341_Fill,
		0,
		0,
		0,
		ili9341_GetLcdPixelWidth,
		ili9341_GetLcdPixelHeight,
		0,
		0,
};
