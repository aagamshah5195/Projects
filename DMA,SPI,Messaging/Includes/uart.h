/*
 * uart.h
 *
 *  Created on: Oct 6, 2016
 *      Author: Akshit
 */
#include <stdint.h>
#ifndef SOURCES_UART_H_
#define SOURCES_UART_H_

void uart_init(uint32_t baud);
void UART0_IRQHandler (void);
void RGB_init(void);

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
#endif /* SOURCES_UART_H_ */
