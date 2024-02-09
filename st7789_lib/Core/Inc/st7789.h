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

void st7789_init();
void st7789_SendData(uint8_t data);
void st7789_SendCmd(uint8_t cmd);
void st7789_Reset();
void st7789_SoftwareReset();
void st7789_SleepIn();
void st7789_SleepOut();
void st7789_NormalDispModeOn();
void st7789_InversionOn();
void st7789_InversionOff();
void st7789_DisplayOn();
void st7789_DisplayOff();
void st7789_ColAddrSet(uint16_t colStart, uint16_t colEnd);
void st7789_RowAddrSet(uint16_t rowStart, uint16_t rowEnd);
void st7789_RamWrite(uint16_t *pBuff, uint32_t len);
void st7789_PixelFormat(uint8_t pixelMode);
void st7789_Rotation(uint8_t rotation);

void st7789_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void st7789_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void st7789_ColumnSet(uint16_t colStart, uint16_t colEnd);
void st7789_RowSet(uint16_t rowStart, uint16_t rowEnd);

#endif /* INC_ST7789_H_ */
