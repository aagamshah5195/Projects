/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * log.c
 *  Created on: Oct 9, 2016
 * This file contains logger functions
 * LOG_0 -> Prints out the string of ASCII characters
 * LOG_1 -> Prints out the string of ASCII characters along with the numeric parameter of type integer
 * LOG_2 -> Prints out the string of ASCII characters along with the numeric parameter of type float
 * ftoa -> Converts float to ascii
 * itoa -> Converts integer to ascii
 * reverse -> Reqd by itoa and ftoa to reverse the string and get desired output
 */

#include "main.h"
void LOG_0(uint8_t * data, uint32_t len)
{
#ifdef DEBUG
#ifdef FRDM
	for (int i=0;i<len;i++)
	{
		//Wait until TX buffer is full or transmission complete flag is set
		while(!((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK)));
	    UART0_D = *data;
	    data++;				//point to next character
	}


#endif

#ifdef BBB
	for (i=0;i<len;i++)
	{
		printf("\n%p",*data);
		data++;
	}
#endif
#endif
}
void LOG_1(uint8_t * data, uint32_t len, uint32_t param, uint8_t param_size)
{
#ifdef DEBUG
#ifdef FRDM
LOG_0(data,len);
char string[20];
my_itoa(string,param,0);
int p_size=strlen(string);
LOG_0(string,p_size);
#endif
#ifdef BBB
	for (int i=0;i<len;i++)
	{
		printf("\n%p",*data);
		*data++;
	}
	printf(":");
	printf("%d",param);
#endif
#endif
}
void LOG_2(uint8_t * data, uint32_t len, float param, uint8_t param_size)
{
#ifdef DEBUG
#ifdef FRDM
LOG_0(data,len);
char string[20];
my_ftoa(param,string,6);
LOG_0(string,param_size);
#endif
#ifdef BBB
	for (int i=0;i<len;i++)
	{
		printf("\n%p",*data);
		*data++;
	}
	printf(":");
	printf("%d",param);
#endif
#endif
}


// reverse string after itoa
void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = *(str+i);
        *(str+i) = *(str+j);
        *(str+j) = temp;
        i++; j--;
    }
}

// Converts integer to ascii
int my_itoa(char *str, int data, int d)
{
    int i = 0,count=0;
    if(data<0)
    {
        count++;
        data=-data;
    }
    while (data)
    {
        *(str+i++) = (data%10) + '0';
        data = data/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        *(str+i++) = '0';
    if(count==1)
        *(str+i++)='-';
    reverse(str, i);
    *(str+i) = '\0';
    return i;
}

// Converts a floating point number to string.
void my_ftoa(float data, char *str, int number_after_decimal)
{
    // Extract integer part
    int before_decimal = (int)data;

    float after_decimal;
    // Extract floating part
    if (data<0)
	 after_decimal= (float)before_decimal-data;

    else
    	after_decimal = data-(float)before_decimal;

    // convert integer part to string
    int i = my_itoa(str,before_decimal, 0);

    // check for numbers after point
    if (number_after_decimal != 0)
    {
        *(str+i) = '.';  // add dot

        // Get the value of fraction part
        after_decimal = after_decimal * pow(10, number_after_decimal);

        my_itoa(str+i+1,(int)after_decimal, number_after_decimal);
    }
}


