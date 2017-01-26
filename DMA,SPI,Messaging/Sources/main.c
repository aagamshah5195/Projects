/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*main.h */

#include "main.h"

extern uint8_t packet_byte,rx_byte;

int main(void)
{
#ifdef MESSAGE
//LOG_0("\n\rEnter the message\r\n");
uint8_t str[2],byte_length=0,byte_process=0,current_length=0,packet_length=0,packet_complete=0;

//system - init peripherals
	uart_init(baud);
	RGB_init();
	Buffer_init(&RXBUFF,25);
	//profiler();
	while(1)
	{
		if(rx_byte == 1)
		{
			//atoi
					//start();								// for profiling
					str[byte_length] = packet_byte;				//byte processing for terminal input
					byte_length++;
					if(byte_length == 2)
					{
						packet_byte = myAtoi(str);
						byte_process = 1;
						byte_length = 0;
						LOG_0("\t|\t");
					}

					if(byte_process == 1)
					{
						byte_process = 0;
						Add_Item(&RXBUFF,packet_byte);

						current_length ++;
						if(current_length == 2)					//length byte from the second byte
						{
							packet_length = packet_byte;
							if(packet_length == 0)
							{
								current_length = 0;
								byte_length = 0;
								LOG_0("\r\npacket_error\r");
							}
						}

						if(current_length == packet_length)
						{
							packet_complete = 1;
							current_length = 0;
							LOG_0("\r\npacket_complete\r");
						}
					}
					UART0_C2 |= UART0_C2_RIE_MASK; 			//Peripheral interrupt enable (RX)
					rx_byte = 0;
		}

		if(packet_complete == 1) {
			decode_packet();
			packet_complete = 0;
			//end();		//for profiling
		}

	}
#endif

#ifdef DMA_PROFILE_TEST
#ifdef SIZE8
		char a0[10]="0bcdefghi";
		char b0[10];
		char a1[100]="0s there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna n";
		char b1[100];
		char a2[1000]="0s there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use";
		char b2[1000];
		char a3[5000]="0s there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you useis there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.";
		char b3[5000];
		uint32_t length=5000;
		profiler();
		memmove_dma8(a3,b3,length);
#endif
#ifdef SIZE32
		uint32_t a0[3]= {0,1,2};
		uint32_t b0[3];
		uint32_t a1[25]= {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
		uint32_t b1[25];
		uint32_t a2[250]= {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
		uint32_t a3[1250]={0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1};//="0s there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj n
		uint32_t b2[250];
		uint32_t b3[1250];
		uint32_t length=5000;
		profiler();
		memmove_dma32(a3,b3,length);
#endif
	while(1);
#endif

#ifdef SPI
	uint8_t receive;
	spi_init();
	while(1)
	{
		spi_send_byte('o');
	}
#endif
#ifdef NORDIC_TEST

	spi_init();
	uart_init(38400);
	uint8_t status1,status2,status3;
	LOG_0("\r\nInitializing nRF24L01\r\n");
#ifdef config_test
	LOG_0("\r\nCONFIG TEST\r\n");
	//nrf_config();
	uint8_t status;
		nrf_write_register(NORDIC_CONFIG_BASE,NORDIC_POWER_UP_MASK);	// Writing in Config for Using it in RX mode and Power up
		status=nrf_read_register(NORDIC_CONFIG_BASE);					// Reading Config Reg
		if(status==NORDIC_POWER_UP_MASK)								// LED control to verify it is able to write the value
				{
					RGB_init();
					R_ON;B_ON;G_ON;
				}
		LOG_1("Status:",status);										// Uart control to verify the value

#endif

#ifdef status_test
	LOG_0("\r\nSTATUS TEST\r\n");
	status1=nrf_status_read();
	LOG_1("Status:",status1);
#endif

#ifdef rf_test
	LOG_0("\r\nRF TEST\r\n");
	nrf_RF_Setup();
	status2=nrf_read_register(NORDIC_RF_SETUP_BASE);
	LOG_1("Status:",status2);
	if(status2==0X07)
			{
				RGB_init();
				R_ON;
				LOG_0("\r\nPOWER LEVEL: 0db\r\n");
			}
	if(status2==0X05)
				{
					RGB_init();
					B_ON;
					LOG_0("\r\nPOWER LEVEL: -6db\r\n");
				}
	if(status2==0X03)
				{
					RGB_init();
					R_ON;B_ON;
					LOG_0("\r\nPOWER LEVEL: -12db\r\n");
				}
	if(status2==0X01)
				{
					RGB_init();
					G_ON;
					LOG_0("\r\nPOWER LEVEL: -18db\r\n");
				}
#endif

#ifdef fifo_status_test
	LOG_0("\r\nFIFO STATUS TEST\r\n");
	status3=nrf_read_register(NORDIC_FIFO_STATUS_BASE);
	LOG_1("Status:",status3);
#endif

#ifdef tx_addr_test
	LOG_0("\r\nTX ADDR TEST\r\n");
	status4=nrf_read_register(NORDIC_TX_ADDR_BASE);
	LOG_1("Status:",status4);
#endif
#endif
    return 0;
}
