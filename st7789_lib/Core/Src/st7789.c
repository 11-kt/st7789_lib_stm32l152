/*
 * st7789.c
 *
 *  Created on: Feb 6, 2024
 *      Author: Andrianov Vitaly
 */

#include "st7789.h"

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

	st7789_FillRect(0, 0,  WIDTH_st7789, HEIGHT_st7789, GREEN_st7789);

	CMSIS_CS_Disable();
}

void st7789_SendData(uint8_t data) {
	CMSIS_SPI_Enable();

	while( (SPI1->SR & SPI_SR_TXE) == RESET) {}

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

  st7789_SetWindow(x, y, x + w - 1, y + h - 1);

  st7789_RamWrite(&color, (h * w));
}
