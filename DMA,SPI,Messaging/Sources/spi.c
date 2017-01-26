/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/* spi.c
 * This file contains initialisation of spi module of FRDM
 * It also includes read and write functions of spi and flushing the Spi registers
 */
#include "main.h"

void spi_init(void)
{
	   // Turn on port C
	   SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	   // Turn on SPI0 clock
	   SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

	   // Set up ports for SPI0
	   PORTC->PCR[4] |= PORT_PCR_MUX(1); // CSN as gpio pin
	   PORTC->PCR[5] |= PORT_PCR_MUX(2); // SCLK pin
	   PORTC->PCR[6] |= PORT_PCR_MUX(2); // MISO pin
	   PORTC->PCR[7] |= PORT_PCR_MUX(2); // MOSI pin
	   PORTC->PCR[8] |= PORT_PCR_MUX(1); // CE as gpio pin

	   // Set port C, pin 4 data direction to output
	   PTC_BASE_PTR->PDDR |= 1<<4;

	   SPI_C1_REG(SPI0) = SPI_C1_SPE_MASK;	// Enable SPIO clock
	   SPI_C2_REG(SPI0) = 0x00;

	   SPI_C1_REG(SPI0) = SPI_C1_MSTR_MASK |SPI_C1_SPE_MASK ;	// Enable Master Mode and SPIO clk

	   // prescaler=1, divisor=4 , 24MHz/4 = 6MHz
	   SPI_BR_REG(SPI0) = 0x01;
}

uint8_t spi_write_read_byte(char spiMsg)
{

  while(!(SPI_S_SPTEF_MASK & SPI0_S)); //While buffer is not empty do nothing
  SPI0_D = spiMsg;    //Write char to SPI
  while(!(SPI0_S & SPI_S_SPRF_MASK));
  spiMsg=SPI0_D;	// Read char from SPI
  return spiMsg;
}

void spi_flush()
{
	SPI0_C1&=0xBF;
	spi_init();
}
