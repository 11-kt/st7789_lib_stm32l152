/*
 * st7789.c
 *
 *  Created on: Feb 6, 2024
 *      Author: Andrianov Vitaly
 */

#include "st7789.h"
uint8_t buff_frame[120*160*2];

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

	st7789_SetWindow(0, 0, 120, 160);
	st7789_FillDisplay(YELLOW_st7789);
	st7789_RunDisplayUPD();
//	st7789_StopDispayUPD();

	HAL_Delay(25);

	st7789_SetWindow(120, 0, 240, 160);
	st7789_FillDisplay(RED_st7789);
	st7789_RunDisplayUPD();
	//	st7789_StopDispayUPD();

	HAL_Delay(25);

	st7789_SetWindow(120, 160, 240, 320);
	st7789_FillDisplay(GREEN_st7789);
	st7789_RunDisplayUPD();
//	st7789_StopDispayUPD();

	HAL_Delay(25);

	st7789_SetWindow(0, 160, 120, 320);
	st7789_FillDisplay(MAGENTA_st7789);
	st7789_RunDisplayUPD();

	HAL_Delay(25);
//
//	int i = 60;
//	for (i=60; i < 100; i++) {
//		st7789_DrawPixel_DMA(i, i, BLUE_st7789, 120, 160);
//	}
////	st7789_FillDisplay(MAGENTA_st7789);
//	st7789_RunDisplayUPD();
//
//	HAL_Delay(25);
//	st7789_SetWindow(50, 50, 100, 100);
//	st7789_DrawChar_DMA(0, 0, BLACK_st7789, &font_7x9, 3, 'A', 50, 50);
//	st7789_RunDisplayUPD();
//
//	HAL_Delay(25);
//	st7789_DrawChar(110, 110, BLACK_st7789, &font_7x9, 3, 'A');
}

void st7789_SendData(uint8_t data) {
	CMSIS_SPI_Enable();

	while((SPI1->SR & SPI_SR_TXE) == RESET) {}

	*((__IO uint8_t *) & SPI1->DR) = data;

	while((SPI1->SR & (SPI_SR_TXE | SPI_SR_BSY)) != SPI_SR_TXE) {};

	CMSIS_SPI_Disable();
}

void st7789_SendCmd(uint8_t cmd) {
	CMSIS_DC_Enable();

	SET_BIT(SPI1->CR1, SPI_CR1_BIDIOE);

	st7789_SendData(cmd);

	CMSIS_DC_Disable();
}

void st7789_Reset() {
	CMSIS_RST_Enable();
	CMSIS_RST_Disable();
}

void st7789_SoftwareReset() {
	st7789_SendCmd(SWRESET);
}

void st7789_SleepIn() {
	st7789_SendCmd(SLPIN);
}

void st7789_SleepOut() {
	st7789_SendCmd(SLPOUT);
}

void st7789_NormalDispModeOn() {
	st7789_SendCmd(NORON);
}

void st7789_InversionOn() {
	st7789_SendCmd(INVON);
}

void st7789_InversionOff() {
	st7789_SendCmd(INVOFF);
}

void st7789_DisplayOn() {
	st7789_SendCmd(DISPON);
}


void st7789_DisplayOff() {
	st7789_SendCmd(DISPOFF);
}

void st7789_ColAddrSet(uint16_t colStart, uint16_t colEnd) {
	st7789_SendCmd(CASET);
	st7789_SendData(colStart >> 8);
	st7789_SendData(colStart & 0xFF);
	st7789_SendData((colEnd-1)>>8);
	st7789_SendData((colEnd-1)&0xFF);
}

void st7789_RowAddrSet(uint16_t rowStart, uint16_t rowEnd) {
	st7789_SendCmd(RASET);
	st7789_SendData(rowStart >> 8);
	st7789_SendData(rowStart & 0xFF);
	st7789_SendData((rowEnd-1) >> 8);
	st7789_SendData((rowEnd-1) & 0xFF);
}

void st7789_PixelFormat(uint8_t pixelMode) {
	st7789_SendCmd(COLMOD);
	st7789_SendData(pixelMode);
}

void st7789_Rotation(uint8_t rotation) {
	st7789_SendCmd(MADCTL);
	st7789_SendData(rotation);
}

void st7789_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {

	CMSIS_CS_Enable();

	st7789_ColumnSet(x0, x1);

	st7789_RowSet(y0, y1);

	st7789_SendCmd(RAMWR);

	CMSIS_CS_Disable();
}

void st7789_ColumnSet(uint16_t colStart, uint16_t colEnd) {
	if (colStart > colEnd) return;

	if (colEnd > WIDTH_st7789) return;

	colStart += XSTART_st7789;
	colEnd += XSTART_st7789;

	st7789_ColAddrSet(colStart, colEnd);
}

void st7789_RowSet(uint16_t rowStart, uint16_t rowEnd) {
	if (rowStart > rowEnd) return;

	if (rowEnd > HEIGHT_st7789) return;

	rowStart += YSTART_st7789;
	rowEnd += YSTART_st7789;

	st7789_RowAddrSet(rowStart, rowEnd);
}

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

void st7789_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color){
  if ((x >= WIDTH_st7789) || (y >= HEIGHT_st7789)) return;

  if ((x + w) > WIDTH_st7789) w = WIDTH_st7789 - x;

  if ((y + h) > HEIGHT_st7789) h = HEIGHT_st7789 - y;

  st7789_SetWindow(x, y, x + w, y + h);

  st7789_RamWrite(&color, (h * w));
}

void st7789_DrawPixel(int16_t x, int16_t y, uint16_t color){
  if ((x < 0) ||(x >= WIDTH_st7789) || (y < 0) || (y >= HEIGHT_st7789)) return;

  st7789_SetWindow(x, y, x, y);

  st7789_RamWrite(&color, 1);
}

void st7789_DrawChar(uint16_t x, uint16_t y, uint16_t textColor, font_t* font,uint8_t fontIncrease, unsigned char ch) {
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
			/* if '¨' symbol */
			else if(ch == 168)
				currentChar = font->data[(160) * font->fontHeight + i];
			/* if '¸' symbol */
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

void st7789_PrintString(uint16_t x, uint16_t y, uint16_t textColor, font_t* font, uint8_t fontIncrease, char *str) {

	if (fontIncrease < 1) fontIncrease = 1;

	uint16_t len = strlen(str);

	while (len--) {
		st7789_DrawChar(x, y, textColor, font, fontIncrease, *str);

		x = x + (font->fontWidth * fontIncrease);

		str++;
	}
}

//TEST DMA

void st7789_RunDisplayUPD() {
	DMA1_Channel3->CCR &= ~(DMA_CCR_EN); // DMA off

	DMA1_Channel3->CPAR = (uint32_t)&(SPI1->DR); // spi1 data reg to dma

	DMA1_Channel3->CMAR = (uint32_t)&(buff_frame); // data adr

	DMA1_Channel3->CNDTR = sizeof(buff_frame); // data size

	DMA1->IFCR &= ~(DMA_IFCR_CGIF3);

	CMSIS_CS_Enable();

//	DMA1_Channel3->CCR |= DMA_CCR_CIRC; // CIRC mode DMA

	DMA1_Channel3->CCR |= DMA_CCR_EN; // DMA on
}

void st7789_StopDispayUPD() {

	// wait until all data is sent (count becomes 0)
	while (DMA1_Channel3->CNDTR != 0) {};
	// Wait until tx buffer is empty (not set)
	while (!((SPI1->SR & SPI_SR_TXE) == RESET));
	// Wait until bus is not busy
	while((SPI1->SR & (SPI_SR_TXE | SPI_SR_BSY)) != SPI_SR_TXE) {};

	DMA1_Channel3->CCR &= ~(DMA_CCR_EN); // DMA off

	DMA1_Channel3->CCR &= ~DMA_CCR_CIRC; //CIRC mode off

	CMSIS_CS_Disable();
}

void st7789_FillDisplay(uint16_t color) {
	uint8_t color_high = (color>>8);
	uint8_t color_low = color;
	for (int i=0; i < sizeof(buff_frame) - 2; i = i+2) {
		buff_frame[i] = color_high;
		buff_frame[i+1] = color_low;
	}
}

//void st7789_DrawPixel_DMA(int16_t x, int16_t y, uint16_t color, uint16_t win_Width, uint16_t win_Height) {
//	uint8_t color_high = (color>>8);
//	uint8_t color_low = color;
//
//	if ((x < 0) || (x >= win_Width) || (y < 0) || (y >= win_Height)) return;
//
//	buff_frame[y * win_Width * 2 + x] = color_high;
//	buff_frame[y * win_Width * 2 + x + 1] = color_low;
//}
//
//void st7789_DrawChar_DMA(uint16_t x, uint16_t y, uint16_t textColor, font_t* font,uint8_t fontIncrease, unsigned char ch, uint16_t win_Width, uint16_t win_Height) {
//	uint32_t currentChar, nextX, nextY;
//	uint32_t currentX = x, currentY = y;
//
//	if (fontIncrease < 1) fontIncrease = 1;
//
//	/* Check LCD space*/
//	if (win_Width >= (x + font->fontWidth) || win_Height >= (y + font->fontHeight)){
//		/* Go through font */
//		for (uint8_t i = 0; i < font->fontHeight; i++) {
//			/* if eng symbol */
//			if (ch < 127)
//				currentChar = font->data[(ch - 32) * font->fontHeight + i];
//			/* if rus symbol */
//			else if(ch > 191 )
//				currentChar = font->data[((ch - 192) + 96) * font->fontHeight + i];
//			/* if '¨' symbol */
//			else if(ch == 168)
//				currentChar = font->data[(160) * font->fontHeight + i];
//			/* if '¸' symbol */
//			else if(ch == 184)
//				currentChar = font->data[(161) * font->fontHeight + i];
//
//			for (uint8_t j = 0; j < font->fontWidth; j++) {
//				if ((currentChar << j) & 0x8000) {
//					for (nextY = 0; nextY < fontIncrease; nextY++) {
//						for (nextX = 0; nextX < fontIncrease; nextX++) st7789_DrawPixel_DMA(currentX+nextX, currentY+nextY, textColor, win_Width, win_Height);
//					}
//				}
//				currentX += fontIncrease;
//			}
//			currentX = x;
//			currentY += fontIncrease;
//		}
//	}
//}
