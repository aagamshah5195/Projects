/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*memory.c*/

#include <stdint.h>
#include <stdio.h>
#include "memory.h"

//Function for reversing the data
int8_t my_reverse(uint8_t * src, uint32_t length)
{
/* if(length<0) //  negative length
    printf("Error\n");
    else if(length ==0) //check for 0 length
    printf("Error\n");
    else{
        if(((*(src+length)))!='\0') //check for NULL ending
    	printf("Error\n"); 
	}*/
    int i;
    char temp;
    for (i=0;i<length/2;i++)
    {
        temp=*(src+i);
        *(src+i)=*(src+length-1-i);
        *(src+length-1-i)=temp;
    }
    return 1;
}

//Function for replacing all data after the given source with 0's
int8_t my_memzero(uint8_t * src, uint32_t length)
{
    int i;
    for (i=0;i<length;i++)
        *(src+i)=0;
    return 1;
}


//Function for moving the data from one memory location to another
int8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length)
{
    unsigned int i;

    char* src_p = (char*)src;
    char* dst_p = (char*)dst;

    if (src_p==dst_p)   //If source equals destination return 0
	return 0;

    else if( src_p > dst_p )
    {
        for( i = 0;i < length; ++i )
           *(dst_p+i) = *(src_p+i);
    }

    else
     {
        for( i = 0; i != length; ++i )
           *(dst_p+length - i - 1) = *(src_p+length - i - 1);
     }
	return 1;
}



