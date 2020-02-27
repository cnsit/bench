#ifndef __CNSIT_LCD_H__
#define __CNSIT_LCD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct
{
	void     (*Init)(uint32_t);
	uint16_t (*ReadID)(void);
	void     (*DisplayOn)(void);
	void     (*DisplayOff)(void);
	void     (*SetCursor)(uint16_t, uint16_t);
	void     (*WritePixel)(uint16_t, uint16_t, uint16_t);
	uint16_t (*ReadPixel)(uint16_t, uint16_t);
	void     (*Fill)(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);

	/* Optimized operation */
	void     (*SetDisplayWindow)(uint16_t, uint16_t, uint16_t, uint16_t);
	void     (*DrawHLine)(uint16_t, uint16_t, uint16_t, uint16_t);
	void     (*DrawVLine)(uint16_t, uint16_t, uint16_t, uint16_t);

	uint16_t (*GetWidth)(void);
	uint16_t (*GetHeight)(void);
	void     (*DrawBitmap)(uint16_t, uint16_t, uint8_t*);
	void     (*DrawRGBImage)(uint16_t, uint16_t, uint16_t, uint16_t, uint8_t*);
} LCDTypeDef;

#ifdef __cplusplus
}
#endif

#endif
