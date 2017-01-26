/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/* log.c
 * This file contains logger functions
 * LOG_0 -> Prints out the string of ASCII characters
 * LOG_1 -> Prints out the string of ASCII characters along with the numeric parameter of type integer
 * LOG_2 -> Prints out the string of ASCII characters along with the numeric parameter of type float
 * ftoa -> Converts float to ascii
 * itoa -> Converts integer to ascii
 * reverse -> Reqd by itoa and ftoa to reverse the string and get desired output
 */

#include "math.h"
#include "log.h"
#include "MKL25Z4.h"

void LOG_0(uint8_t * data)
{

	for (int i=0;*data!='\0';i++)
	{
		//Wait until TX buffer is full or transmission complete flag is set
		while(!((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK)));
	    UART0_D = *data;
	    data++;				//point to next character
	}

}
void LOG_1(uint8_t * data, uint32_t param)
{

		LOG_0(data);
		uint8_t dest[20];
		my_itoa(dest,param,10);
		LOG_0(dest);

}
void LOG_2(uint8_t * data, float param)
{

		LOG_0(data);
		uint8_t dest[20];
		my_ftoa(param,dest,4);
		LOG_0(dest);

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

uint8_t myAtoi(uint8_t *str)
{
    uint8_t res,res1,res2; // Initialize result

    // Iterate through all characters of input string and
    // update result

    	if(str[0] >= 'A' && str[0] <= 'F')
    	{
    		res1 = str[0] - 0x37;
    		res1 = res1 * 16;
    	}
    	else
    	{
    		res1 = str[0] - 0x30;
    		res1 = res1 * 16;
    	}

    	if(str[1] >= 'A' && str[1] <= 'F')
    	{
    		res2 = str[1] - 0x37;
    	}
    	else
    		res2 = str[1] - 0x30;

    	res = res1 + res2;
    // return result.
    return res;
}

void converthex(char *data, unsigned int a) //definition
{
   unsigned int temp =a;
   int digits=0,set;
   int i=0;
   unsigned int x;
   unsigned int mask;
   mask=0x0f;
   while(temp!=0)
   {
        temp=temp/16;
        digits++;
        if(digits>1)mask=mask<<4;
   }
   set=digits;
   set--;

   data[i]='0';
   i++;
   data[i]='x';
   i++;
   temp=a;
   while(digits!=0)
   {
        x=(temp&mask);
        x=x>>(set*4);
        if(x<=9)data[i]=0x30+x;
        else
        {
            data[i]=0x41+(x-10);
        }
        digits--;
        i++;
        temp=temp<<4;
   }
    data[i]='\0';
}
