/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * uart.h
 *  Created on: Oct 6, 2016
 */
 
#include <stdint.h>
#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_

void uart_init(uint32_t baud);
void UART0_IRQHandler (void);
void RGB_init(void);

#define R(B) TPM2_C0V=TPM2_MOD *(B)		// Red led control with Brightness 'B'
#define G(B) TPM2_C1V=TPM2_MOD *(B)		// Green led control with Brightness 'B'
#define B(B) TPM0_C1V=TPM0_MOD *(B)		// Blue led control with Brightness 'B'


#endif /* SOURCES_UART_H_ */
