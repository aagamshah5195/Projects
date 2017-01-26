/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*data.c*/

#include<stdio.h>
#include<stdint.h>
#include "data.h"


// Function for integer to ascii string

int8_t *my_iitoa(int8_t * str, int32_t data, int32_t base)
{
    /*Initialize some counter variables*/
    uint16_t count=0;
    uint32_t length_count=0;

    //Condition for input 0
    if (data == 0)
    {
        *str = '0';
	str++;
        *str = '\0';
	return str;
    }
    //Condition for negative input
    if (data < 0 && base == 10)
    {
        count++;
        data = -data;
    }
    //Converting integer to  reverse ascii string
    while(data!=0)
    {
        uint16_t rem = data % base;     //taking one digit at a time

        if (rem>9)                      //For Hexadecimal digits greater than 9
        {
	     *str= (rem-10)+'A';
	     str++;
        }
        else                            //For digits less than 9
        {
	     *str= rem+'0';
	     str++;
        }
        data = data/base;               //Eliminating the digit which is already computed for
        length_count++;                 //Incrementing the length count
    }

    //Adding a negative sign for negative decimal input
    if (count==1)
    {
	*str = '-';
 	length_count++;
        str++;    //Converting integer to  reverse ascii string
    }

    *str='\0';
     str--;

    //Reversing the calculated ascii string to get correct ascii string
    uint16_t i ;
    uint8_t temp;
    for(i=0;i<length_count/2;i++)
    {
	temp=*(str-i);
	*(str-i)=*(str+1+i-length_count);
	*(str+1+i-length_count)=temp;
    }

   return str;
}

 //Function for ascii to integer
int32_t my_atoi(uint8_t * str)
{

    uint16_t count = 0;  // Initialize count for sign
    uint16_t i = 0;


    // If it is negative, then increment count
    if (*str == '-')
    {
        count++ ;
   	i++;
    }
	
    int32_t result = 0;  // Initialize result
    for (; *(str+i) != '\0'; ++i)
	{	
	if (*str >= '0' && *str <= '9')
        result = result*10 + *(str+i) - '0';
	else
		{
		printf("Invalid Input"); //If input are other than number
		return 0;
		}
	}

    // Return the Final result with sign
    if (count==0)
	return result;
    else
	return -1*result;
}



//Function for converting data to hex
void dump_memory(uint8_t * start, uint32_t length)
{
    int16_t i;
    for(i=0;i<length;i++)
    {
        printf("\nHex of %hi byte is %2u",i,*(start+((uint32_t)i)));
    }
}

//Function for converting big endian to little endian
int32_t big_to_little(int32_t data)
{
    int32_t little;
    little= (((data>>24) & 0x000000ff) | ((data>>8) & 0x0000ff00) | ((data<<8) & 0x00ff0000) | ((data<<24) & 0xff000000));		       
    return little;
}



//Function for converting little endian to big endian
int32_t little_to_big(int32_t data)
{
    int32_t big;
    big= (((data>>24) & 0x000000ff) | ((data>>8) & 0x0000ff00) | ((data<<8) & 0x00ff0000) | ((data<<24) & 0xff000000));
    return big; 
}
