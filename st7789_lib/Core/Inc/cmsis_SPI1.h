/*
 * cmsis_SPI1.h
 *
 *  Created on: Feb 5, 2024
 *      Author: Andrianov Vitaly
 */

#ifndef INC_CMSIS_SPI1_H_
#define INC_CMSIS_SPI1_H_

#include "stm32l152xe.h"
#include "stm32l1xx.h"

//--------------------------------------------------------------------------------//
	void CMSIS_SPI1_init();				// spi1 init
	void CMSIS_GPIO_init();				// gpio (spi1 + display cs, rst, dc) init
	void CMSIS_DMA_init();				// transmit	spi dma
//--------------------------------------------------------------------------------//
	void CMSIS_SPI_Enable();			// spi enable
	void CMSIS_SPI_Disable();			// spi disable
	void CMSIS_CS_Enable();				// display cs enable
	void CMSIS_CS_Disable();			// display cs disable
	void CMSIS_RST_Enable();			// display rst enable
	void CMSIS_RST_Disable();			// display rst disable
	void CMSIS_DC_Enable();				// display dc enable
	void CMSIS_DC_Disable();			// display dc disable
//--------------------------------------------------------------------------------//
	#define spi1_RST_Pin GPIO_PIN_0		// display rst pin
	#define spi1_RST_GPIO_Port GPIOA	// display rst port
	#define spi1_DC_Pin GPIO_PIN_1		// display dc pin
	#define spi1_DC_GPIO_Port GPIOA		// display dc port
	#define spi1_CS_Pin GPIO_PIN_9		// display cs pin
	#define spi1_CS_GPIO_Port GPIOA		// display cs port
//--------------------------------------------------------------------------------//

#endif /* INC_CMSIS_SPI1_H_ */
