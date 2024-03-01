/*
 * cmsis_SPI1.c
 *
 *  Created on: Feb 5, 2024
 *      Author: Andrianov Vitaly
 */

#include "cmsis_SPI1.h"

/**
  * @brief SPI1 init
  * @note master mode, Software Slave Management, MSB FIRST
  * prescaler=2, full-duplex, 8bit data, dma on tx
  * @retval void
  */
void CMSIS_SPI1_init() {
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; 						// Enable SPI1 clock

	SPI1->CR1 |= (0<<0) | (1<<1); 								// CPOL=1, CPHA=1

	SPI1->CR1 |= (1<<2); 										// Master Mode

	SPI1->CR1 |= (0<<3); 										// BR[2:0] = 000: fPCLK/2; fPLCK=32MHz

	SPI1->CR1 &= ~(1<<7); 										// LSBfirst=0 -> MSB FIRST

	SPI1->CR1 |= (1<<8) | (1<<9);  								// SSM=1, SSi=1 -> Software Slave Management

	SPI1->CR1 &= ~(1<<10);  									// RXONLY = 0, full-duplex

	SPI1->CR1 &= ~(1<<11);  									// DFF=0, 8 bit data

	SPI1->CR2 |= (1<<1); 										// TX DMA ena
}

/**
  * @brief SPI1 and display gpio init
  * @note Output: PA0,PA1,PA9, alternate:PA5,PA7, H/S: PA0,PA1, AF5(SPI1): PA5,PA7
  * @retval void
  */
void CMSIS_GPIO_init() {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 							// Enable GPIO Clock

	GPIOA->MODER |= (1<<0)|(1<<2)|(2<<10)|(2<<14)|(1<<18);		// Output functions for PA0,PA1,PA9, alternate functions for PA5,PA7

	GPIOA->OSPEEDR |= (3<<0)|(3<<2)|(3<<10)|(3<<14)|(3<<18);	// HIGH Speed for PA0,PA1

	GPIOA->AFR[0] |= (5<<20)|(5<<28);   						// AF5(SPI1) for PA5,PA7
}

/**
  * @brief SPI1 TX DMA init
  * @note 1byte data, mem to periph mode, mem inc on
  * @retval void
  */
void CMSIS_DMA_init() {
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	DMA1_Channel3->CCR |= DMA_CCR_PSIZE_0; 						// Peripheral width 1 byte

	DMA1_Channel3->CCR |= DMA_CCR_DIR; 							// Mem to periph

	DMA1_Channel3->CCR |= DMA_CCR_MINC; 						// Mem inc on

	DMA1_Channel3->CCR |= DMA_CCR_PL; 							// High priority DMA
}

/**
  * @brief SPI1 enable
  * @retval void
  */
void CMSIS_SPI_Enable() {
	if((SPI1->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE) {
		SET_BIT(SPI1->CR1, SPI_CR1_SPE);
	}
}

/**
  * @brief SPI1 disable
  * @retval void
  */
void CMSIS_SPI_Disable() {
	if((SPI1->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE) {
		CLEAR_BIT(SPI1->CR1, SPI_CR1_SPE);
	}
}

/**
  * @brief display cs enable
  * @retval void
  */
void CMSIS_CS_Enable() {
	spi1_CS_GPIO_Port->BSRR = (spi1_CS_Pin << 16);
}

/**
  * @brief display cs disable
  * @retval void
  */
void CMSIS_CS_Disable() {
	spi1_CS_GPIO_Port->BSRR = spi1_CS_Pin;
}

/**
  * @brief display rst enable
  * @retval void
  */
void CMSIS_RST_Enable() {
	spi1_RST_GPIO_Port->BSRR = (spi1_RST_Pin << 16);
}

/**
  * @brief display rst disable
  * @retval void
  */
void CMSIS_RST_Disable() {
	spi1_RST_GPIO_Port->BSRR = spi1_RST_Pin;
}

/**
  * @brief display dc enable
  * @retval void
  */
void CMSIS_DC_Enable() {
	spi1_DC_GPIO_Port->BSRR = (spi1_DC_Pin << 16);
}

/**
  * @brief display cd disable
  * @retval void
  */
void CMSIS_DC_Disable() {
	spi1_DC_GPIO_Port->BSRR = spi1_DC_Pin;
}
