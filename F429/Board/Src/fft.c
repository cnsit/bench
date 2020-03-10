/*
 * fft.c
 *
 *  Created on: Mar 7, 2020
 *      Author: jonyzhu
 */
#define fft_len 4096
#define adc_data_len (fft_len)
#define fft_data_len (fft_len)

function fft_init(){
	arm_rfft_instance_q15 sf,sr;
	arm_rfft_init_q15(&sf, fft_len, 0, 1);
	arm_rfft_init_q15(&sr, fft_len, 1, 0);
}
function fft_sample(){
	arm_shift_q15(adc_data, -1, adc_lcd, adc_data_len);
	curve(adc_lcd, adc_data_len, 0, 0, lcd_max_x, lcd_adc_panel_height, lcd_adc_scale_x, 1, red, 0);

	arm_rfft_q15(&sf, adc_data, fft_data);
	arm_abs_q15(fft_data, fft_data, fft_data_len);
	curve(fft_data, fft_data_len, 0, lcd_adc_panel_height+1, lcd_max_x, lcd_fft_panel_height,lcd_fft_scale_x,1, dark_gray,1);
}
