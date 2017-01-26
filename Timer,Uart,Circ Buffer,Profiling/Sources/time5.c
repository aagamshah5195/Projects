/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*time5.c*/

#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>
#include <string.h>

int8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length);
int8_t my_memzero(uint8_t * src, uint32_t length);
int8_t my_reverse(uint8_t * src, uint32_t length);
int8_t *my_iitoa(int8_t * str, int32_t data, int32_t base);
int32_t my_atoi(uint8_t * str);
void my_ftoa(float data, char *str, int number_after_decimal);
int my_itoa(char *str, int data, int d);
void reverse(char *str, int len);

void main()
 {/*
    	char a0[10]="abcdefghi";
	char b0[10];
	char a1[100]="is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna n";
	char b1[100];
	char a2[1000]="is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use";
	char b2[1000];
	char a3[5000]="is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you useis there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.is there a way to zjkcnxvkllsanvjklmxcn kjadnfbv djjas j sa jsd jsfjlsj ndksja jad akdj dams adna This is a free online calculator which counts the number of characters or letters in a text, useful for your tweets on Twitter, as well as a multitude of other applications.Whether it is Snapchat, Twitter, Facebook, Yelp or just a post to co-workers or business officials, the number of actual characters matters. What you say may not be as important as how you say it. And how many characters you use.";
	char b3[5000];
	char a4[20];
	char a5[20];
	char a6[20];
    struct timeval tvalBefore, tvalAfter;  // removed comma

    gettimeofday (&tvalBefore, NULL);
    memmove(a0,b0,10);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("10 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    memmove(a1,b1,100);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("100 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    memmove(a2,b2,1000);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("1000 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    memmove(a3,b3,5000);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("5000 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
printf("\nmy_memmove\n");
gettimeofday (&tvalBefore, NULL);
    my_memmove(a0,b0,10);
    gettimeofday (&tvalAfter, NULL);
    printf("10 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    my_memmove(a1,b1,100);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("100 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    my_memmove(a2,b2,1000);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("1000 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    my_memmove(a3,b3,5000);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("5000 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
		  printf("\nmy_reverse\n");
    gettimeofday (&tvalBefore, NULL);
    my_reverse(a0,10);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("10 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    my_reverse(a1,100);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("100 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    my_reverse(a2,1000);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("1000 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    my_reverse(a3,5000);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("5000 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
printf("\ninbuilt reverse\n");
gettimeofday (&tvalBefore, NULL);
    strrev(a0,10);
    gettimeofday (&tvalAfter, NULL);
    printf("10 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    strrev(a1,100);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("100 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    strrev(a2,1000);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("1000 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    strrev(a3,5000);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("5000 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
		  
printf("\nmy_memzero\n");
    gettimeofday (&tvalBefore, NULL);
    my_memzero(a0,10);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("10 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    my_memzero(a1,100);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("100 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    my_memzero(a2,1000);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("1000 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    my_memzero(a3,5000);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("5000 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
printf("\ninbuilt memzero\n");
gettimeofday (&tvalBefore, NULL);
    memset(a0,0,10);
    gettimeofday (&tvalAfter, NULL);
    printf("10 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    memset(a1,0,100);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("100 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    memset(a2,0,1000);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("1000 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
 gettimeofday (&tvalBefore, NULL);
    memset(a3,0,5000);
    gettimeofday (&tvalAfter, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("5000 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
printf("\ninbuild itoa\n");
gettimeofday (&tvalBefore, NULL);
    itoa(500,a4,10);
    gettimeofday (&tvalAfter, NULL);
    printf(" Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon

printf("my_itoa\n")
gettimeofday (&tvalBefore, NULL);
    my_iitoa(a5,200,10);
    gettimeofday (&tvalAfter, NULL);
    printf("Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon

printf("\ninbuild atoi\n");
gettimeofday (&tvalBefore, NULL);
    atoi("200");
    gettimeofday (&tvalAfter, NULL);
    printf(" Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon

printf("\nmy_atoi\n")
gettimeofday (&tvalBefore, NULL);
    my_atoi("500");
    gettimeofday (&tvalAfter, NULL);
    printf("10 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
printf("\nmy_ftoa\n");
my_ftoa(500.254,a6,3);
    gettimeofday (&tvalAfter, NULL);
    printf("10 Time in microseconds: %ld microseconds\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          );
*/
struct timeval tvalBefore, tvalAfter;  // removed comma

gettimeofday (&tvalBefore, NULL);
    printf("\n20 characters of str\n");
    gettimeofday (&tvalAfter, NULL);
    printf("Time in microseconds: %ld microseconds for printf1\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
int val0=10,val1=12,val2=14;
float val3=10.0,val4=12.0,val5=14.0;
gettimeofday (&tvalBefore, NULL);
    printf("\nInteger val :%d\n",val0);
    gettimeofday (&tvalAfter, NULL);
    printf("Time in microseconds: %ld microseconds for printf2 int\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
gettimeofday (&tvalBefore, NULL);
    printf("\nFloat val: %f\n",val3);
    gettimeofday (&tvalAfter, NULL);
    printf("Time in microseconds: %ld microseconds for printf2 float\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon
gettimeofday (&tvalBefore, NULL);
    printf("\n2 Integer val :%d\t%d\n",val0,val1);
    gettimeofday (&tvalAfter, NULL);
    printf("Time in microseconds: %ld microseconds for printf3 int\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon

gettimeofday (&tvalBefore, NULL);
    printf("\n2 Float val: %f\t%f\n",val3,val4);
    gettimeofday (&tvalAfter, NULL);
    printf("Time in microseconds: %ld microseconds for printf3 float\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon


gettimeofday (&tvalBefore, NULL);
    printf("\n3 Integer val :%d\t%d\t%d\n",val0,val1,val2);
    gettimeofday (&tvalAfter, NULL);
    printf("Time in microseconds: %ld microseconds for printf4 int\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon

gettimeofday (&tvalBefore, NULL);
    printf("\n3 Float val: %f\t%f\t%f\n",val3,val4,val5);
    gettimeofday (&tvalAfter, NULL);
    printf("Time in microseconds: %ld microseconds for printf4 float\n",
            ((tvalAfter.tv_sec - tvalBefore.tv_sec)*1000000L
           +tvalAfter.tv_usec) - tvalBefore.tv_usec
          ); // Added semicolon

}

/*

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
int8_t my_memzero(uint8_t * src, uint32_t length)
{

    int i;
    for (i=0;i<length;i++)
        *(src+i)=0;
    return 1;
}



int8_t my_reverse(uint8_t * src, uint32_t length)
{
 if(length<0) //  negative length
    printf("Error\n");
    else if(length ==0) //check for 0 length
    printf("Error\n");
    else{
        if(((*(src+length)))!='\0') //check for NULL ending
    	printf("Error\n"); 
	}   
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
int8_t *my_iitoa(int8_t * str, int32_t data, int32_t base)
{
    //Initialize some counter variables
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

// Function for ascii to integer
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
		printf("Invalid Input"); //If input is other than number
		return 0;
		}
	}

    // Return the Final result with sign
    if (count==0)
	return result;
    else
	return -1*result;
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
*/
