/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * dac.c
 *
 * Created on: Dec 6, 2016
 * 
 * This file includes DAC initialization and calibration
 * External peripherals(Sensors) are interfaced with FRDM through DAC
 * It gives variable voltage values which are combined and calibrated to obtain a signal wave for desired results
 */

#include "MKL25Z4.h"
#include <stdint.h>
#include "dac.h"


//Function to initialize DAC
void DAC0_init(void) {
SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;	//Enable Port E
PORTE_PCR30 |= PORT_PCR_MUX(0); // Configure it as GPIO
PTC->PDDR |= 0x40000000; //setting as output

SIM_SCGC6 |= SIM_SCGC6_DAC0_MASK; /* clock to DAC module */
DAC0_C1 = 0; /* disable the use of buffer */
DAC0_C0 = DAC_C0_DACEN_MASK | DAC_C0_DACTRGSEL_MASK; /* enable DAC and use software trigger */
}


