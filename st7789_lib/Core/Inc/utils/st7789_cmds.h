/*
 * st7789_cmds.h
 *
 *  Created on: Feb 2, 2024
 *      Author: Andrianov Vitaly
 */

#ifndef INC_UTILS_ST7789_CMDS_H_
#define INC_UTILS_ST7789_CMDS_H_

//----- st7789 commands -----//
//--- Read Display MADCTL ---//
#define 	MADCTL_MY	0x80 // Row Address Order
#define 	MADCTL_MX	0x40 // Column Address Order
#define 	MADCTL_MV	0x20 // Row/Column Exchange
#define 	MADCTL_ML	0x10 // Scan Address Order
#define 	MADCTL_RGB	0x00 // RGB Order
#define 	MADCTL_BGR	0x08 // BGR Order
#define 	MADCTL_MH	0x04 // Horizontal Order
//---------------------------//
//------ Software reset -----//
#define 	SWRESET		0x01
//--------- Sleep in --------//
#define 	SLPIN		0x10
//--------- Sleep out -------//
#define 	SLPOUT		0x11
//- Normal Display Mode  On -//
#define 	NORON		0x13
//-- Display Inversion Off --//
#define 	INVOFF		0x20
//--- Display Inversion On --//
#define 	INVON		0x21
//------- Display Off -------//
#define 	DISPOFF		0x28
//------- Display On --------//
#define 	DISPON		0x29
//--- Column Address  Set ---//
#define 	CASET		0x2A
//----- Row Address Set -----//
#define 	RASET		0x2B
//------ Memory  Write ------//
#define 	RAMWR		0x2C
// Read Display Pixel Format //
#define 	COLMOD		0x3A
//--- Read Display MADCTL ---//
#define 	MADCTL		0x36
//---------------------------//

#endif /* INC_UTILS_ST7789_CMDS_H_ */
