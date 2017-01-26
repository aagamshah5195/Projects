/**************************************************************************//**
 @author:Aagam Shah
 *- IoT Project
 * This is a code for IoT based Smart Plant Monitoring System where different 
 * sensors like Temperature, Light, Soil Moisture etc are interfaced with the
 * Leopard Gecko board using different protocols like I2C, ADC-DMA, LEUART etc.
 * Other modules like Letimer, Analog Comparator etc were also configured in order
 * to get the desired functionality. Realized event-driven firmware design for 
 * load power management using DMA as well as clock optimizations.
 *
 ******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Silicon Labs has no
 * obligation to support this Software. Silicon Labs is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Silicon Labs will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_int.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_letimer.h"
#include "em_gpio.h"
#include "em_acmp.h"
#include "em_timer.h"
#include "em_dma.h"
#include "em_adc.h"
#include "dmactrl.h"
#include "em_i2c.h"
#include "em_leuart.h"
#include "TSL2561.h"

/*Initializing the energy modes*/
#define EM0 0
#define EM1 1
#define EM2 2
#define EM3 3
#define EM4 4

/*Defining GPIO port and pin*/
#define LED0_port gpioPortE					/*LED0 port*/
#define LED0_pin 2							/*LED0 pin*/
#define LED1_port gpioPortE					/*LED1 port*/
#define LED1_pin 3							/*LED1 pin*/
#define LIGHT_EXCITE_port gpioPortD			/*Light_Excite port*/
#define LIGHT_EXCITE_pin 6					/*Light_Excite pin*/
#define LIGHT_SENSE_port gpioPortC			/*Light_Sense port*/
#define LIGHT_SENSE_pin 6					/*Light_Sense pin*/
#define I2C1_SDA_port gpioPortC				/*SDA port*/
#define I2C1_SDA_pin 4						/*SDA pin*/
#define I2C1_SCL_port gpioPortC				/*SCL port*/
#define I2C1_SCL_pin 5						/*SCL pin*/
#define I2C1_Int_port gpioPortD				/*Interrupt Port*/
#define I2C1_Int_pin 1						/*Interrupt Pin*/
#define I2C1_Vdd_port gpioPortD				/*Power port*/
#define I2C1_Vdd_pin 0						/*Power Pin*/
#define I2C1_Write  0						/*write enabled*/
#define I2C1_Read 1							/*read enabled*/

/*Global Variables*/
#define LETIMER0_Energy_Mode EM2
float LETIMER0_on_time= 0.004;           /*in seconds*/
#define LETIMER0_period 6.25               /*in seconds*/
uint32_t LETIMER0_ULFRCO_count= 1000;	/*Count for ULFRCO*/
#define LETIMER0_LFXO_count 32768		/*Count for LFXO*/
uint32_t VDD_ref=2;						/*Reference for the ACMP*/
uint32_t count=0;
uint32_t count1=0;
int count2=0;							/*Count used in ADC0_IRQHandler*/
#define Calib_enable 1					/*To enable or disable the calibration of ULFRCO*/
#define DMA_enable 1					/*To enable or disable the DMA*/
#define Passive_lightsensor_enable 0	/*To enable or disable the on board passive light sensor*/

#define sign  67						/*Transmitting a random number to indicate presence or absence of - sign*/
#define positive 'a'					/*Transmitting 'a' through LEUART0 indicating positive temperature values*/
#define negative 'b'					/*Transmitting 'b' through LEUART0 indicating negative temperature values*/
uint8_t int_average=0;					/*Transmitting integral part of temperature value*/
uint8_t int_average1=0;					/*Transmitting integral part of soil moisture value*/
uint8_t fract_average=0;				/*Transmitting fractional part of temperature value*/
uint8_t fract_average2=0;				/*Transmitting fractional part of soil moisture value*/
uint16_t fract_average_1 = 0;

DMA_CB_TypeDef cb;						/*Structure for call back used in DMA*/
#define DMA_CHANNEL_ADC_TEMP       0			/*Defining the Channel for ADC*/
#define DMA_CHANNEL_ADC_SOIL       3
#define ADCSAMPLES          500		/*No. of ADC Samples*/
uint16_t ramBufferAdcData[ADCSAMPLES];	/*ADC RAM buffer*/
uint16_t ramBufferAdcData1[ADCSAMPLES];	/*ADC RAM buffer*/
#define ADCSAMPLESPERSEC    100000		/*ADC samples per second*/
uint16_t dma_count=0;					/*Count for number of ramBufferAdcData array elements used in DMA*/
uint16_t dma_count1=0;					/*Count for number of ramBufferAdcData array elements used in DMA*/
uint32_t sum= 0;						/*Sum variable used for temperature calculations*/
uint32_t sum1= 0;						/*Sum variable used for soil moisture calculations*/
float average=0;						/*Average variable used for temperature calculations*/
uint16_t average1=0;						/*Average variable used for soil moisture calculations*/

#define LOW_TEMP_LIMIT  15				/*Lower Temperature Threshold*/
#define HIGH_TEMP_LIMIT 35				/*Higher Temperature Threshold*/
bool transferActive;					/*This FLAG indicates whether the transfer is complete or not*/

uint32_t period =1;						/*This is for indicating which stage of the period is it in the LETIMER interrupt handler*/


/*Sleep mode counter*/
unsigned int sleep_counter[EM4+1];


/*Initializing all the setup routines*/
void sleep(void);
void BlockSleepMode(unsigned int minmode);
void UnblockSleepMode(unsigned int minmode);
void CMU_setup(void);
void GPIO_setup(void);
void ACMP_setup(void);
void TIMER0_setup(void);
void LETIMER0_setup(void);
void LED_ON(bool state);
void calibrate(void);
void ADC_setup(void);
void DMA_setup(void);
float TempConvert(float sample);
void Callback(unsigned int channel, bool primary, void *user);
void I2C_setup(void);
void I2C_write(uint8_t Addr,uint8_t Data);
void I2C_sensor(void);
uint16_t I2C_read(uint8_t addr);
void stabilisation(void);
void Leuart_setup(void);


/**************************************************************************//**
 * @brief Sleep Routine
 * To make the MCU sleep in different energy modes - code used from the silicon labs
 *
 *****************************************************************************/
void sleep(void){
	if(sleep_counter[0]>0){
		return;								/*Blocked all energy modes below EM0*/
	}
	else if(sleep_counter[1]>0){
		EMU_EnterEM1();						/*Blocked all energy modes below EM1 and Enter EM1*/
	}
	else if(sleep_counter[2]>0){
		EMU_EnterEM2(true);					/*Blocked all energy modes below EM2 and Enter EM2*/
	}
	else if(sleep_counter[3]>0){
		EMU_EnterEM3(true);					/*Blocked all energy modes below EM3 and Enter EM3*/
	}
	else{
		EMU_EnterEM4();						/*Enter EM4*/
	}
}

void BlockSleepMode(unsigned int minmode){				/*Setting the appropriate Energy mode and blocking the modes under that*/
	INT_Disable();
	sleep_counter[minmode]++;
	INT_Enable();
}

void UnblockSleepMode(unsigned int minmode){			/*Releasing the blocks under the given energy mode*/
	INT_Disable();
	if(sleep_counter[minmode]>0){
		sleep_counter[minmode]--;
	}
	else{
		sleep_counter[minmode]=0;
	}
	INT_Enable();
}


/**************************************************************************//**
 * @brief CMU_setup() Routine : Selecting/enabling the Timer, GPIO ,Clocks,
 * Selecting the required Oscillator, Selecting LETIMR0 Clock
 ******************************************************************************/
void CMU_setup(){
	/*Set up the high frequency oscillator*/
	CMU_HFRCOBandSet(cmuHFRCOBand_14MHz);
	CMU_ClockSelectSet(cmuClock_HF,cmuSelect_HFRCO);		/*Set HFRCO as HF system clock*/
	CMU_OscillatorEnable(cmuOsc_HFXO,false,false);			/*Disabling HF crystal oscillator in order to save energy*/
	CMU_ClockEnable(cmuClock_HFPER,true);					/*Enabling the HF peripheral clock*/

	/*Enable Low Frequency oscillator for low frequency peripherals*/
	CMU_OscillatorEnable(cmuOsc_LFXO,true,true);
	if(LETIMER0_Energy_Mode==EM3){
		CMU_ClockSelectSet(cmuClock_LFA,cmuSelect_ULFRCO);		/*Selecting ULFRCO clock*/
		//CMU_ClockSelectSet(cmuClock_LFB,cmuSelect_LFRCO);		/*Selecting the LFXO clock*/
		CMU_OscillatorEnable(cmuOsc_LFXO,false,false);			/* Disabling LFXO oscillator*/
	}
	else{
		CMU_ClockSelectSet(cmuClock_LFA,cmuSelect_LFXO);		/*Selecting the LFXO clock*/

	}
	//CMU_ClockSelectSet(cmuClock_LFA,cmuSelect_LFXO);		/*Selecting the LFXO clock*/
	//CMU_ClockSelectSet(cmuClock_LFB,cmuSelect_LFXO);		/*Selecting the LFXO clock*/
	CMU_ClockEnable(cmuClock_CORELE, true);
	CMU_ClockEnable(cmuClock_LETIMER0, true);					/*Enabling clock for LETIMER*/
	CMU_ClockEnable(cmuClock_GPIO, true);						/*Enabling clock for GPIO*/
	if(Passive_lightsensor_enable==1)
	{
		CMU_ClockEnable(cmuClock_ACMP0,true);					/*Enabling clock for ACMP*/
	}
	CMU_ClockEnable(cmuClock_TIMER0,true);						/*Enabling clock for TIMER0*/
	CMU_ClockEnable(cmuClock_TIMER1,true);						/*Enabling clock for TIMER1*/
	CMU_ClockEnable(cmuClock_ADC0,true);						/*Enabling clock for ADC0*/
	CMU_ClockEnable(cmuClock_DMA,true);							/*Enabling clock for DMA*/
	CMU_ClockEnable(cmuClock_I2C1,true);						/*Enabling clock for I2C1*/

}


/**************************************************************************************//**
 * @brief TIMER0_setup() Routine : Setup andConfigure the parameters of TIMER0 and TIMER1
 *****************************************************************************************/
void TIMER0_setup(void){
	  int iflags0;
	  int iflags1;
	 /* Select TIMER0 parameters */
	  TIMER_Init_TypeDef timerInit0 =
	  {
	    .enable     = false,
	    .debugRun   = true,
	    .prescale   = timerPrescale1,
	    .clkSel     = timerClkSelHFPerClk,
	    .fallAction = timerInputActionNone,
	    .riseAction = timerInputActionNone,
	    .mode       = timerModeUp,
	    .dmaClrAct  = false,
	    .quadModeX4 = false,
	    .oneShot    = false,
	    .sync       = false,
	  };
	  /*Initializing TIMER0*/
	  TIMER_Init(TIMER0, &timerInit0);

	  /* Select TIMER0 parameters */
	  TIMER_Init_TypeDef timerInit1 =
	  	  {
	  	    .enable     = false,
	  	    .debugRun   = true,
	  	    .prescale   = timerPrescale1,
	  	    .clkSel     = timerClkSelCascade,
	  	    .fallAction = timerInputActionNone,
	  	    .riseAction = timerInputActionNone,
	  	    .mode       = timerModeUp,
	  	    .dmaClrAct  = false,
	  	    .quadModeX4 = false,
	  	    .oneShot    = false,
	  	    .sync       = true,
	  	  };
	  /*Initializing TIMER1*/
	  TIMER_Init(TIMER1, &timerInit1);

	  /*Clearing interrupt flags for TIMER0*/
	  iflags0=LETIMER0->IF;
	  LETIMER0->IFC=iflags0;

	  NVIC_EnableIRQ(TIMER0_IRQn); 					/*Enable Interrupts for TIMER0*/

	  /*Clearing interrupt flags for TIMER1*/
	  iflags1=LETIMER0->IF;
	  LETIMER0->IFC=iflags1;

	  BlockSleepMode(EM1);

	  NVIC_EnableIRQ(TIMER1_IRQn);					/*Enable Interrupts for TIMER1*/
	  UnblockSleepMode(EM1);
}

/**************************************************************************//**
 * @brief GPIO_setup routine is to configure the GPIO
 *****************************************************************************/
void GPIO_setup(){
	GPIO_DriveModeSet(LIGHT_EXCITE_port, gpioDriveModeLowest);					/*Driving the excite pin to the lowest drive mode*/
	GPIO_DriveModeSet(LIGHT_SENSE_port, gpioDriveModeLowest);					/*Driving the light_sense to the lowest drive mode*/
	GPIO_DriveModeSet(LED0_port, gpioDriveModeLowest);							/*Driving the LED0 to the lowest drive mode*/
	GPIO_DriveModeSet(LED1_port, gpioDriveModeLowest);							/*Driving the LED1 to the lowest drive mode*/

	GPIO_PinModeSet(LIGHT_EXCITE_port,LIGHT_EXCITE_pin,gpioModePushPull,0);		/*Light_Excite pin is set for pushpull mode*/
	GPIO_PinModeSet(LIGHT_SENSE_port,LIGHT_SENSE_pin,gpioModeDisabled,0);		/*Light_Sense pin is disabled*/
	GPIO_PinModeSet(I2C1_Int_port,I2C1_Int_pin,gpioModeInput,0);				/*Setting up the Interrupt line*/
	GPIO_PinModeSet(I2C1_Vdd_port,I2C1_Vdd_pin,gpioModePushPull,0);				/*Setting up the VDD*/
	GPIO_PinModeSet(LED0_port, LED0_pin, gpioModePushPullDrive, 0);				/*Setting up LED0*/
	GPIO_PinModeSet(LED1_port, LED0_pin, gpioModePushPullDrive, 0);				/*Setting up LED1*/
}


/**************************************************************************//**
 * @brief GPIO_ODD_IRQHandler
 * Interrupt Service Routine (ISR) for GPIO
 *****************************************************************************/
void GPIO_ODD_IRQHandler(void)
{
	INT_Disable();
	uint16_t value;

	uint32_t flags= GPIO->IF;			/* GPIO interrupt flags are cleared*/
	GPIO -> IFC = flags;

	value = I2C_read(0xAC);				/*setting address of word mode or with ADC_DLOW and then reading the light readings*/

	if(value < 15)
	{
		LED_ON(true);					/*LED on when ambient light is dark*/
	}
	if(value > 2048)
	{
		LED_ON(false);					/*LED off when ambient light is bright*/
	}
	INT_Enable();
}


/**************************************************************************//**
 * @brief  I2C_setup routine is to setup the I2C
 *****************************************************************************/
void I2C_setup(void)
{
  /* Initializing the I2C*/
  I2C_Init_TypeDef i2cInit =
  	{
  	  .enable = true,                    /* Enable when init done */
  	  .master = true,                    /* Set to master mode */
  	  .refFreq = 0,                       /* Use currently configured reference clock */
  	  .freq = I2C_FREQ_STANDARD_MAX,   /* Set to standard rate assuring being within I2C spec */
  	  .clhr = i2cClockHLRStandard      /* Set to use 4:4 low/high duty cycle */
  	};

  /* Using PC4 (SDA) and PC5 (SCL) */
  GPIO_PinModeSet(gpioPortC, 5, gpioModeWiredAnd, 1);
  GPIO_PinModeSet(gpioPortC, 4, gpioModeWiredAnd, 1);

  /*Toggling the SCL pin to reset*/
  for (int i = 0; i < 9; i++)
    {
      GPIO_PinModeSet(gpioPortC, 5, gpioModeWiredAnd, 0);
      GPIO_PinModeSet(gpioPortC, 5, gpioModeWiredAnd, 1);
    }

  /* Enable pins at location 1 */
  I2C1->ROUTE = I2C_ROUTE_SDAPEN |
                I2C_ROUTE_SCLPEN |
                (0 << _I2C_ROUTE_LOCATION_SHIFT);

  /* Initializing the I2C1 */
  I2C_Init(I2C1, &i2cInit);

  //check if busy, if busy then abort
  if (I2C1->STATE & I2C_STATE_BUSY)
  {
      I2C1->CMD = I2C_CMD_ABORT;
  }
}

// Delay routine in the load power management
void stabilisation (void)
{
	for(int i =0; i<10000; i++){}
}

/*****************************************************************************************************//**
 * @brief I2C_read(): Function for reading the ambient light sensor values from register of the external TSL2651 sensor
 ********************************************************************************************************/
uint16_t I2C_read(uint8_t addr)
{
	uint8_t address=addr;
	uint8_t data0=0;
	uint8_t data1=0;

	I2C1->TXDATA = (Slave_Address << 1) | I2C1_Write;		//Prime
	I2C1->CMD = I2C_CMD_START;								//Start bit
	I2C1->IFC = I2C_IFC_START;
	while ((I2C1->IF & I2C_IF_ACK)==0);						//Wait for ACK of start bit
	I2C1->IFC = I2C_IFC_ACK;								//Clearing the ACK bit

	I2C1->TXDATA = address;									//Transmit Command Register Address
	while ((I2C1->IF & I2C_IF_ACK)==0);
	I2C1->IFC = I2C_IFC_ACK;

	I2C1->CMD = I2C_CMD_START;								//Repeat Start
	I2C1->TXDATA = (Slave_Address << 1) | I2C1_Read;		//Prime
	while((I2C1->IF & I2C_IF_ACK) == 0);
	I2C1->IFC = I2C_IFC_ACK;
	while ((I2C1->IF & I2C_IF_RXDATAV) ==  0);				//Wait for RXDATAV to be set which indicates the data is valid
	data0= I2C1->RXDATA;									//reading the values for lower register
	I2C1->CMD = I2C_CMD_ACK;								//Sending an ACK
	while ((I2C1->IF & I2C_IF_RXDATAV) ==  0);
	data1= I2C1->RXDATA;									//reading the values for higher register
	I2C1->CMD = I2C_CMD_NACK;								//Sending a NACK

	I2C1->CMD = I2C_CMD_STOP;								//Stop bit
	while ((I2C1->IF & I2C_IF_MSTOP)==0);
	I2C1->IFC = I2C_IFC_MSTOP;
	return (data1*256) + data0;								//Returning the data
}


/*****************************************************************************************************//**
 * @brief I2C_write(): Function for writing values into the registers of external TSL2651 sensor
 ********************************************************************************************************/
void I2C_write(uint8_t Addr,uint8_t Data)
{
	I2C1->TXDATA = (Slave_Address << 1) | I2C1_Write;		//Slave address with write enabled

	I2C1->CMD = I2C_CMD_START;								//Start bit
    I2C1->IFC = I2C_IFC_START;								//check for start flag in IF register and then clear it
	while ((I2C1->IF & I2C_IF_ACK)==0);						//Wait for ACK flag
	I2C1->IFC = I2C_IFC_ACK;								//Clearing the ACK flag

	I2C1->TXDATA = Addr;									//Register address in slave
    while(!(I2C1->IF & I2C_IF_ACK));						//Wait for ACK flag to be set
	I2C1->IFC = I2C_IFC_ACK;								//Clear ACk flag

	I2C1->TXDATA = Data;									//Transmit the value to be written in the register specified in Command register
	while ((I2C1->IF & I2C_IF_ACK)==0);
	I2C1->IFC = I2C_IFC_ACK;

	I2C1->CMD = I2C_CMD_STOP;								//Stop bit
	while ((I2C1->IF & I2C_IF_MSTOP)==0);					//Wait for Master stop flag
	I2C1->IFC = I2C_IFC_MSTOP;								//Clear the Master stop flag

}


/**************************************************************************//**
 * @brief I2C_sensor: Configures the TSL2651 active light sensor
 *****************************************************************************/
void I2C_sensor(void)
{
		INT_Disable();

		//defining persistence to 4
		uint8_t address = 0x86; // interrupt register is being accessed
		uint8_t data = (TSL2651_INTR <<4)|(TSL2651_Persistence_value) ;		//Persistence set to 4
		I2C_write(address, data);	//Calling the write function

		//defining threshold low low register
		address = 0x82; 			// threshold low low register is being accessed
		data = 0x0f;				//setting the value in low low register
		I2C_write(address, data);

		//defining threshold low high register
		address = 0x83; 			// threshold low low register is being accessed
		data = 0x00;				//setting the value in low high register
		I2C_write(address, data);

		//defining threshold high low register
		address = 0x84; 			// threshold high low register is being accessed
		data = 0x00;				//setting the value in high low register
		I2C_write(address, data);

		//defining threshold high high register
		address = 0x85; 			// threshold high high register is being accessed
		data = 0x08;				//setting the value in high high register
		I2C_write(address, data);

		//defining low gain and integration time
		address = 0x81; 			// timing register being accessed
		data = 0x01;   				// Integration time set to 101ms
		I2C_write(address, data);

		I2C_write(CMDbit,0x03);     //writing value on to command register to power up the sensor

		for(int i =0; i<10000; i++)			//Delay
		{}

		INT_Enable();
}


/**************************************************************************//**
 * @brief ADC_setup routine is to setup the ADC
 *****************************************************************************/
void ADC_setup(void)
{
  ADC_Init_TypeDef        adcInit       = ADC_INIT_DEFAULT;
  ADC_InitSingle_TypeDef  adcInitSingle = ADC_INITSINGLE_DEFAULT;
  ADC_InitScan_TypeDef    adcInitScan = ADC_INITSCAN_DEFAULT;

  adcInit.timebase = ADC_TimebaseCalc(0);

  /* Configure ADC single mode to sample Ref/2 */
  adcInit.prescale = ADC_PrescaleCalc((ADCSAMPLESPERSEC*13), 0); /* Set the ADC prescaler */
  ADC_Init(ADC0, &adcInit);

  adcInitSingle.input     =  adcSingleInputTemp;  /* Reference */
  adcInitScan.input       = ADC_SCANCTRL_INPUTMASK_CH3;
  ADC_InitSingle(ADC0, &adcInitSingle);
  ADC_InitScan(ADC0,&adcInitScan);
  ADC0->SINGLECTRL &= 0xFFFFFFFE;
  ADC0->SINGLECTRL |= 0x00000001;					/*Setting the ADC in repetitive mode for DMA*/
  ADC0->SCANCTRL &= 0xFFFFFFFE;
  ADC0->SCANCTRL |= 0x00000001;						/*Setting the ADC in repetitive mode for DMA*/
  if(DMA_enable==0)
  {
	  ADC_IntEnable(ADC0,ADC_IEN_SINGLE);			/*Enabling the ADC interrupts*/
	  NVIC_EnableIRQ(ADC0_IRQn);
	  ADC0->SINGLECTRL &= 0xFFFFFFFE;
	  ADC0->SINGLECTRL |= 0x00000000;				/*Resetting the ADC from the repetitive mode for ADc0_IRQHandler*/
  }
}


/**************************************************************************//**
 * @brief ADC0_IRQHandler
 * Interrupt Service Routine (ISR) for ADC
 *****************************************************************************/
void ADC0_IRQHandler(void)
{
	INT_Disable();
	  count2++;												/*Incremeting the count*/

	  int intflags=0;
	  intflags = ADC0->IF;								/*Clearing the interrupt flags*/
	  ADC0->IFC =intflags;

	  if(count2<ADCSAMPLES)
	  {
		  sum = sum + ADC0->SINGLEDATA;					/*Sum of Temperatures of all 1000 ADC samples*/
	  }
	  else
	  {
	  ADC0->CMD |= ADC_CMD_SINGLESTOP;					/*Stopping the ADC indicating conversion is complete*/


	  average = sum / ADCSAMPLES;						/*Taking the average of 1000 ADC temperature samples*/

      average= TempConvert(average);					/*Determining the actual average temperature in celsius*/
		  if((average > LOW_TEMP_LIMIT) & (average < HIGH_TEMP_LIMIT))						/*If inside the temperature limits turn OFF LED1*/
		  {
			  GPIO_PinOutClear(LED1_port,LED1_pin);
		  }
		  else																				/*If outside the temperature limits turn ON LED1*/
		  {
			  GPIO_PinOutSet(LED1_port,LED1_pin);
		  }
	/* Clearing flag to indicate that transfer is complete */
	transferActive = false;
	  sum=0;													/*Clearing the sum*/
	  count2=0;													/*Clearing the count*/
	  UnblockSleepMode(EM1);
	  }
		INT_Enable();
}


/**************************************************************************//**
 * @brief DMA_setup is to configure DMA for ADC RAM Transfer - the routine declaration
 * is taken from the Silicon labs - Changed the code according to the Assignment Requirements
 *****************************************************************************/
void DMA_setup(void)
{
  DMA_Init_TypeDef        dmaInit;
  DMA_CfgChannel_TypeDef  chnlCfg;
  DMA_CfgDescr_TypeDef    descrCfg;
  DMA_CfgDescr_TypeDef   descrCfg3;
  DMA_CfgChannel_TypeDef chnlCfg3;

  /* Initializing the DMA */
  dmaInit.hprot        = 0;
  dmaInit.controlBlock = dmaControlBlock;
  DMA_Init(&dmaInit);

  /* Setting up call-back function */
  cb.cbFunc  = Callback;
  cb.userPtr = NULL;

  /* Setting up channel */
  chnlCfg.highPri   = false;
  chnlCfg.enableInt = true;
  chnlCfg.select    = DMAREQ_ADC0_SINGLE;
  chnlCfg.cb        = &cb;
  DMA_CfgChannel(DMA_CHANNEL_ADC_TEMP, &chnlCfg);

  /* Setting up channel descriptor */
  descrCfg.dstInc  = dmaDataInc2;
  descrCfg.srcInc  = dmaDataIncNone;
  descrCfg.size    = dmaDataSize2;
  descrCfg.arbRate = dmaArbitrate1;
  descrCfg.hprot   = 0;
  DMA_CfgDescr(DMA_CHANNEL_ADC_TEMP, true, &descrCfg);

  /* Configure DMA channel 3 used */
   chnlCfg3.highPri   = false;
   chnlCfg3.enableInt = true;
   chnlCfg3.select    = DMAREQ_ADC0_SCAN;
   chnlCfg3.cb        = &cb;
   DMA_CfgChannel(DMA_CHANNEL_ADC_SOIL, &chnlCfg3);

   descrCfg3.dstInc  = dmaDataInc2;
   descrCfg3.srcInc  = dmaDataIncNone;
   descrCfg3.size    = dmaDataSize2;
   descrCfg3.arbRate = dmaArbitrate1;
   descrCfg3.hprot   = 0;
   DMA_CfgDescr(DMA_CHANNEL_ADC_SOIL, true, &descrCfg3);

}


/**************************************************************************//**
 * @brief  Callback function called when transfer to the DMA is complete. The routine declaration
 * is taken from silicon labs' sample program. - Changed the code according to the Assignment Requirements
 *****************************************************************************/
void Callback(unsigned int channel, bool primary, void *user)
{
  (void) channel;
  (void) primary;
  (void) user;
  ADC_Start(ADC0,false);
  UnblockSleepMode(EM1);
  if (channel == 0)
  {
  /* Clearing flag to indicate that transfer is complete */
  transferActive = false;

  while(dma_count<ADCSAMPLES)
  {
	  sum=sum + ramBufferAdcData[dma_count];								/*Sum of Temperatures of all 1000 ADC samples*/
	  dma_count++;
  }
	  average = sum / ADCSAMPLES;											/*Average temperature value for 1000 ADC samples*/

	  average= TempConvert(average);
	  //average = -1.6;
	  if(average<0)
	  {
	  	 average=average*(-1);
	  }
	  int_average= (uint8_t)average;
	  if((average > LOW_TEMP_LIMIT) & (average < HIGH_TEMP_LIMIT))			/*If inside the temperature limits turn OFF LED1*/
	  {
		  GPIO_PinOutClear(LED1_port,LED1_pin);
	  }
	  else															/*If outside the temperature limits turn ON LED1*/
	  {
		  GPIO_PinOutSet(LED1_port,LED1_pin);
	  }

  dma_count= 0;
  sum=0;
  //Leuart_setup();
  ADC0->CMD |= ADC_CMD_SINGLESTOP;					/*Stopping the ADC indicating conversion is complete*/
  ADC0->CMD |= ADC_CMD_SCANSTART;					/*Starting the ADC indicating conversion is starting*/
  UnblockSleepMode(EM1);
  DMA_ActivateBasic(DMA_CHANNEL_ADC_SOIL,
          	    	               true,
          	    	               false,
          	    	               (void *)ramBufferAdcData1,
          	    	               (void *)&(ADC0->SCANDATA),
          	    	                ADCSAMPLES - 1);

          transferActive=true;
  BlockSleepMode(EM1);
  }
  if (channel == 3)
  {
	  /* Clearing flag to indicate that transfer is complete */
	    transferActive = false;
	    while(dma_count1<ADCSAMPLES)
	      {
	    	  sum1 = sum1 + ramBufferAdcData1[dma_count1];								/*Sum of Temperatures of all 1000 ADC samples*/
	    	  dma_count1++;
	      }
	    average1 = sum1 / ADCSAMPLES;											/*Average temperature value for 1000 ADC samples*/
	    //int_average1= average1;
	    int_average1= (uint8_t)(average1/100);
	    fract_average2= (uint8_t)(average1%100);
	    dma_count1=0;
	    sum1=0;
	    ADC0->CMD |= ADC_CMD_SCANSTOP;					/*Stopping the ADC indicating conversion is complete*/
	     ADC0->CMD |= ADC_CMD_SINGLESTART;					/*Starting the ADC indicating conversion is starting*/
	    Leuart_setup();
  }
}


/**************************************************************************//**
 * @brief TempConvert is a routine to convert the temperature to celsius
 * The entire routine is from Silicon Labs
 *****************************************************************************/
float TempConvert(float sample)
{
	float temp;
	float cal_temp_0 = (float) ((DEVINFO->CAL & _DEVINFO_CAL_TEMP_MASK)>> _DEVINFO_CAL_TEMP_SHIFT);
	float cal_value_0 = (float) ((DEVINFO->ADC0CAL2 & _DEVINFO_ADC0CAL2_TEMP1V25_MASK)>> _DEVINFO_ADC0CAL2_TEMP1V25_SHIFT);
	float tgrad = -6.27;
	temp = (cal_temp_0 - ((cal_value_0 - sample)/tgrad));
	return temp;
}

/**************************************************************************//**
 * @brief ACMP_setup: Configures the Analog Comparator
 *****************************************************************************/
void ACMP_setup(void)
{
	/*Select ACMP parameters*/
  ACMP_Init_TypeDef acmp_init =
  {
    false,                              /* Full bias current*/
    true,                              /* Half bias current */
    4,                                  /* Biasprog current configuration */
    false,                              /* Enable interrupt for falling edge */
    true,                               /* Enable interrupt for rising edge */
    acmpWarmTime256,                    /* Warm-up time in clock cycles, >140 cycles for 10us with 14MHz */
    acmpHysteresisLevel6,               /* Hysteresis configuration */
    0,                                  /* Inactive comparator output value */
    true,                               /* Enable low power mode */
    VDD_ref,                            /* Vdd reference scaling */
    true,                               /* Enable ACMP */
  };

  /* Initialize and set ACMP channel */
  ACMP_Init(ACMP0, &acmp_init);
  ACMP_ChannelSet(ACMP0, acmpChannelVDD, acmpChannel6);

  ACMP_IntEnable(ACMP0, ACMP_IEN_EDGE);   /* Enable edge interrupt */

  /* Wait for warmup */
  while (!(ACMP0->STATUS & ACMP_STATUS_ACMPACT)) ;

  BlockSleepMode(EM2);

  /* Enable interrupts */
  NVIC_ClearPendingIRQ(ACMP0_IRQn);
  NVIC_EnableIRQ(ACMP0_IRQn);
}

/**************************************************************************//**
 * @brief ACMP0_IRQHandler: Interrupt Service Routine(ISR) for ACMP
 *****************************************************************************/
void ACMP0_IRQHandler(void)
{
	INT_Disable();
  /* Clear interrupt flag */
  ACMP0->IFC = ACMP_IFC_EDGE;
	INT_Enable();

}


/**************************************************************************//**
 * @brief  LETIMER0_setup
 * Configures and starts the LETIMER0
 *****************************************************************************/
void LETIMER0_setup(){
	int Comp0_Init;
	int Comp1_Init;
	int presc;					/*Initialized the prescaler*/
	int flags;
	const LETIMER_Init_TypeDef letimerInit =
	  {
	  .enable         = false,                   /* Start counting when init completed. */
	  .debugRun       = false,                  /* Counter shall not keep running during debug halt. */
	  .rtcComp0Enable = false,                  /* Don't start counting on RTC COMP0 match. */
	  .rtcComp1Enable = false,                  /* Don't start counting on RTC COMP1 match. */
	  .comp0Top       = true,                   /* Load COMP0 register into CNT when counter underflows. COMP0 is used as TOP */
	  .bufTop         = false,                  /* Don't load COMP1 into COMP0 when REP0 reaches 0. */
	  .out0Pol        = 0,                      /* Idle value for output 0. */
	  .out1Pol        = 0,                      /* Idle value for output 1. */
	  .ufoa0          = letimerUFOANone,		/*PWM output on output 0*/
	  .ufoa1          = letimerUFOANone,		/*PWM output on output 1*/
	  .repMode        = letimerRepeatFree       /* Count until stopped */
	  };

	  /* Initialize LETIMER */
	  LETIMER_Init(LETIMER0, &letimerInit);

	  if(LETIMER0_Energy_Mode==EM3)
		  Comp0_Init = LETIMER0_period * LETIMER0_ULFRCO_count;

	  else
	  {
		  Comp0_Init = LETIMER0_period * LETIMER0_LFXO_count;
		  /*Now we will use a prescaler*/
		  presc=LETIMER0_period / 2;
	  	  CMU->LFAPRESC0 &=  0xfffff0ff;
	  	  CMU->LFAPRESC0 |= presc << 8;
	  	  presc= 1 << presc;
		  Comp0_Init = LETIMER0_period * (LETIMER0_LFXO_count / presc);
	  }

	  LETIMER0->CNT = Comp0_Init;			/*Loading the value of Comp0 into Count*/
	  LETIMER_CompareSet(LETIMER0,0,Comp0_Init);

	  if(LETIMER0_Energy_Mode==EM3)
		  Comp1_Init = LETIMER0_on_time * LETIMER0_ULFRCO_count;

	  else
		  //Comp1_Init = LETIMER0_on_time * LETIMER0_LFXO_count;
		  Comp1_Init = LETIMER0_on_time * (LETIMER0_LFXO_count / presc);

	  LETIMER_CompareSet(LETIMER0,1,Comp1_Init);
	  while(LETIMER0->SYNCBUSY!=0);							/*Waiting for LETIMER0 synch bit to be cleared*/

	  flags=LETIMER0->IF;
	  LETIMER0->IFC=flags;

	  LETIMER0->IEN=((LETIMER_IEN_COMP1)|(LETIMER_IEN_UF));		/*Interrupts are enabled either when Comp1 value gets matched or an underflow occurs*/

	  BlockSleepMode(EM3);				/*Setting the appropriate Energy mode and blocking the modes under that*/
	  NVIC_EnableIRQ(LETIMER0_IRQn);
}


/**************************************************************************//**
 * @brief LETIMER0_IRQHandler
 * Interrupt Service Routine (ISR) for LETIMER
 *****************************************************************************/
void LETIMER0_IRQHandler(void)
{

/*Setting the duty cycle and period alternatively on LETIMER*/
 INT_Disable();
 int IntFlags;
 //GPIO_PinOutClear(LED_GPIO_PORT,LED_GPIO_PIN);
 IntFlags=LETIMER0->IF;
 /*Setting the duty cycle and period alternatively on LETIMER*/
 if((IntFlags & LETIMER_IF_COMP1)!=0)
 {
     LETIMER0->IFC=IntFlags;
     if(Passive_lightsensor_enable == 1)// check if passive_lightsense_switch is ON
    {
    ACMP_Enable(ACMP0);
     /* Wait for warm up */
     GPIO_PinOutSet(LIGHT_EXCITE_port, LIGHT_EXCITE_pin);
     while (!(ACMP0->STATUS & ACMP_STATUS_ACMPACT)) ;
    }
 }


 if((IntFlags & LETIMER_IF_UF)!=0)
 {

     LETIMER0->IFC=IntFlags;
     if(Passive_lightsensor_enable == 1)
     {
    	 	 	if(ACMP0->STATUS & ACMP_STATUS_ACMPOUT)
    	 		{
    	 		LED_ON(false);
    	 		ACMP_Disable(ACMP0);

    	 		ACMP0->INPUTSEL &= 0xFFFFC0FF;					/*Clearing only the VDD level bits in INPUTSEL*/
    	 		ACMP0->INPUTSEL |= 0x00000200;					/*Setting the value of 2 for VDD level bits*/

    	 		ACMP_Enable(ACMP0);
    	 		}

    	 		else
    	 		{
    	 		LED_ON(true);
    	 		ACMP_Disable(ACMP0);

    	 		ACMP0->INPUTSEL &= 0xFFFFC0FF;					/*Clearing only the VDD level bits in INPUTSEL*/
    	 		ACMP0->INPUTSEL |= 0x00003D00;					/*Setting the value of 61 for VDD level bits*/

    	 		ACMP_Enable(ACMP0);
    	 		}

    	 		GPIO_PinOutClear(LIGHT_EXCITE_port,LIGHT_EXCITE_pin);	/*Clearing the output pin Light_Excite*/
     }

     if(DMA_enable!=0)
     {
    	 UnblockSleepMode(EM1);
         DMA_ActivateBasic(DMA_CHANNEL_ADC_TEMP,
	    	                       true,
	    	                       false,
	    	                       (void *)ramBufferAdcData,
	    	                       (void *)&(ADC0->SINGLEDATA),
	    	                       ADCSAMPLES - 1);

        transferActive=true;

     }

   /*Blocking the sleep mode to EM1 for ADC*/
     BlockSleepMode(EM1);
   /*Starting ADC Conversion*/
     ADC_Start(ADC0, adcStartSingle);

     if(period==1)													//Period 1
     {																//Power up sequence
     GPIO_PinOutSet(I2C1_Vdd_port, I2C1_Vdd_pin);					//Setting the power pin
     stabilisation();												//Delay routine in power up
     I2C_setup();
     I2C_sensor();

     GPIO_ExtIntConfig(I2C1_Int_port, I2C1_Int_pin,1, false, true, true);			/* Configure PD1 interrupt on falling edge */
     	 	  GPIO->IFC = GPIO->IF;

     	  /* Enable GPIO_ODD interrupt vector in NVIC */
     	  NVIC_EnableIRQ(GPIO_ODD_IRQn);
     }
     else if(period==3)												//Power down sequence
     {
    	 GPIO_ExtIntConfig(I2C1_Int_port, I2C1_Int_pin,1, false, true, false);		//Disabling the TSL2651 interrupt
    	 GPIO_PinOutClear(I2C1_Vdd_port, I2C1_Vdd_pin);							//Clearing the power pin
    	 GPIO->IFC = GPIO->IF;
    	 //period_stage=0;
    	 UnblockSleepMode(EM1);
    	 BlockSleepMode(EM3);

     }

     if(period==3)
     {
    	period=1;
     }
     else
     {
    	 period++;
     }
  }
INT_Enable();
}
/**************************************************************************//**
 * @brief Calibartion routine for the ULFCRO
 ******************************************************************************/
void calibrate(void){
	float ratio = 0;
	CMU_OscillatorEnable(cmuOsc_LFXO,true,true);

	CMU_ClockSelectSet(cmuClock_LFA,cmuSelect_LFXO);

	LETIMER_Init_TypeDef letimerInit =
		  {
		  .enable         = false,                   /* Start counting when init completed. */
		  .debugRun       = false,                  /* Counter shall not keep running during debug halt. */
		  .rtcComp0Enable = false,                  /* Don't start counting on RTC COMP0 match. */
		  .rtcComp1Enable = false,                  /* Don't start counting on RTC COMP1 match. */
		  .comp0Top       = true,                   /* Load COMP0 register into CNT when counter underflows. COMP0 is used as TOP */
		  .bufTop         = false,                  /* Don't load COMP1 into COMP0 when REP0 reaches 0. */
		  .out0Pol        = 0,                      /* Idle value for output 0. */
		  .out1Pol        = 0,                      /* Idle value for output 1. */
		  .ufoa0          = letimerUFOANone,
		  .ufoa1          = letimerUFOANone,
		  .repMode        = letimerRepeatOneshot      /* Count only for one cycle */
		  };

	/*Initializing the LETIMER*/
	LETIMER_Init(LETIMER0, &letimerInit);

	LETIMER0->CNT = LETIMER0_LFXO_count;			/*Loading the count value of LETIMER with LFXO counter value*/
	TIMER0->CNT =0;									/*Resetting the counter for TIMER0*/
	TIMER1->CNT =0;									/*Resetting the counter for TIMER1*/

	TIMER0_setup();									/*Routine call to TIMER0_setup*/
	LETIMER_Enable(LETIMER0,true);
	TIMER_Enable(TIMER0,true);						/*Enabling the TIMER0*/
	TIMER_Enable(TIMER1,true);						/*Enabling the TIMER1*/
	while((LETIMER0->CNT)!=0);						/*Waiting till LETIMER counter comes to 0*/
	count=(((TIMER1->CNT) << 16)|(TIMER0->CNT));	/*In order to use TIMER as a 32-bit counter, we left shift TIMER1 counter by 16 bits and OR it with TIMER0*/

	LETIMER_Enable(LETIMER0,false);					/*Disabling the LETIMER*/
	TIMER_Enable(TIMER0,false);						/*Disabling the TIMER0*/
	TIMER_Enable(TIMER1,false);						/*Disabling the TIMER1*/
	CMU_OscillatorEnable(cmuOsc_LFXO,false,false);
	CMU_OscillatorEnable(cmuOsc_ULFRCO,true,true);
	CMU_ClockSelectSet(cmuClock_LFA,cmuSelect_ULFRCO);
	LETIMER0->CNT = LETIMER0_ULFRCO_count;							/*Loading the count value of LETIMER with ULFRCO counter value*/
	TIMER0->CNT =0;
	TIMER1->CNT =0;
	LETIMER_Init(LETIMER0, &letimerInit);
	TIMER0_setup();
	LETIMER_Enable(LETIMER0,true);

	TIMER_Enable(TIMER0,true);
	TIMER_Enable(TIMER1,true);

	while((LETIMER0->CNT)!=0);

	count1= ((TIMER1->CNT) << 16)|(TIMER0->CNT);				/*In order to use TIMER as a 32-bit counter, we left shift TIMER1 counter by 16 bits and OR it with TIMER0*/

	ratio = (float)count /(float) count1;						/*ratio of LFXOcount to the ULFRCO count used for calibration of ULFRCO*/
	LETIMER0_ULFRCO_count= LETIMER0_ULFRCO_count *ratio;		/*Multiplying the ratio to the count value to calibrate ULFRCO*/
	LETIMER0_on_time= LETIMER0_on_time *ratio;
	TIMER_Enable(TIMER0,false);									/*Disabling the TIMER0*/
	TIMER_Enable(TIMER1,false);									/*Disabling the TIMER1*/
	LETIMER_Enable(LETIMER0,false);								/*Disabling the LETIMER*/
}


/**************************************************************************//**
 * @brief LED_ON Routine – For turning ON/OFF the LED depending upon the LED Status
 *****************************************************************************/
void LED_ON(bool state){

	if(state)
		GPIO_PinOutSet(LED0_port,LED0_pin);						/*Switching on the LED*/
	else
		GPIO_PinOutClear(LED0_port,LED0_pin);					/*Switching off the LED*/
}

void Leuart_setup(void)
{
	if(LETIMER0_Energy_Mode==EM3){
		CMU_OscillatorEnable(cmuOsc_LFRCO,true,true);
		CMU_ClockSelectSet(cmuClock_LFB,cmuSelect_LFRCO);		/*Selecting the LFRCO clock*/
	}
	else
	{
		CMU_ClockSelectSet(cmuClock_LFB,cmuSelect_LFXO);		/*Selecting the LFXO clock*/
	}
	CMU_ClockEnable(cmuClock_LEUART0,true);						/*Enabling clock for LEUART0*/

	int intr_flags;

	intr_flags= LEUART0->IF;
	LEUART0->IFC = intr_flags;

  /* Defining the LEUART1 initialization data */
  LEUART_Init_TypeDef leuart1Init =
  {
    .enable   = leuartEnableTx,       /* Activate data reception on LEUn_TX pin. */
    .refFreq  = 0,                    /* Inherit the clock frequenzy from the LEUART clock source */
    .baudrate = 9600,                 /* Baudrate = 9600 bps */
    .databits = leuartDatabits8,      /* Each LEUART frame containes 8 databits */
    .parity   = leuartNoParity,       /* No parity bits in use */
    .stopbits = leuartStopbits1,      /* Setting the number of stop bits in a frame to 2 bitperiods */
  };

  /* Reseting and initializing LEUART1 */
  LEUART_Reset(LEUART0);
  LEUART_Init(LEUART0, &leuart1Init);

  /* Enable GPIO for LEUART0. TX is on D4 */
    GPIO_PinModeSet(gpioPortD,                 //GPIO port
                    4,                         //GPIO port number
                    gpioModePushPull,          //Pin mode is set to push pull
                    1);                        //High idle state

   /* Enable Loopback */
   LEUART0->CTRL |= LEUART_CTRL_LOOPBK;
   /* Enable Auto Tri state */
   LEUART0->CTRL |= LEUART_CTRL_AUTOTRI;

   /* Route LEUART1 TX pin to DMA location 0 */
   LEUART0->ROUTE = LEUART_ROUTE_TXPEN |
                   LEUART_ROUTE_LOCATION_LOC0;

   while (LEUART0->SYNCBUSY) { }

  LEUART_IntEnable(LEUART0,LEUART_IEN_TXBL);			/*Enabling the ADC interrupts*/
  NVIC_EnableIRQ(LEUART0_IRQn);
}

void LEUART0_IRQHandler(void)
{
	INT_Disable();
	uint8_t flags = LEUART0->IF;
	LEUART0->IFC = flags;

	LEUART0->IEN &= ~LEUART_IEN_TXBL;
		//int i;
		/* Enable Transmission*/
		LEUART0->CMD |= LEUART_CMD_TXEN;
		LEUART0->CMD |= LEUART_CMD_RXEN;

		LEUART0->TXDATA = int_average;
		while((LEUART0->IF & LEUART_IF_TXC)==0);
		flags = LEUART0->IF;
		LEUART0->IFC = flags;

		fract_average_1 = average * 10;
		fract_average = fract_average_1 % 10;
		LEUART0->TXDATA = fract_average;
		while((LEUART0->IF & LEUART_IF_TXC)==0);
		flags = LEUART0->IF;
		LEUART0->IFC = flags;
		//average=0;
		if(GPIO_PinInGet(LED0_port,LED0_pin) == 1)
		{
			LEUART0->TXDATA = positive;
			while((LEUART0->IF & LEUART_IF_TXC)==0);
			flags = LEUART0->IF;
			LEUART0->IFC = flags;
		}
		if(GPIO_PinInGet(LED0_port,LED0_pin) == 0)
		{
			LEUART0->TXDATA = negative;
			while((LEUART0->IF & LEUART_IF_TXC)==0);
			flags = LEUART0->IF;
			LEUART0->IFC = flags;
		}
		LEUART0->TXDATA = sign;
		while((LEUART0->IF & LEUART_IF_TXC)==0);
		flags = LEUART0->IF;
		LEUART0->IFC = flags;

		LEUART0->TXDATA = int_average1;
		while((LEUART0->IF & LEUART_IF_TXC)==0);
		flags = LEUART0->IF;
		LEUART0->IFC = flags;

		LEUART0->TXDATA = fract_average2;
		while((LEUART0->IF & LEUART_IF_TXC)==0);
		flags = LEUART0->IF;
		LEUART0->IFC = flags;

		//average1=0;
		LEUART0->CMD |= LEUART_CMD_TXDIS;
		INT_Enable();
}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
	CHIP_Init();
	BlockSleepMode(LETIMER0_Energy_Mode);
	CMU_setup();												/*Calling the CMU setup routine*/
	GPIO_setup();												/*Calling the GPIO setup routine*/
	if(Calib_enable==1)
	{
		calibrate();												/*Calling the calibration routine*/
	}
	CMU_setup();
	ADC_setup();												/*Calling the ADC setup routine*/
	ADC0->CMD |= ADC_CMD_SINGLESTOP;
	if(DMA_enable==1)
	{
	DMA_setup();												/*Calling the DMA setup routine*/
	}
	LETIMER0_setup();											/*Calling the LETIMER setup routine*/
	BlockSleepMode(LETIMER0_Energy_Mode);
	if(Passive_lightsensor_enable == 1)
	ACMP_setup();												/*Calling the ACMP setup routine*/

	LETIMER_Enable(LETIMER0,true);
	while(1){
		if(DMA_enable==0 && count2>0 && count2<ADCSAMPLES)
		ADC0->CMD |= ADC_CMD_SINGLESTART;						/*Keeping the ADC conversions on till all ADC samples are done*/
		sleep();
	}
}
