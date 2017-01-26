/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/
/*
 * nordic.c
 * Created on: Nov 1, 2016
 * This file contains nordic functions for FRDM.
 * It includes reading and writing data in the nordic register and monitoring the status.
 *
 */
#include"main.h"

static int i;

#define RF_CHANNEL 2
#define PAYLOAD_SIZE 1//payload size
uint8_t payload[PAYLOAD_SIZE];  // payload data
uint8_t TX_address[5] = {0XE7, 0XE7, 0XE7, 0XE7, 0XE7};


//function to configure nordic
void nrf_config()
{
	uint8_t status;
	nrf_write_register(NORDIC_CONFIG_BASE,NORDIC_POWER_UP_MASK);	// Writing in Config for Using it in RX mode and Power up
	status=nrf_read_register(NORDIC_CONFIG_BASE);					// Reading Config Reg
	if(status==NORDIC_POWER_UP_MASK)								// LED control to verify it is able to write the value
			{
				RGB_init();
				R_ON;B_ON;G_ON;
			}
	LOG_1("Status:",status);										// Uart control to verify the value
}



//function to write the value in the slave
void nrf_write_register(uint8_t reg, uint8_t value)
{
	NRF_CS_ENABLE();
	spi_write_read_byte(0x20|reg);// Send Write Command
	//for(i=0;i<500;i++); //delay
	spi_write_read_byte(value);//Writing value
	NRF_CS_DISABLE();
}

//function to write multiple values in the slave
void nrf_write_multiple(uint8_t register1, uint8_t *loc, uint8_t size)
{
	NRF_CS_ENABLE();	//clearing the ss bit to drive it low
	spi_write_read_byte(NORDIC_W_REGISTER|register1);

	  for(i=0; i<size; i++)
	  {
	    spi_write_read_byte(loc[i]);
	  }
	NRF_CS_DISABLE();	 //setting the ss bit high
}

// function to read the status of register by sending the nope
uint8_t nrf_read_register(uint8_t reg)
{
	uint8_t byte0,byte1;			// Clearing the ss bit to drive it low
	NRF_CS_ENABLE();
	byte0=spi_write_read_byte(NORDIC_R_REGISTER|reg);	// Send Read command
	byte1 = spi_write_read_byte(NORDIC_NOP);  // Sending 0xFF to read the value of register
	NRF_CS_DISABLE();				// setting the ss bit high
	return byte1;
}

// function to get default status
uint8_t nrf_status_read()
{
     uint8_t rx_ret = 0;

     NRF_CS_ENABLE();               // Clearing the ss bit to drive it low
     while(WAIT_SPTEF);				// Wait for SPTEF flag to get set
     SPI_D_REG(SPI0) = 0xFF;		// Transmit FF to data register
     while(WAIT_SPRF);				// Wait for SPRF flag to get set
     rx_ret = SPI_D_REG(SPI0);		// Receive data
     NRF_CS_DISABLE();				// setting the ss bit high

     return(rx_ret);
}

//function to flush txs fifo
void nrf_flush_tx_fifo()
{
	spi_write_read_byte(NORDIC_FLUSH_TX);
}

// function to set the RF parameters required for transmission.
void nrf_RF_Setup(void)
{
	//Setting a data rate of 1 Mbps, transmit power of 0dBm and the low power gain
	nrf_write_register(NORDIC_RF_SETUP_BASE, NORDIC_RF_PWR(0x07));
	//nrf_write_register(0x06,0x03);
}

/*
// sending payload to transmit buffer to send it
void NORDIC_TX_Payload(uint8_t *payload, uint8_t Payload_size) {
	uint16_t count = 0;
	//flushes the old data
	nrf_flush_tx_fifo();

	// writing the payload data
	nrf_write_multiple(NORDIC_W_TX_PAYLOAD, payload, Payload_size);

	//setting CE pin to start transmission
	CE_High();

	//setting some delay for which signal is high
	while(count!=8000)
	{
		count++;
	}

	//stop transmission
	CE_Low();
}

void nrf_set_tx_address()
{

	//setting the tx address width of 5 bytes in the Setup_aw (setup address width register)
	nrf_write_register(NORDIC_SETUP_AW, NORDIC_AW(5));

	nrf_write_multiple(NORDIC_TX_ADDR, (uint8_t*)TX_address, sizeof(TX_address));

	// enable auto-ack for pipe 0
	nrf_write_register(NORDIC_EN_AA, 0x00 | NORDIC_ENAA_P0(1));

	// enable data pipe 0
	//RF_WriteRegister(NORDIC_EN_RXADDR, 0x00 | NORDIC_ERX_P0(1));
}

*/





