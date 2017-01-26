/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/* dma.c
 *  Created on: Oct 31, 2016
 */

#include "main.h"

volatile uint8_t ov_count=0;

void memmove_dma8(uint8_t * src, uint8_t * dst, uint32_t length)
{
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;				//Enable Clock for DMAMUX
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;				//Enable Clock for DMA
	DMAMUX0_CHCFG0 &= 0x00;							//Disable DMA MUX Channel 0 before configuring

	DMA_SAR0 = (uint32_t)src;						//Set the Source Address

	DMA_DAR0 = (uint32_t)dst;						//Set the Destination Address

	DMA_DSR_BCR0 |= length;							//Set the number of byte transfers yet to be transferred

	DMA_DCR0 |= DMA_DCR_SSIZE(1);					//Set the data size of source bus cycle as 8-bit
	DMA_DCR0 |= DMA_DCR_DSIZE(1);					//Set the data size of destination bus cycle as 8-bit

#ifdef MEMMOVE
	DMA_DCR0 |= DMA_DCR_SINC_MASK;					//Incrementing source address after each successful transfer
#endif
	DMA_DCR0 |= DMA_DCR_DINC_MASK;					//Incrementing destination address after each successful transfer
	DMA_DCR0 |= DMA_DCR_EINT_MASK;					//Enabling Interrupts when all the transfers are complete
	NVIC->ISER[0]=0x1;								//Enabling device-specific interrupt in the NVIC interrupt controller.
	DMAMUX0_CHCFG0 |= (DMAMUX_CHCFG_SOURCE(60));					//Routing the DMA source to DMA channel 0 (60th option)
	DMAMUX0_CHCFG0 |= (DMAMUX_CHCFG_ENBL_MASK);		//Enabled the DMA channel 0

	start();										//Function call to start code profiling
	DMA_DCR0 |= DMA_DCR_START_MASK;					//Starting the DMA transfers
}


void memmove_dma32(uint32_t * src, uint32_t * dst, uint32_t length)
{
	uint32_t length2 = length % 4;					//Used when number of bytes to be transferred is not divisible number of words
	length = length - length2;

	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;				//Enable Clock for DMAMUX
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;				//Enable Clock for DMA
	DMAMUX0_CHCFG0 = 0x00;							//Disable DMA MUX Channel 0 before configuring

	DMA_SAR0 = (uint32_t)src;						//Set the Source Address
	DMA_DAR0 = (uint32_t)dst;						//Set the Destination Address

	DMA_DSR_BCR0 |= length;							//Set the number of byte transfers yet to be transferred

	if(length2 == 0)
	{
		DMA_DCR0 &= ~DMA_DCR_SSIZE_MASK;			//Set the data size of source bus cycle as 32-bit
		DMA_DCR0 &= ~DMA_DCR_DSIZE_MASK;			//Set the data size of destination bus cycle as 32-bit

		#ifdef MEMMOVE
		DMA_DCR0 |= DMA_DCR_SINC_MASK;				//Incrementing source address after each successful transfer
		#endif
		DMA_DCR0 |= DMA_DCR_DINC_MASK;				//Incrementing destination address after each successful transfer
		DMA_DCR0 |= DMA_DCR_EINT_MASK;				//Enabling Interrupts when all the transfers are complete
		NVIC->ISER[0]=0x1;							//Enabling device-specific interrupt in the NVIC interrupt controller.

		DMAMUX0_CHCFG0 |= (DMAMUX_CHCFG_SOURCE(60));					//Routing the DMA source to DMA channel 0 (60th option)
		DMAMUX0_CHCFG0 |= (DMAMUX_CHCFG_ENBL_MASK);	//Enabled the DMA channel 0

		start();									//Function call to start code profiling
		DMA_DCR0 |= DMA_DCR_START_MASK;				//Starting the DMA transfers
	}

	else
	{
		DMA_DCR0 &= ~DMA_DCR_SSIZE_MASK;			//Set the data size of source bus cycle as 32-bit
		DMA_DCR0 &= ~DMA_DCR_DSIZE_MASK;			//Set the data size of destination bus cycle as 32-bit

		#ifdef MEMMOVE
		DMA_DCR0 |= DMA_DCR_SINC_MASK;				//Incrementing source address after each successful transfer
		#endif
		DMA_DCR0 |= DMA_DCR_DINC_MASK;				//Incrementing destination address after each successful transfer

		DMAMUX0_CHCFG0 |= (DMAMUX_CHCFG_SOURCE(60));					//Routing the DMA source to DMA channel 0 (60th option)
		DMAMUX0_CHCFG0 |= (DMAMUX_CHCFG_ENBL_MASK);	//Enabled the DMA channel 0

		start();									//Function call to start code profiling
		DMA_DCR0 |= DMA_DCR_START_MASK;				//Starting the DMA transfers



		DMA_DSR_BCR0 |= length2;					//Set the number of byte transfers yet to be transferred( operating in 8-bit for nun-divisible number of words

		DMA_DCR0 |= DMA_DCR_SSIZE(1);				//Set the data size of source bus cycle as 8-bit
		DMA_DCR0 |= DMA_DCR_DSIZE(1);				//Set the data size of destination bus cycle as 8-bit

		#ifdef MEMMOVE
		DMA_DCR0 |= DMA_DCR_SINC_MASK;				//Incrementing source address after each successful transfer
		#endif
		DMA_DCR0 |= DMA_DCR_DINC_MASK;				//Incrementing destination address after each successful transfer
		DMA_DCR0 |= DMA_DCR_EINT_MASK;				//Enabling Interrupts when all the transfers are complete
		NVIC->ISER[0]=0x1;							//Enabling device-specific interrupt in the NVIC interrupt controller.

		DMAMUX0_CHCFG0 &= 0x00;						//Disable DMA MUX Channel 0 before configuring
		DMAMUX0_CHCFG0 |= (DMAMUX_CHCFG_SOURCE(60));					//Routing the DMA source to DMA channel 0 (60th option)
		DMAMUX0_CHCFG0 |= (DMAMUX_CHCFG_ENBL_MASK);	//Enabled the DMA channel 0

		DMA_DCR0 |= DMA_DCR_START_MASK;				//Starting the DMA transfers
	}
}

void DMA0_IRQHandler(void)
{
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;			//Setting off the interrupt
	TPM1_SC &= ~TPM_SC_CMOD(1);			// Stop Counter
	if(DMA_DSR_BCR0 & 0x07000000)
	{
		LOG_0("\r\nError\r\n");
	}
	float val_count=0;
	float timer_clk=0;
	val_count= TPM1_CNT;
	timer_clk= val_count/T1CLK;			// Execution time


#ifdef SIZE8
#ifdef MEMMOVE
	LOG_2("\r\nExecution time for memmove_dma8:\r\n",timer_clk);
#endif

#ifdef MEMZERO
	LOG_2("\r\nExecution time for memzero_dma8:\r\n",timer_clk);
#endif
#endif

#ifdef SIZE32
#ifdef MEMMOVE
	LOG_2("\r\nExecution time for memmove_dma32:\r\n",timer_clk);
#endif

#ifdef MEMZERO
	LOG_2("\r\nExecution time for memzero_dma32:\r\n",timer_clk);
#endif
#endif

}

void TPM1_IRQHandler(void)
{
	if(TPM1_SC & TPM_SC_TOF_MASK)
	{
		ov_count++;					//Increment of oveflow
		TPM1_SC &= ~TPM_SC_TOF_MASK;			//clear the tof bit by writing 1
	}
}
