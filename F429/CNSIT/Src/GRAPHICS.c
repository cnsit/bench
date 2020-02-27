/*
 * GRAPHICS.c
 *
 *  Created on: Feb 23, 2020
 *      Author: jonyzhu
 */

#include "../Inc/GRAPHICS.h"

void Line(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t color, LCDTypeDef* lcd){
	int16_t dx = xe-xs, dx2 = dx<<1;
	int16_t dy = ye-ys, dy2 = dy<<1;
	int16_t s = -1;
	if(dx == 0){ //垂直线
		if(dy>0){
			s = 1;
		}else if(dy==0){
			s = 0;
		}
		for(int16_t i=ys;i!=ye;i+=s){
			lcd->WritePixel(xe, i, color);
		}
	}else if(dy==0){//水平线
		if(dx>0){
			s = 1;
		}else if(dx==0){
			s = 0;
		}
		for(int16_t i=xs;i!=xe;i+=s){
			lcd->WritePixel(i, ye, color);
		}
	}else{
		float k = (float)dy/dx;
		int16_t e = 0;
		if(k>=-1&&k<=1){
			if(dy>=0){
				s = 1;
			}
			int16_t y = ys;
			for(int16_t i=xs;i<=xe;i++){
				lcd->WritePixel(i, y, color);
				if( (e>=0&&e<=dx) || (e<0&&(-e)<=dx)){
					e += dy2;
				}else{
					e += dy2 -s*dx2;
					y += s;
				}
			}
		}else{
			if(dy>=0){
				s = 1;
			}else{
				dy = -dy;
			}
			int16_t x = xs;
			for(int16_t i=ys;i!=ye;i+=s){
				lcd->WritePixel(x, i, color);
				if((e>=0&&e<=dy) || (e<0&&(-e)<=dy)){
					e += s*dx2;
				}else{
					e += s*dx2 - dy2;
					x++;
				}
			}
		}
	}
}
uint16_t Char(uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, char v, LCDTypeDef *lcd, const CNSITFontDescTypeDef *font ){
	CNSITFontIndexMapTypeDef map = font->IndexMap[v - font->Start];
	if(x>=lcd->GetWidth()){
		return lcd->GetWidth();
	}
	uint16_t color;
	uint8_t bytes = (map.Width % 8 == 0?0:1 )+ (map.Width / 8); //data bytes per row
	for (uint16_t r = 0; r < map.Height; r++) {
		if((y+r)>lcd->GetHeight()){
			return x+map.Width;
		}
		uint16_t i = 0;							//total bits drawn
		for (uint8_t c = 0; c < bytes; c++) {
			char d = font->Data[map.Index + r*bytes + c];
			int s = 8;
			while (i < map.Width && s>0) {
				if((x+i)>=lcd->GetWidth()){
					return lcd->GetWidth();
				}
				if((d & (1 << --s)) == 0){
					color = bg;
				}else{
					color = fg;
				}
				lcd->WritePixel(x + i++, y + map.Height - r - 1, color);
			}
		}
	}
	return x + map.Width;
}
uint16_t String(uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, char* v, LCDTypeDef *lcd, const CNSITFontDescTypeDef *font ){
	while (*v) {
		x = Char(x, y, fg, bg, *v, lcd, font);
		v++;
	}
	return x;
}
