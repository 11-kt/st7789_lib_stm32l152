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

typedef struct {
	uint8_t fontWidth;
	uint8_t fontHeight;
	const uint16_t *data;
} font_t;

typedef struct {
	uint16_t str_length;
	uint16_t str_height;
} fonts_size_t;

char* st7789_symbols_getStringSize(char* str, fonts_size_t* sizeStruct, font_t* font);

extern font_t font_7x9;

#endif /* INC_UTILS_ST7789_SYMBOLS_H_ */
