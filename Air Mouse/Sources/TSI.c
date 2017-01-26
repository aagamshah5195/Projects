/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/* TSI.c
 * This file includes Capacitive Touch Sensor Interface with FRDM
 * It is also calibrated based on touch intensity and distance from the reference point
 * It is calibrated in a way to accomodate two mouse clicks
 * It measures click sensitivity and distance to check left or right mouse click
 */
#include "MKL25Z4.h"
#include "tsi.h"

//Function to initialize TSI sensor(Capacitive Touch)
void TSISensor(void) {
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;	//Enable clock for Port B
    SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;	//Enable TSI clock

    TSI0->GENCS |= TSI_GENCS_ESOR_MASK;		//Enable end of scan interrupt
    TSI0->GENCS |= TSI_GENCS_MODE(0);		//Set TSI in capacitive sensing mode
    TSI0->GENCS |= TSI_GENCS_REFCHRG(4);	//Set reference osc charge and discharge current value as 8uA
	TSI0->GENCS |= TSI_GENCS_DVOLT(0);		//Set direct voltage as 1.03V
	TSI0->GENCS |= TSI_GENCS_EXTCHRG(7);	//Set electrode osc charge and discharge current value as 64uA
	TSI0->GENCS |= TSI_GENCS_PS(4);			//Set prescaler /16
	TSI0->GENCS |= TSI_GENCS_NSCN(11);		//Scan number 12==>NSCN+1
	TSI0->GENCS |= TSI_GENCS_TSIIEN_MASK;	//TSI mode enabled
	TSI0->GENCS |= TSI_GENCS_STPE_MASK;		//TSI in low power mode

    TSI0->GENCS |= TSI_GENCS_TSIEN_MASK;	//Enable interrupt

    NVIC_EnableIRQ(TSI0_IRQn);	//Enable NVIC TSI interrupt

    selfCalibration();
}

//This function callibrates TSI sensor outputs
void selfCalibration(void)
{
    unsigned char cnt;
    unsigned char trigger_backup;

    TSI0->GENCS |= TSI_GENCS_EOSF_MASK;      // Clear End of Scan Flag
    TSI0->GENCS &= ~TSI_GENCS_TSIEN_MASK;    // Disable TSI module

    if(TSI0->GENCS & TSI_GENCS_STM_MASK)     // Back-up TSI Trigger mode from Application
        trigger_backup = 1;
    else
        trigger_backup = 0;

    TSI0->GENCS &= ~TSI_GENCS_STM_MASK;      // Use SW trigger
    TSI0->GENCS &= ~TSI_GENCS_TSIIEN_MASK;    // Enable TSI interrupts

    TSI0->GENCS |= TSI_GENCS_TSIEN_MASK;     // Enable TSI module

    for(cnt=0; cnt < total_electrode; cnt++)  // Get Counts when Electrode not pressed
    {
        TSI0->DATA = ((elec_array[cnt] << TSI_DATA_TSICH_SHIFT) );
        TSI0->DATA |= TSI_DATA_SWTS_MASK;
        while(!(TSI0->GENCS & TSI_GENCS_EOSF_MASK));
        TSI0->GENCS |= TSI_GENCS_EOSF_MASK;
        gu16Baseline[cnt] = (TSI0->DATA & TSI_DATA_TSICNT_MASK);
    }

    TSI0->GENCS &= ~TSI_GENCS_TSIEN_MASK;    // Disable TSI module
    TSI0->GENCS |= TSI_GENCS_TSIIEN_MASK;     // Enale TSI interrupt
    if(trigger_backup)                      // Restore trigger mode
        TSI0->GENCS |= TSI_GENCS_STM_MASK;
    else
        TSI0->GENCS &= ~TSI_GENCS_STM_MASK;

    TSI0->GENCS |= TSI_GENCS_TSIEN_MASK;     // Enable TSI module

    TSI0->DATA = ((elec_array[0]<<TSI_DATA_TSICH_SHIFT) );
    TSI0->DATA |= TSI_DATA_SWTS_MASK;
}

//Function to calculate where it is touched on the sensor
void sliderRead(void) {
    if(end_flag) {
        end_flag = 0;
        if((gu16Delta[0] > gu16Threshold[0])||(gu16Delta[1] > gu16Threshold[1])) {
            SliderPercentegePosition[0] = (gu16Delta[0]*100)/(gu16Delta[0]+gu16Delta[1]);
            SliderPercentegePosition[1] = (gu16Delta[1]*100)/(gu16Delta[0]+gu16Delta[1]);
            SliderDistancePosition[0] = (SliderPercentegePosition[0]* SLIDER_LENGTH)/100;
            SliderDistancePosition[1] = (SliderPercentegePosition[1]* SLIDER_LENGTH)/100;
            AbsolutePercentegePosition = ((100 - SliderPercentegePosition[0]) + SliderPercentegePosition[1])/2;
            AbsoluteDistancePosition = ((SLIDER_LENGTH - SliderDistancePosition[0]) + SliderDistancePosition[1])/2;
         } else {
            SliderPercentegePosition[0] = NO_TOUCH;
            SliderPercentegePosition[1] = NO_TOUCH;
            SliderDistancePosition[0] = NO_TOUCH;
            SliderDistancePosition[1] = NO_TOUCH;
            AbsolutePercentegePosition = NO_TOUCH;
            AbsoluteDistancePosition = NO_TOUCH;
         }
    }
}

//Function to calculate the intensity of touch
float readPercentage() {
    sliderRead();
    return (float)AbsolutePercentegePosition/100.0;
}

//Function to calculate the distance from which it is burnt
uint8_t readDistance() {
    sliderRead();
    return AbsoluteDistancePosition;
}


static void changeElectrode(void)
{
    int16_t u16temp_delta;

    gu16TSICount[ongoing_elec] = (TSI0->DATA & TSI_DATA_TSICNT_MASK);          // Save Counts for current electrode
    u16temp_delta = gu16TSICount[ongoing_elec] - gu16Baseline[ongoing_elec];  // Obtains Counts Delta from callibration reference
    if(u16temp_delta < 0)
        gu16Delta[ongoing_elec] = 0;
    else
        gu16Delta[ongoing_elec] = u16temp_delta;

    //Change Electrode to Scan
    if(total_electrode > 1)
    {
        if((total_electrode-1) > ongoing_elec)
            ongoing_elec++;
        else
            ongoing_elec = 0;

        TSI0->DATA = ((elec_array[ongoing_elec]<<TSI_DATA_TSICH_SHIFT) );
        TSI0->DATA |= TSI_DATA_SWTS_MASK;
    }
}


void TSI0_IRQHandler(void)
{
    end_flag = 1;
    TSI0->GENCS |= TSI_GENCS_EOSF_MASK; // Clear End of Scan Flag
    changeElectrode();
}








