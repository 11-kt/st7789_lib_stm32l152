/*
 * st7789.c
 *
 *  Created on: Feb 6, 2024
 *      Author: Andrianov Vitaly
 */

#include "st7789.h"

uint8_t buff_frame[120*160*2];	// DMA frame buffer

/**
  * @brief Display init cmds sequence
  * @note comtrol display params
  * @retval void
  */
void st7789_init() {
	CMSIS_CS_Enable();

	st7789_Reset();

	st7789_SoftwareReset();

	st7789_SleepOut();

	st7789_PixelFormat((uint8_t) (ColorMode_65K_st7789 | ColorMode_16bit_st7789));

	st7789_Rotation((uint8_t) ROTATION_st7789);

	st7789_ColAddrSet((uint8_t) XSTART_st7789, (uint8_t) WIDTH_st7789);

	st7789_RowAddrSet((uint8_t) YSTART_st7789, (uint8_t) HEIGHT_st7789);

	st7789_NormalDispModeOn();

	st7789_InversionOn();

	st7789_DisplayOn();

	st7789_FillRect(0, 0,  WIDTH_st7789, HEIGHT_st7789, WHITE_st7789);

	CMSIS_CS_Disable();
}

/**
  * @brief Send data to display
  * @param data - Data byte
  * @retval void
  */
void st7789_SendData(uint8_t data) {
	CMSIS_SPI_Enable();

	while((SPI1->SR & SPI_SR_TXE) == RESET) {}

	*((__IO uint8_t *) & SPI1->DR) = data;

	while((SPI1->SR & (SPI_SR_TXE | SPI_SR_BSY)) != SPI_SR_TXE) {};

	CMSIS_SPI_Disable();
}

/**
  * @brief Send command to display
  * @param cmd - Command byte
  * @retval void
  */
void st7789_SendCmd(uint8_t cmd) {
	CMSIS_DC_Enable();

	SET_BIT(SPI1->CR1, SPI_CR1_BIDIOE);

	st7789_SendData(cmd);

	CMSIS_DC_Disable();
}

/**
  * @brief Display hardware reset
  * @note  Control display rst pin
  * @retval void
  */
void st7789_Reset() {
	CMSIS_RST_Enable();
	CMSIS_RST_Disable();
}

/**
  * @brief Display software reset
  * @note  SWRESET cmd
  * @retval void
  */
void st7789_SoftwareReset() {
	st7789_SendCmd(SWRESET);
}

/**
  * @brief Display sleep mode on
  * @note  SLPIN cmd
  * @retval void
  */
void st7789_SleepIn() {
	st7789_SendCmd(SLPIN);
}

/**
  * @brief Display sleep mode off
  * @note  SLPOUT cmd
  * @retval void
  */
void st7789_SleepOut() {
	st7789_SendCmd(SLPOUT);
}

/**
  * @brief Display normal mode on (not partial mode)
  * @note  NORON cmd
  * @retval void
  */
void st7789_NormalDispModeOn() {
	st7789_SendCmd(NORON);
}

/**
  * @brief Display color inversion mode on
  * @note  INVON cmd
  * @retval void
  */
void st7789_InversionOn() {
	st7789_SendCmd(INVON);
}

/**
  * @brief Display color inversion mode off
  * @note  INVOFF cmd
  * @retval void
  */
void st7789_InversionOff() {
	st7789_SendCmd(INVOFF);
}

/**
  * @brief Display on
  * @note  DISPON cmd
  * @retval void
  */
void st7789_DisplayOn() {
	st7789_SendCmd(DISPON);
}

/**
  * @brief Display off
  * @note  DISPOFF cmd
  * @retval void
  */
void st7789_DisplayOff() {
	st7789_SendCmd(DISPOFF);
}

/**
  * @brief Display column addr set
  * @note  CASET cmd
  * @param colStart - Column Start
  * @param colEnd - Column End
  * @retval void
  */
void st7789_ColAddrSet(uint16_t colStart, uint16_t colEnd) {
	st7789_SendCmd(CASET);
	st7789_SendData(colStart >> 8);
	st7789_SendData(colStart & 0xFF);
	st7789_SendData((colEnd-1)>>8);
	st7789_SendData((colEnd-1)&0xFF);
}

/**
  * @brief Display row addr set
  * @note  RASET cmd
  * @param rowStart - Row Start
  * @param rowEnd - Row End
  * @retval void
  */
void st7789_RowAddrSet(uint16_t rowStart, uint16_t rowEnd) {
	st7789_SendCmd(RASET);
	st7789_SendData(rowStart >> 8);
	st7789_SendData(rowStart & 0xFF);
	st7789_SendData((rowEnd-1) >> 8);
	st7789_SendData((rowEnd-1) & 0xFF);
}

/**
  * @brief Display pixel mode
  * @note  COLMOD cmd
  * @param pixelMode - Pixel mode
  * @retval void
  */
void st7789_PixelFormat(uint8_t pixelMode) {
	st7789_SendCmd(COLMOD);
	st7789_SendData(pixelMode);
}

/**
  * @brief Display rotation
  * @note  MADCTL cmd
  * @param rotation - rotation mode
  * @retval void
  */
void st7789_Rotation(uint8_t rotation) {
	st7789_SendCmd(MADCTL);
	st7789_SendData(rotation);
}

/**
  * @brief Display set window
  * @note  RAMWR cmd
  * @param x0 - window start
  * @param y0 - window start
  * @param x1 - window end
  * @param y1 - window end
  * @retval void
  */
void st7789_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {

	CMSIS_CS_Enable();

	st7789_ColumnSet(x0, x1);

	st7789_RowSet(y0, y1);

	st7789_SendCmd(RAMWR);

	CMSIS_CS_Disable();
}

/**
  * @brief Display column set
  * @param colStart - column start
  * @param colEnd - column end
  * @retval void
  */
void st7789_ColumnSet(uint16_t colStart, uint16_t colEnd) {
	if (colStart > colEnd) return;

	if (colEnd > WIDTH_st7789) return;

	colStart += XSTART_st7789;
	colEnd += XSTART_st7789;

	st7789_ColAddrSet(colStart, colEnd);
}

/**
  * @brief Display row set
  * @param rowStart - row start
  * @param rowEnd - row end
  * @retval void
  */
void st7789_RowSet(uint16_t rowStart, uint16_t rowEnd) {
	if (rowStart > rowEnd) return;

	if (rowEnd > HEIGHT_st7789) return;

	rowStart += YSTART_st7789;
	rowEnd += YSTART_st7789;

	st7789_RowAddrSet(rowStart, rowEnd);
}

/**
  * @brief Display ram write
  * @param pBuff - buffer to write
  * @param len - buffer length
  * @retval void
  */
void st7789_RamWrite(uint16_t *pBuff, uint32_t len) {
	CMSIS_CS_Enable();

	uint8_t buff[2];
	buff[0] = *pBuff >> 8;
	buff[1] = *pBuff & 0xFF;

	while (len--){
		st7789_SendData(buff[0]);
		st7789_SendData(buff[1]);
	}

	CMSIS_CS_Disable();
}

/**
  * @brief Display fill rect
  * @param x - start x
  * @param y - start y
  * @param w - rect width
  * @param h - rect height
  * @param color - rect color
  * @retval void
  */
void st7789_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color){
  if ((x >= WIDTH_st7789) || (y >= HEIGHT_st7789)) return;

  if ((x + w) > WIDTH_st7789) w = WIDTH_st7789 - x;

  if ((y + h) > HEIGHT_st7789) h = HEIGHT_st7789 - y;

  st7789_SetWindow(x, y, x + w, y + h);

  st7789_RamWrite(&color, (h * w));
}

/**
  * @brief Display pixel
  * @param x - start x
  * @param y - start y
  * @param color - pixel color
  * @retval void
  */
void st7789_DrawPixel(int16_t x, int16_t y, uint16_t color){
  if ((x < 0) ||(x >= WIDTH_st7789) || (y < 0) || (y >= HEIGHT_st7789)) return;

  st7789_SetWindow(x, y, x, y);

  st7789_RamWrite(&color, 1);
}

/**
  * @brief Display char
  * @param x - start x
  * @param y - start y
  * @param textColor - text color
  * @param font - font
  * @param fontIncrease - font size multiply to constant value
  * @param ch - char
  * @retval void
  */
void st7789_DrawChar(uint16_t x, uint16_t y, uint16_t textColor, font_t* font, uint8_t fontIncrease, unsigned char ch) {
	uint32_t currentChar, nextX, nextY;
	uint32_t currentX = x, currentY = y;

	if (fontIncrease < 1) fontIncrease = 1;

	/* Check LCD space*/
	if (WIDTH_st7789 >= (x + font->fontWidth) || HEIGHT_st7789 >= (y + font->fontHeight)){
		/* Go through font */
		for (uint8_t i = 0; i < font->fontHeight; i++) {
			/* if eng symbol */
			if (ch < 127)
				currentChar = font->data[(ch - 32) * font->fontHeight + i];
			/* if rus symbol */
			else if(ch > 191 )
				currentChar = font->data[((ch - 192) + 96) * font->fontHeight + i];
			/* if '�' symbol */
			else if(ch == 168)
				currentChar = font->data[(160) * font->fontHeight + i];
			/* if '�' symbol */
			else if(ch == 184)
				currentChar = font->data[(161) * font->fontHeight + i];

			for (uint8_t j = 0; j < font->fontWidth; j++) {
				if ((currentChar << j) & 0x8000) {
					for (nextY = 0; nextY < fontIncrease; nextY++) {
						for (nextX = 0; nextX < fontIncrease; nextX++) st7789_DrawPixel(currentX+nextX, currentY+nextY, textColor);
					}
				}
				currentX += fontIncrease;
			}
			currentX = x;
			currentY += fontIncrease;
		}
	}
}

/**
  * @brief Display string
  * @param x - start x
  * @param y - start y
  * @param textColor - text color
  * @param font - font
  * @param fontIncrease - font size multiply to constant value
  * @param str - string
  * @retval void
  */
void st7789_PrintString(uint16_t x, uint16_t y, uint16_t textColor, font_t* font, uint8_t fontIncrease, char *str) {

	if (fontIncrease < 1) fontIncrease = 1;

	uint16_t len = strlen(str);

	while (len--) {
		st7789_DrawChar(x, y, textColor, font, fontIncrease, *str);

		x = x + (font->fontWidth * fontIncrease);

		str++;
	}
}
