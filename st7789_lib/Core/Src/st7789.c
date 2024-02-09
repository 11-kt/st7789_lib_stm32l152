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

	CMSIS_CS_Disable();
}

void st7789_SendData(uint8_t data) {
	CMSIS_SPI_Enable();

	while( (SPI1->SR & SPI_SR_TXE) == RESET ) {}

	*((__IO uint8_t *) & SPI1->DR) = data;

	while((SPI1->SR & (SPI_SR_TXE | SPI_SR_BSY)) != SPI_SR_TXE ) {};

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
