/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*project_1.c*/

#include <stdio.h>
#include "data.h"
#include "memory.h"
#include "project_1.h"
#include <stdint.h>

void project_1_report()
{ 
   
      uint8_t arr[32];
      uint8_t *aptr_1 = &arr[0];
      uint8_t *aptr_2 = &arr[8];
      uint8_t *aptr_3 = &arr[16];
      uint16_t i,j;

      printf("\nBelow functions displays memory functions\n");
      //Initalizing 16 bytes starting from aptr_1 from 31-46
      for(i=0;i<=15;i++)
      {
         *(aptr_1+i)= i+31;   
      }
      

      //Initalizing the contents from aptr_3 to end of arr array to 0's
      my_memzero(aptr_3,16);

      //Moving 8 bytes from aptr_1 to aptr_3
      my_memmove(aptr_1,aptr_3,8);

      //Moving 16 bytes from aptr_2 to aptr_1
      my_memmove(aptr_2,aptr_1,16);

      //Reversing the entire 32 bytes starting from aptr_1
      my_reverse(aptr_1,32);
      
      //Printing out the entire 32 byte array
      for(j=0;j<32;j++)
        printf("\nByte %d of arr is %d",j+1,*(arr+j));

      uint8_t string[100]; 	
      uint8_t *str=(uint8_t *)string;

      printf("\n\nBelow functions displays data functions\n");
      // Function call for integer to ascii
      my_itoa((int8_t *)str,12345,2);				
      printf("\nAscii String after itoa is: %s\n",string);

      // Function call for asci to integer
      uint8_t string1[100]="789456";				
      printf("\nAscii to integer: %d\n",my_atoi(string1));
			
      //Function call for dump_memory
      uint8_t string2[100]="This is a test string";
      uint8_t *str1=(uint8_t *)string2;
      dump_memory(str1+5,10);	
			
      //Function call for converting little endian to big endian
      int32_t x=little_to_big(12345678);			
      printf("\n\nLittle to big:%X\n",x);

      //Function call for converting big endian to little endian
      int32_t y=big_to_little(87654321);			
      printf("\nBig to little :%X\n",y);
}

