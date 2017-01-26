/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * main.c
 *
 *  Created on: Nov 27, 2016
*/



#include "MKL25Z4.h"
#include "adc.h"
#include "log.h"
#include "uart.h"
#include "rtc.h"
#include "i2c.h"
#include "dma.h"
#include "profiler.h"
#include <stdint.h>

//#define light_sensor
//#define temp_sensor
//#define noise_sensor
//#define rtc_timer
#define eeprom_test

extern int seconds,minutes,onesecond,hours;
uint8_t interrupt = 0;
int i,j;

int main (void)
{
uint16_t result;
uint16_t result_TEMP;
uint16_t result_LDR;
uint32_t average_result_TEMP=0;
float voltage_TEMP = 0.0;
float temperature = 0.0;

#ifdef ADC_test
/*Configure ADC0 */
ADC0_init();

//Calibrating the adc module
ADC0_calibrate();
#endif

uart_init(baud);
LOG_0("\r\nFINAL DEMO\r\n");

while (1)
	{
		//ADC0_calibrate();
#ifdef light_sensor
		ADC0_SC1A = 14; /* start conversion on channel 14 for LDR*/

		/* wait for COCO */
		while(!(ADC0_SC1A & 0x80)) { }

		/* read conversion result and clear COCO flag */
		result = ADC0_RA;

		//Logging the result
		LOG_2("\n\rADC value of light sensor is :",(uint16_t)result);
#endif

#ifdef temp_sensor
		while(1)
		{
			ADC0_SC1A = 14; /* start conversion on channel 14 for temp sensor*/
			/* wait for COCO */
			while(!(ADC0_SC1A & 0x80)) { }
			/* read conversion result and clear COCO flag */
			result_TEMP = ADC0_RA;
			/*Taking an average */
			average_result_TEMP = mean_filter(result_TEMP);

			if(average_result_TEMP!=0){
				voltage_TEMP = (average_result_TEMP/65536.0) * 3.3;
				temperature = (voltage_TEMP - 0.5)/0.01;
				//Logging the result
				LOG_1("\n\rADC value of temp sensor is :",(uint16_t)average_result_TEMP);
				LOG_2("\n\rTemperature is :",temperature);
				break;
			}
		}
#endif

#ifdef noise_sensor
		ADC0_SC1A = 14; 			/* start conversion on channel 14 for temp sensor*/
		/* wait for COCO */
		while(!(ADC0_SC1A & 0x80)) { }
		/* read conversion result and clear COCO flag */
		result = ADC0_RA;
		LOG_2("\n\rADC value of noise sensor is :",(uint16_t)result);
#endif

#ifdef rtc_timer
		rtc_Clock_Configuration();
		rtc_init();
		setAlarm(1,50);
		LOG_0("\r\nALARM");
		LOG_1(":",1);
		LOG_1(":",50);
		LOG_0("\r\n");
		while(1){
				if(onesecond ==1){
						LOG_1("\r",hours);
						LOG_1(" : ",minutes);
						LOG_1(" : ",seconds);
						onesecond = 0;
						}
			}
#endif

#ifdef eeprom_test
		uint8_t result_data[10],dest[10];
		I2C_init();
		profiler();
		for(i=0;i<10;i++)
		{
		I2C_WriteRegister(0xA0,0x55+i,0x55+i);
		result_data[i]=I2C_ReadRegister(0xA0,0x55+i);
		LOG_1("\r\nRESULT:",result_data[i]);
		}
		memmove_dma8(result_data,dest,10);
#endif
	}
}
