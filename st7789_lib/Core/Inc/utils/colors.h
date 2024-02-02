/*
 * colors.h
 *
 *  Created on: Feb 2, 2024
 *      Author: Andrianov Vitaly
 */

#ifndef INC_UTILS_COLORS_H_
#define INC_UTILS_COLORS_H_

//------------- Цвета -------------//
#define		RED_st7789		0xF800
#define		GREEN_st7789	0x07E0
#define		BLUE_st7789		0x001F
#define		BLACK_st7789	0x0000
#define		WHITE_st7789	0xFFFF
#define		CYAN_st7789		0x07FF
#define		MAGENTA_st7789	0xF81F
#define		YELLOW_st7789	0xFFE0
//---------------------------------//

//-- Битовые маски настройки цветности --//
#define		ColorMode_65K_st7789	0x50
#define		ColorMode_262K_st7789	0x60
#define		ColorMode_12bit_st7789	0x03
#define		ColorMode_16bit_st7789	0x05
#define		ColorMode_18bit_st7789	0x06
#define		ColorMode_16M_st7789	0x07
//---------------------------------------//

#endif /* INC_UTILS_COLORS_H_ */
