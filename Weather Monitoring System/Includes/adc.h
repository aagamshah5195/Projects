/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * adc.h
 *
 *  Created on: Nov 27, 2016
 */

#ifndef ADC_H_
#define ADC_H_


//This function initializes the ADC module
 void ADC0_init(void);

 //function to calibrate the ADC module
 int ADC0_calibrate(void);

 //function to calculate mean of samples
 int mean_filter(uint32_t result);

#endif /* ADC_H_ */
