/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * adc.c
 *
 *  Created on: Nov 27, 2016
 *
 * This file includes ADC initialization and calibration
 * External peripherals(Sensors) are interfaced with FRDM through ADC
 * It gives variable voltage values which are sampled and calibrated to obtain desired results
 * Mean filter is used to obtain mean value of 50 samples for temperature output
 */
#include "MKL25Z4.h"
#include "adc.h"

uint8_t index = 0;
uint32_t avg_result;

//This function initializes the ADC module
void ADC0_init(void)
{
SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; /* clock to PORTC */
PORTC_PCR0 = 0;  /* PTC0 analog input for LDR */
PORTC_PCR5 = 0;  /* PTC5 analog input for Noise */
PORTC_PCR6 = 0;  /* PTC6 analog input for Temperature */

/* clock to ADC0 */
SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;
/* software trigger */
ADC0_SC2 &= ~ADC_SC2_ADTRG_MASK;
/* clock div by 4, long sample time, single ended 16 bit, bus clock */
ADC0_CFG1 = ADC_CFG1_ADIV(2) | ADC_CFG1_ADLSMP_MASK | ADC_CFG1_MODE_MASK | ADC_CFG1_ADICLK(0) ;
}

//function to calibrate the ADC module
int ADC0_calibrate(void)
{
	ADC0_CFG1 |= (ADC_CFG1_MODE(3)  |  	// 16 bits mode
				  ADC_CFG1_ADICLK(1)|	// Input Bus Clock divided by 2 (20-25 MHz out of reset (FEI mode) / 2)
				  ADC_CFG1_ADIV(2)) ;	// Clock divide by 4 (2.5-3 MHz)

	ADC0_SC3 |= ADC_SC3_AVGE_MASK |		// Enable HW average
				ADC_SC3_AVGS(3)   |		// Set HW average of 32 samples
				ADC_SC3_CAL_MASK;		// Start calibration process

	while(ADC0_SC3 & ADC_SC3_CAL_MASK); // Wait for calibration to end

	if(ADC0_SC3 & ADC_SC3_CALF_MASK)	// Check for successful calibration
		return 1;

	uint16_t calib = 0; // calibration variable
	calib += ADC0_CLPS + ADC0_CLP4 + ADC0_CLP3 + ADC0_CLP2 + ADC0_CLP1 + ADC0_CLP0;
	calib /= 2;
	calib |= 0x8000; 	// Set MSB
	ADC0_PG = calib;
	calib = 0;
	calib += ADC0_CLMS + ADC0_CLM4 + ADC0_CLM3 + ADC0_CLM2 + ADC0_CLM1 + ADC0_CLM0;
	calib /= 2;
	calib |= 0x8000;	// Set MSB
	ADC0_MG = calib;

	return 0;
}

//applies a mean filter on temperature samples
int mean_filter(uint32_t result){

	if(index==0)
		avg_result=0;
	if(index!=50){
		index++;
		avg_result += result;
		return 0;
	}
	else if(index==50){
		index=0;
		avg_result = avg_result/50;
		return (uint16_t)avg_result;
	}
}
