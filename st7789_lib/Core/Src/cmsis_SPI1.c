/*
 * cmsis_SPI1.c
 *
 *  Created on: Feb 5, 2024
 *      Author: Andrianov Vitaly
 */

#include "cmsis_SPI1.h"

void CMSIS_SPI1_init() {

	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // Enable SPI1 clock

	SPI1->CR1 |= (0<<0) | (1<<1); // CPOL=1, CPHA=1

	SPI1->CR1 |= (1<<2); // Master Mode

	SPI1->CR1 |= (0<<3); // BR[2:0] = 000: fPCLK/2; fPLCK=32MHz

	SPI1->CR1 &= ~(1<<7); // LSBfirst=0 -> MSB FIRST

	SPI1->CR1 |= (1<<8) | (1<<9);  // SSM=1, SSi=1 -> Software Slave Management

	SPI1->CR1 &= ~(1<<10);  // RXONLY = 0, full-duplex

	SPI1->CR1 &= ~(1<<11);  // DFF=0, 8 bit data

	SPI1->CR2 = 0;

}

void CMSIS_GPIO_init() {

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Enable GPIO Clock

	GPIOA->MODER |= (1<<0)|(1<<2)|(2<<10)|(2<<14)|(1<<18);  // Alternate functions for PA0,PA1

	GPIOA->OSPEEDR |= (3<<0)|(3<<2)|(3<<10)|(3<<14)|(3<<18);  // HIGH Speed for PA0,PA1

	GPIOA->AFR[0] |= (5<<20)|(5<<28);   // AF5(SPI1) for PA5,PA7

}

void CMSIS_SPI_Enable() {
	if((SPI1->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE) {
		SET_BIT(SPI1->CR1, SPI_CR1_SPE);
	}
}

void CMSIS_SPI_Disable() {
	if((SPI1->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE) {
		CLEAR_BIT(SPI1->CR1, SPI_CR1_SPE);
	}
}

void CMSIS_CS_Enable() {
	spi1_CS_GPIO_Port->BSRR = (spi1_CS_Pin << 16);
}

void CMSIS_CS_Disable() {
	spi1_CS_GPIO_Port->BSRR = spi1_CS_Pin;
}

void CMSIS_RST_Enable() {
	spi1_RST_GPIO_Port->BSRR = (spi1_RST_Pin << 16);
}

void CMSIS_RST_Disable() {
	spi1_RST_GPIO_Port->BSRR = (spi1_RST_Pin << 16);
}
