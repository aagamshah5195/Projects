/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * MMA8451Q.c
 * This file contains Accelerometer initialization and callibration functions
 * I2c protocol is used to communicate it with microcontroller
 * It is calibrated to get X,Y,Z axis co ordinates to measure the movement
 * To calibrate accelerometer simple offset method is used since it is easy and reliable
 */
#include "MKL25Z4.h"
#include "MMA8451Q.h"
#include "I2C.h"

unsigned char AccData[6];
short Xout_14_bit, Yout_14_bit, Zout_14_bit;
float Xout_g, Yout_g, Zout_g;
char DataReady;
char Xoffset, Yoffset, Zoffset;

/******************************************************************************
* Accelerometer initialization function
*******************************************************************************/
void Accelerometer_Init (void)
{
	unsigned char reg_val = 0;

	//Configure the PTA14 pin (connected to the INT1 of the MMA8451Q) for falling edge interrupts
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;		// Turn on clock to Port A module
	PORTA_PCR14 |= (PORT_PCR_ISF_MASK|		// Clear the interrupt flag
					  PORT_PCR_MUX(0x1)|	// PTA14 is configured as GPIO
					  PORT_PCR_IRQC(0xA));	// PTA14 is configured for falling edge interrupts

	//Enable PORTA interrupt on NVIC
	 NVIC_EnableIRQ(PORTA_IRQn); 	//The function enables a device-specific interrupt in the NVIC interrupt controller.
	 __enable_irq();				//  This function enables IRQ interrupts by clearing the I-bit in the CPSR


	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG2, 0x40);		// Reset all registers to POR values

	do		// Wait for the RST bit to clear
	{
		reg_val = I2C_ReadRegister(MMA845x_I2C_ADDRESS, CTRL_REG2) & 0x40;
	} 	while (reg_val);

	I2C_WriteRegister(MMA845x_I2C_ADDRESS, XYZ_DATA_CFG_REG, 0x00);		// +/-2g range -> 1g = 16384/4 = 4096 counts
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG2, 0x02);		// High Resolution mode
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG1, 0x3D);	// ODR = 1.56Hz, Reduced noise, Active mode
}

/******************************************************************************
* Simple offset calibration
******************************************************************************/

void Calibrate (void)
{
	unsigned char reg_val = 0;

	while (!reg_val)		// Wait for a first set of data
	{
		reg_val = I2C_ReadRegister(MMA845x_I2C_ADDRESS, STATUS_REG) & 0x08;
	}

	I2C_ReadMultiRegisters(MMA845x_I2C_ADDRESS, OUT_X_MSB_REG, 6, AccData);		// Read data output registers 0x01-0x06

	Xout_14_bit = ((short) (AccData[0]<<8 | AccData[1])) >> 2;		// Compute 14-bit X-axis output value
	Yout_14_bit = ((short) (AccData[2]<<8 | AccData[3])) >> 2;		// Compute 14-bit Y-axis output value
	Zout_14_bit = ((short) (AccData[4]<<8 | AccData[5])) >> 2;		// Compute 14-bit Z-axis output value

	Xoffset = Xout_14_bit / 8 * (-1);							// Compute X-axis offset correction value
	Yoffset = Yout_14_bit / 8 * (-1);							// Compute Y-axis offset correction value
	Zoffset = (Zout_14_bit - SENSITIVITY_2G) / 8 * (-1);		// Compute Z-axis offset correction value

	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG1, 0x00);		// Standby mode to allow writing to the offset registers
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, OFF_X_REG, Xoffset);
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, OFF_Y_REG, Yoffset);
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, OFF_Z_REG, Zoffset);
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG3, 0x00);		// Push-pull, active low interrupt
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG4, 0x01);		// Enable DRDY interrupt
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG5, 0x01);		// DRDY interrupt routed to INT1 - PTA14
	I2C_WriteRegister(MMA845x_I2C_ADDRESS, CTRL_REG1, 0x3D);		// ODR = 1.56Hz, Reduced noise, Active mode
}

/******************************************************************************
* PORT A Interrupt handler
******************************************************************************/

void PORTA_IRQHandler()
{
	PORTA_PCR14 |= PORT_PCR_ISF_MASK;			// Clear the interrupt flag
	DataReady = 1;
}



uint8_t getWhoAmI() {
    uint8_t who_am_i = 0;
    who_am_i=I2C_ReadRegister(MMA845x_I2C_ADDRESS,REG_WHO_AM_I);
    return who_am_i;
}

//Function to get X coordinate
float getAccX() {
    return (float)((getAccAxis(REG_OUT_X_MSB))/4096.0);
}

//Function to get Y coordinate
float getAccY() {
    return (float)((getAccAxis(REG_OUT_Y_MSB))/4096.0);
}

//Function to get Z coordinate
float getAccZ() {
    return (float)((getAccAxis(REG_OUT_Z_MSB))/4096.0);
}

//Function to get all coordinates
void getAccAllAxis(float * res) {
    res[0] = getAccX();
    res[1] = getAccY();
    res[2] = getAccZ();
}

//Function to get axis
uint16_t getAccAxis(uint8_t addr) {
    int16_t acc;
    uint8_t res[2];
    res[0]=I2C_ReadRegister(MMA845x_I2C_ADDRESS,addr);
    acc = (res[0] << 6) | (res[1] >> 2);

    if (acc > UINT14_MAX/2)
        acc -= UINT14_MAX;

    return acc;
}


