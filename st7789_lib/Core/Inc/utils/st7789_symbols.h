/*
 * st7789_symbols.h
 *
 *  Created on: Feb 10, 2024
 *      Author: Andrianov Vitaly
 */

#ifndef INC_UTILS_ST7789_SYMBOLS_H_
#define INC_UTILS_ST7789_SYMBOLS_H_


#include "string.h"
#include "stdlib.h"
#include "stm32l1xx.h"

/**
  * font struct (font width and heigh + data)
 */
typedef struct {
	uint8_t fontWidth;
	uint8_t fontHeight;
	const uint16_t *data;
} font_t;

/**
  * font size struct (string length and height)
 */
typedef struct {
	uint16_t str_length;
	uint16_t str_height;
} fonts_size_t;

char* st7789_symbols_getStringSize(char* str, fonts_size_t* sizeStruct, font_t* font);	// get String size

extern font_t font_11x18;

#endif /* INC_UTILS_ST7789_SYMBOLS_H_ */
