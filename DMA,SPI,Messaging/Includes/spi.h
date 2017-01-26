/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * spi.h
 *  Created on: Oct 26, 2016
 *  
 */

#ifndef SOURCES_SPI_H_
#define SOURCES_SPI_H_

#include "MKL25Z4.h"
#include <stdint.h>

void spi_init(void);
uint8_t spi_write_read_byte(char spiMsg);
void spi_flush();

#endif /* SOURCES_SPI_H_ */
