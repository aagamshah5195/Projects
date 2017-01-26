/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * unittest.c
 * This contains all the unit tests cases for circular buffer*/

#include "main.h"
extern uint8_t flag_once;
void buffer_test(void)
{
	uint8_t sample_data=55;
	Buffer_init(&RXBUFF,25,1);			//init RX buffer
	Buffer_init(&TXBUFF,25,0);			//init TX buffer
	uint8_t temp_val,pass_count=0,fail_count=0;

		LOG_0("\r\nBUFFER UNIT TEST:\r\n",21);

		LOG_0("\r\nEMPTY buffer",14);
		empty_buffer(&RXBUFF);							//empty fully
		temp_val=Remove_Item(&RXBUFF);
		LOG_0("\r\nRemove item TEST -->",22);			//remove test for empty buffer
		if(temp_val ==0)
		{
			LOG_0("FAIL\r\n",6);
			LOG_0("\rBuffer is empty\r\n",19);
			fail_count++;
		}
		else
			{
				LOG_0("PASS\r\n",6);
				pass_count++;
			}

		LOG_0("\r\nFILL buffer",13);				//remove test for full buffer
		full_buffer(&RXBUFF,sample_data);					//fill buffer
		LOG_0("\r\nAdding item test -->",22);
		LOG_0("PASS\r\n",6);
		pass_count++;
//-----------------------------------------------------------------------------------------//

		LOG_0("\r\nEMPTY buffer",14);				//add test for empty buffer
		empty_buffer(&RXBUFF);							//empty fully
		//LOG_0("\rBuffer is empty\r\n",19);
		LOG_0("\rAdding item\r\n",14);
		LOG_0("\r\nAdding item TEST -->",22);
		temp_val=Add_Item(&RXBUFF,sample_data);
		if(temp_val ==0) {
			LOG_0("FAIL\r\n",6);
			LOG_0("\rBuffer is full\r\n",18);
			fail_count++;
		}
		else
		{
			LOG_0("PASS\r\n",6);
			pass_count++;
		}

		LOG_0("\r\nFILL buffer",13);				//add test for full buffer
		full_buffer(&RXBUFF,sample_data);					//fill buffer
		temp_val=Add_Item(&RXBUFF,sample_data);
		LOG_0("\r\nAdding item TEST -->",22);
		if(temp_val ==0) {
			LOG_0("FAIL\r\n",6);
			LOG_0("\rBuffer is full\r\n",18);
			fail_count++;
		}
		else
		{
			LOG_0("PASS\r\n",6);
			pass_count++;
		}
//----------------------------------------------------------------------------------------//
		LOG_0("\r\nEMPTY buffer",14);
		empty_buffer(&RXBUFF);							//empty fully
		LOG_0("\r\nBuffer full TEST -->",22);
		temp_val=BufFull(&RXBUFF);
		if(temp_val ==0) {
			LOG_0("FAIL\r\n",6);
			LOG_0("\rBuffer is not full\r\n",22);
			fail_count++;
		}
		else
		{
			LOG_0("PASS\r\n",6);
			pass_count++;
		}
		LOG_0("\r\nFILL buffer",13);
		full_buffer(&RXBUFF,sample_data);					//fill buffer
		LOG_0("\r\nBuffer full TEST -->",22);
		temp_val=BufFull(&RXBUFF);
		if(temp_val ==0)
		{
			LOG_0("FAIL\r\n",6);
			fail_count++;
		}
		else
		{
			LOG_0("PASS\r\n",6);
			LOG_0("\rBuffer is full\r\n",18);
			pass_count++;
		}
//---------------------------------------------------------------------------------------//
		LOG_0("\r\nEMPTY buffer",14);
		empty_buffer(&RXBUFF);							//empty fully//empty buffer

		LOG_0("\r\nBuffer empty TEST -->",23);
		temp_val=BufEmpty(&RXBUFF);
		if(temp_val ==0)
			{
			LOG_0("FAIL\r\n",6);
			fail_count++;
			}
		else
		{
			LOG_0("PASS\r\n",6);
			LOG_0("\rBuffer is empty\r\n",19);
			pass_count++;
		}

		LOG_0("\r\nFILL buffer",13);
		full_buffer(&RXBUFF,sample_data);					//fill buffer

		LOG_0("\r\nBuffer empty TEST -->",23);
		temp_val=BufEmpty(&RXBUFF);
		if(temp_val ==0)
		{
			LOG_0("FAIL\r\n",6);
			LOG_0("\rBuffer is full\r\n",18);
			fail_count++;
		}
		else
		{
			LOG_0("PASS\r\n",6);
			pass_count++;
		}
		LOG_0("\r\n-----------------------------------------------\r\n",51);
		LOG_0("\rUNIT TEST SUITE:",17);
			LOG_1("\r\nFAIL-->",9,fail_count,8);
			LOG_1("\r\nPASS-->",9,pass_count,8);
}

//fn for buffer complete fill
void full_buffer(CircBuf_t *cptr,uint8_t data)
{
	uint8_t i=0;
	while(i<30)
	{
		i++;
		Add_Item(cptr,data);
	}
}

//fn for buffer empty
void empty_buffer(CircBuf_t *cptr)
{
	uint8_t i=0,dummdata;
	while(i<30)
	{
		i++;
		dummdata=Remove_Item(cptr);
	}

}
