/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * Air Mouse Control using FRDM KL25Z
 * main.c
 */
#include "MKL25Z4.h"
#include "MMA8451Q.h"
#include "I2C.h"
#include "log.h"
#include "uart.h"
#include "tsi.h"
#include "usb.h"

//#define acc_test
//#define touch_test
#define mouse

#define false 0
#define true 0
extern unsigned char AccData[6];
extern short Xout_14_bit, Yout_14_bit, Zout_14_bit;
extern float Xout_g, Yout_g, Zout_g;
extern char DataReady;
extern char Xoffset, Yoffset, Zoffset;
static int i = 0;

/******************************************************************************
* Main
******************************************************************************/

int main (void)
{
#ifdef acc_test
	DataReady = 0;
	I2C_init();
	uart_init(38400);
  	Accelerometer_Init();
  	Calibrate();
  	RGB_init();

  	while(1)
    {
		if (DataReady)		// Is a new set of data ready?
		{
			DataReady = 0;

			I2C_ReadMultiRegisters(MMA845x_I2C_ADDRESS, OUT_X_MSB_REG, 6, AccData);		// Read data output registers 0x01-0x06

			Xout_14_bit = ((short) (AccData[0]<<8 | AccData[1])) >> 2;		// Compute 14-bit X-axis output value
			Yout_14_bit = ((short) (AccData[2]<<8 | AccData[3])) >> 2;		// Compute 14-bit Y-axis output value
			Zout_14_bit = ((short) (AccData[4]<<8 | AccData[5])) >> 2;		// Compute 14-bit Z-axis output value

			Xout_g = ((float) Xout_14_bit) / SENSITIVITY_2G;		// Compute X-axis output value in g's
			Yout_g = ((float) Yout_14_bit) / SENSITIVITY_2G;		// Compute Y-axis output value in g's
			Zout_g = ((float) Zout_14_bit) / SENSITIVITY_2G;		// Compute Z-axis output value in g's

			LOG_1("\r\nX-Axis:",Xout_g);
			LOG_1("\r\nY-Axis:",Yout_g);
			LOG_1("\r\nZ-Axis:",Zout_g);
			if(Zout_g==-1||Zout_g==1)
				{B(0);G(0);R_ON;}
			if(Yout_g==-1||Yout_g==1)
				{R(0);B(0);G_ON;}
			if(Xout_g==-1||Xout_g==1)
				{R(0);G(0);B_ON;}
			Pause(100);
		}
	}
#endif
#ifdef touch_test
  	float a=0;
  		uint8_t b =0;
  		uart_init(38400);
  		TSISensor();
  		while(1){
  			a= readPercentage();
  			b= readDistance();
  			LOG_2("\r\nPercent:",a);
  			LOG_2("\r\nDistance:",b);

  		}
#endif
#ifdef mouse
  			Accelerometer_Init();
  		  	Calibrate();
  		  	int TSI_Pressed = false;
  		    int ButtonPressed = 0; //1=MOUSE_LEFT 2=MOUSE_RIGHT 4=MOUSE_MIDDLE
  		    unsigned int TSI_Press_Time = 0;

  		    while (true) {
  		        if (readPercentage() < 0.01) { //TSI left
  		            if (TSI_Pressed == true) {
  		                if (TSI_Press_Time < 250) {
  		                    if (ButtonPressed == 1) {
  		                        click(MOUSE_LEFT);
  		                    }
  		                    else if (ButtonPressed == 2) {
  		                        click(MOUSE_RIGHT);
  		                    }
  		                    else if (ButtonPressed == 4) {
  		                        click(MOUSE_MIDDLE);
  		                    }
  		                }
  		                TSI_Pressed = false;
  		                TSI_Press_Time = 0;
  		            }
  		        }
  		        else if (readPercentage() < 0.25) { //TSI centre
  		            if (TSI_Pressed == false) {
  		                TSI_Pressed = true;
  		                ButtonPressed = 2;
  		            }
  		        }
  		        else if (readPercentage() < 0.5) { //TSI middle
  		            if (TSI_Pressed == false) {
  		                TSI_Pressed = true;
  		                ButtonPressed = 4;
  		            }
  		        }
  		        else {
  		            if (TSI_Pressed == false) {
  		                TSI_Pressed = true;
  		                ButtonPressed = 1;
  		            }
  		        }
  		        if (TSI_Pressed == true) {
  		            TSI_Press_Time++;
  		        }
  		        float AccY = getAccX();
  		        float AccX = getAccY();
  		        signed char x = AccX * -10;
  		        signed char y = AccY * 10;
  		        move(x, y);
  		    }
#endif
}
