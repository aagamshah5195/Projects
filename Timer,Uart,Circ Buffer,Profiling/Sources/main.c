/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * main.c
 * Created on: Oct 7, 2016
 * This file is a main file where all function calls are made.
 */
#include "main.h"
int8_t next_colour=0;
float B=1.0;
int main()
{
	uart_init(38400);					// Initialise Uart0
#ifdef LOGGER_TEST
	//Test cases for Uart Logger
	LOG_0("\r\n|***************Test cases for Uart Logger***************|\r\n",62);
	LOG_0("\r\nTesting123,Serial Print Test,no params\r\n",42);
	LOG_1("\r\nThis is an Integer number:",28,200,8);
	LOG_1("\r\nThis is an Integer number:",28,4096,16);
	LOG_1("\r\nThis is an Integer number:",28,123456,32);
	LOG_2("\r\nThis is an Floating number:",29,1543.321,sizeof(1543.321));
	while(1);
#endif

#ifdef RGB_TEST
	RGB_init();							// Initialise Rgb led
	//Cases for LED
	LOG_0("\r\n\r\n|***************Test cases for Uart LED****************|\r\n",62);
	LOG_0("\r\nPRESS ANY OF THE KEYS LISTED BELOW\r\n",38);
	LOG_0("\r\na -> NEXT_COLOR",17);
	LOG_0("\r\nd -> PREVIOUS_COLOR",21);
	LOG_0("\r\nw -> BRIGHTNESS +",19);
	LOG_0("\r\ns -> BRIGHTNESS -\r\n",21);
	while(1)
	    {
	    	switch(next_colour)
	    	{
	    	case 1:
	    		R(B);
	    		B(0);
	    		G(0);
	    		break;
	    	case 2:
	    	    R(0);
	    	    B(0);
	    	    G(B);
	    	    break;
	    	case 3:
	    	  	R(0);
	    	    B(B);
	    	    G(0);
	    	    break;
	    	case 4:
	    	  	R(B);
	    	    B(B);
	    	    G(0);
	    	    break;
	    	case 5:
	    	  	R(B);
	    	    B(0);
	    	    G(B);
	    	    break;
	    	case 6:
	    	  	R(0);
	    	    B(B);
	    	    G(B);
	    	    break;
	    	case 7:
	    	  	R(B);
	    	    B(B);
	    	    G(B);
	    	    break;
	    	case 8:
	    	    R(0);
	    	    B(0);
	    	    G(0);
	    	    break;
	    	default:
	    		next_colour=1;
	    		break;
	    	}

	    }
#endif

#ifdef BUFFER
	uint8_t read,i=0;
	while(1)
		{
			Buffer_init(&RXBUFF,25,1);			//Initialise RX Buffer
			Buffer_init(&TXBUFF,25,0);			//Initialise TX Buffer

			LOG_0("\r\nEnter your string\r\n",21);
			LOG_0("\r\nStoring in receive buffer\r\n",29);

			data=0;
			while(1)									//infinite loop
			{
				//receive in RX buff ,loop to copy contents from UART0_D into RX BUFFER
				if(data == 1)						//incoming data in rx buff complete
				{
					while(i<Max)
					{
						read = Remove_Item(&RXBUFF);	//read from rx buff
						Add_Item(&TXBUFF,read);			//write to tx buff
						i++;
					}
					data=2;
					LOG_0("\r\nSending from tx buffer\r\n",26);
					UART0_C2 |= UART0_C2_TIE_MASK;		//enable tx interrupt after copy from rxbuff complete

				}
				if(data == 3)						//copied from tx buff complete
				{
					break;				//delete heap memory
				}
			}
		}

#endif

#ifdef PROFILE_TEST
	int i=0;
	char a0[10]="abcdefghi";
	char b0[10];
	char a1[100]="is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna n";
	char b1[100];
	char a2[1000]="is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use";
	char b2[1000];
	char a3[5000]="is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you useis there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.";
	char b3[5000];
	int32_t length=10;
	profiler();
	start();
	my_memmove(a0,b0,10);
	end();
	//start();
	//end();
	while(1);
#endif
#ifdef UNIT_TEST
	buffer_test();
	Destroy(&RXBUFF);
	LOG_0("\r\nFreeing up heap\r\n",19);
	while(1);
#endif
    return 0;
}



