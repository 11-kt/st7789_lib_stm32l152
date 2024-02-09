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

void CMSIS_SPI1_init();
void CMSIS_GPIO_init();
void CMSIS_SPI_Enable();
void CMSIS_SPI_Disable();
void CMSIS_CS_Enable();
void CMSIS_CS_Disable();
void CMSIS_RST_Enable();
void CMSIS_RST_Disable();
void CMSIS_DC_Enable();
void CMSIS_DC_Disable();

#define spi1_RST_Pin GPIO_PIN_0
#define spi1_RST_GPIO_Port GPIOA
#define spi1_DC_Pin GPIO_PIN_1
#define spi1_DC_GPIO_Port GPIOA
#define spi1_CS_Pin GPIO_PIN_9
#define spi1_CS_GPIO_Port GPIOA

#endif /* INC_CMSIS_SPI1_H_ */
