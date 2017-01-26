/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * uart.h
 *
 *  Created on: Nov 28, 2016
 */

#ifndef INCLUDES_UART_H_
#define INCLUDES_UART_H_
#include <stdint.h>

void uart_init(uint32_t baud);
void UART0_IRQHandler (void);
void RGB_init(void);
void UART0_WriteString(char string[]);
void UART0_WriteChar(char BYTE);
void UART0_ReadString(char string[]);

char UART0_ReadChar();

#define R(bright) TPM2_C0V=TPM2_MOD *(bright)		// Red led control with Brightness 'B'
#define G(bright) TPM2_C1V=TPM2_MOD *(bright)		// Green led control with Brightness 'B'
#define B(bright) TPM0_C1V=TPM0_MOD *(bright)		// Blue led control with Brightness 'B'

#define R_ON	TPM2_C0V = TPM2_MOD
#define R_OFF	TPM2_C0V = 0

#define G_ON	TPM2_C1V = TPM2_MOD
#define G_OFF	TPM2_C1V = 0

#define B_ON	TPM0_C1V = TPM0_MOD
#define B_OFF	TPM0_C1V = 0

#define baud 38400			//baud rate



#endif /* INCLUDES_UART_H_ */
