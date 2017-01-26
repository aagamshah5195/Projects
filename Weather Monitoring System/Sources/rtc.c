/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * rtc.c
 *
 *  Created on: Dec 3, 2016
 * This file contains RTC clock setup
 * It consits of RTC clock configuration and initialization
 * RTC clocks and timer are configured and interrupt is generated after every second
 * 32 khz clock is essential to run RTC
 * In addition to that alarm setup is provided as an additional feature
 */

#include"MKL25Z4.h"
#include"rtc.h"
#include "uart.h"
#include "log.h"

int seconds = 0,alarm = 0,minutes = 0,onesecond=0,hours=0;

int totalAlarmSeconds;

//Function to configure clock setup for RTC
void rtc_Clock_Configuration (void)
{
	MCG_C1 |= MCG_C1_IRCLKEN_MASK; //Enable internal reference clock
	MCG_C2 &= ~(MCG_C2_IRCS_MASK);  //Internal Reference Clock -->Slow

	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	//**RTC_CLKIN**//
	PORTC_PCR1 |= (PORT_PCR_MUX(1));       //PTC1 as RTC_CLKIN
	SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0b10);  //32 Khz clock source for RTC

	//**32KHz Frequency**//
	SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b100); //Clockout pin --> 32 KHz

	PORTC_PCR3 |= PORT_PCR_MUX(5); //PTC3 as CLKOUT
}

//Function to initialize RTC
void rtc_init(void)
{
    /*enable the clock to SRTC module register space*/
	SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

	/*Clear Registers, reset All RTC registers*/
    RTC_CR  = RTC_CR_SWR_MASK;
    RTC_CR  &= ~RTC_CR_SWR_MASK;

    if (RTC_SR & RTC_SR_TIF_MASK){
        RTC_TSR = 0x00000000;   //  this action clears the TIF
    }

    /*Set time compensation parameters*/
    RTC_TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);

    NVIC_EnableIRQ(RTC_Seconds_IRQn);
    /*Enable Seconds Interrupt*/
    RTC_IER |= RTC_IER_TSIE_MASK; //Seconds interrupt enable

    /*Timer enable*/
    RTC_SR |= RTC_SR_TCE_MASK;

}

/*Function to set alarm
 * Parameters: minutes and seconds as a user input to set the alarm
 */
void setAlarm(int alarmMinutes, int alarmSeconds){
	totalAlarmSeconds = alarmMinutes*60 + alarmSeconds;
    RTC_TAR = totalAlarmSeconds;
    NVIC_EnableIRQ(RTC_IRQn);
    /*Enable Alarm Interrupt*/
    RTC_IER |= RTC_IER_TAIE_MASK; //Alarm interrupt enable

}

void RTC_Seconds_IRQHandler(void)
{
	onesecond = 1;
	seconds = RTC_TSR;
	if (seconds >59)
	{
		 minutes++;
		 RTC_SR &= ~RTC_SR_TCE_MASK;
		 RTC_TSR = 0x00; //Reset counter
		 seconds = RTC_TSR;
		 RTC_SR |= RTC_SR_TCE_MASK;
		 int alarmTime = RTC_TAR;
		 RTC_TAR = alarmTime - 60;
	}
	if(minutes > 59)
	{
		hours++;
		minutes =0;
	}
}

void RTC_IRQHandler(void)
{
	LOG_0(" Alarm time!!!!");
	RTC_TAR = totalAlarmSeconds;
}
