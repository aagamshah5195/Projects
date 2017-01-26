/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*profiler.c*/

#include "main.h"
#ifdef FRDM
void profiler(void)
{

SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;			// Enable TPM1 Clock gate
SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);			// Select MCGFLLCLK clock 21 Mhz

TPM1_SC=0;									// Disable Timer
TPM1_MOD = MOD_VAL;							//Set Counter for 10 uS


TPM1_SC |= TPM_SC_PS(0);	// Prescaler divide by 1

__enable_irq();					// Enable global Interrupt
NVIC_EnableIRQ(TPM1_IRQn);  	// Enable NVIC Interrupt
TPM1_SC |= TPM_SC_TOIE_MASK; 	// Enable Timer Overflow Interrupt
}

void start(void)
{
	TPM1_SC |= TPM_SC_CMOD(1);		// Start Counter
}

uint8_t ov_count=0;
void end(void)
{
	uint32_t val_count=0;
	float timer_clk=0;
	TPM1_SC &= ~TPM_SC_CMOD(1);			// Stop Counter

	val_count= TPM1_CNT;
	timer_clk= val_count/T1CLK;			// Clock

	if (ov_count !=0)
	{
		timer_clk = timer_clk + (MOD_VAL/T1CLK)*ov_count;
		ov_count=0;
	}
	LOG_2("\r\nExexution time for my_memmove\r\n:",24,timer_clk,sizeof(timer_clk));
}

/*--------------------------------------------------------------------------------------------
 * Timer1 overflow interrupt service
 --------------------------------------------------------------------------------------------*/
void TPM1_IRQHandler(void)
{
	if(TPM1_SC & TPM_SC_TOF_MASK)
	{
		ov_count++;					//Increment of oveflow
		TPM1_SC &= ~TPM_SC_TOF_MASK;			//clear the tof bit by writing 1
	}
}
#endif
#ifdef BBB
void profile_BBB(void)
int a[5000], b[5000];
    struct timeval start_time, end_time;  // removed comma

    gettimeofday (&start_time, NULL);
    memmove(a,b,10);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation
    printf("inbuilt memmove\n")
    printf("10 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    memmove(a,b,100);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("100 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    memmove(a,b,1000);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("1000 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    memmove(a,b,5000);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("5000 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
printf("\nmy_memmove\n");

    printf("10 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    my_memmove(a,b,100);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("100 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    my_memmove(a,b,1000);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("1000 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    my_memmove(a,b,5000);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("5000 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
printf("my_memzero\n");
    gettimeofday (&start_time, NULL);
    my_memzero(a,10);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("10 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    my_memzero(a,100);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("100 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    my_memzero(a,1000);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("1000 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    my_memzero(a,5000);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("5000 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
printf("inbuilt memzero\n");
gettimeofday (&start_time, NULL);
    memset(a,0,10);
    gettimeofday (&end_time, NULL);
    printf("10 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    memset(a,0,100);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("100 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    memset(a,0,1000);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("1000 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    memset(a,0,5000);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("5000 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
printf("my_reverse\n");
    gettimeofday (&start_time, NULL);
    my_reverse(a,10);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("10 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    my_reverse(a,100);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("100 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    my_reverse(a,1000);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("1000 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    my_reverse(a,5000);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("5000 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
printf("inbuilt reverse\n");
gettimeofday (&start_time, NULL);
    strrev(a,10);
    gettimeofday (&end_time, NULL);
    printf("10 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    strrev(a,100);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("100 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    strrev(a,1000);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("1000 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
 gettimeofday (&start_time, NULL);
    strrev(a,5000);
    gettimeofday (&end_time, NULL);

    // Changed format to long int (%ld), changed time calculation

    printf("5000 Time in microseconds: %ld microseconds\n",
            ((end_time.tv_sec - start_time.tv_sec)*1000000L
           +end_time.tv_usec) - start_time.tv_usec
          ); // Added semicolon
    return 0;
}
#endif
