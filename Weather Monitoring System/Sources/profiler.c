/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * profiler.c
 *
 *  Created on: Dec 7, 2016
 */
 
#include "profiler.h"
void profiler(void)
{

SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;			// Enable TPM1 Clock gate
SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);			// Select MCGFLLCLK clock 21 Mhz

TPM1_SC=0;									// Disable Timer
TPM1_MOD = MOD_VAL;							//Set Counter for 10 uS


TPM1_SC |= TPM_SC_PS(0);	// Prescaler divide by 1

/*__enable_irq();					// Enable global Interrupt
NVIC_EnableIRQ(TPM1_IRQn);  	// Enable NVIC Interrupt
TPM1_SC |= TPM_SC_TOIE_MASK; 	// Enable Timer Overflow Interrupt*/
}

void start(void)
{
	TPM1_SC |= TPM_SC_CMOD(1);		// Start Counter
}

void end(void)
{
	uint32_t val_count=0;
	float timer_clk=0;
	TPM1_SC &= ~TPM_SC_CMOD(1);			// Stop Counter

	val_count= TPM1_CNT;
	timer_clk= val_count/T1CLK;			// Clock

/*	if (ov_count !=0)
	{
		timer_clk = timer_clk + (MOD_VAL/T1CLK)*ov_count;
		ov_count=0;
	}*/
	LOG_2("\r\nExecution time:",timer_clk);
}



