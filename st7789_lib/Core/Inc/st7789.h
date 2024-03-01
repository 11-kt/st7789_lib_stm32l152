/*
 * st7789.h
 *
 *  Created on: Feb 2, 2024
 *      Author: Andrianov Vitaly
 */

#ifndef INC_ST7789_H_
#define INC_ST7789_H_

#include "cmsis_SPI1.h"
#include "utils/st7789_cmds.h"
#include "utils/colors.h"
#include "utils/display_st7789.h"
#include "utils/st7789_symbols.h"
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	void st7789_init();																										// display init cmds sequence
	void st7789_SendData(uint8_t data);																						// send data to display
	void st7789_SendCmd(uint8_t cmd);																						// send cmd to display
	void st7789_Reset();																									// display hardware reset
	void st7789_SoftwareReset();																							// display software reset
	void st7789_SleepIn();																									// display sleep mode on
	void st7789_SleepOut();																									// display sleep mode off
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	void st7789_NormalDispModeOn();																							// normal display mode (not partial mode)
	void st7789_InversionOn();																								// on display color inversion
	void st7789_InversionOff();																								// off display color inversion
	void st7789_DisplayOn();																								// off display inversion
	void st7789_DisplayOff();																								// send comand to display off
	void st7789_ColAddrSet(uint16_t colStart, uint16_t colEnd);																// set display column addr
	void st7789_RowAddrSet(uint16_t rowStart, uint16_t rowEnd);																// set display row addr
	void st7789_RamWrite(uint16_t *pBuff, uint32_t len);																	// write data to display
	void st7789_PixelFormat(uint8_t pixelMode);																				// set display pixel format
	void st7789_Rotation(uint8_t rotation);																					// set display rotation
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	void st7789_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);										// fill rect on display
	void st7789_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);												// set display window size
	void st7789_ColumnSet(uint16_t colStart, uint16_t colEnd);																// set current display column
	void st7789_RowSet(uint16_t rowStart, uint16_t rowEnd);																	// set current display row
	void st7789_DrawPixel(int16_t x, int16_t y, uint16_t color);															// draw pixel on display
	void st7789_DrawChar(uint16_t x, uint16_t y, uint16_t textColor, font_t* font, uint8_t fontIncrease, unsigned char ch);	// draw char on display
	void st7789_print(uint16_t x, uint16_t y, uint16_t textColor, font_t* font, uint8_t fontIncrease, char *str);			// draw string on display
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	void st7789_RunDisplayUPD();
	void st7789_FillDisplay(uint16_t color);
	void st7789_StopDispayUPD();
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	#define	rgb565(r, g, b)	(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))										// red, blue, green num to hex color
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//

#endif /* INC_ST7789_H_ */
