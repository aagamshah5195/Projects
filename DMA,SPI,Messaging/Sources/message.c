/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/
/*
 * message.c
 * Created on: Nov 1, 2016
 * This file contains messaging module of FRDM.
 * It can send and decode multiple length packets.
 * If the command, length or checksum is not matched it will send NAK
 * If everything goes proper it will send ACK. Also there LED control provided to verify message control
 */
 
#include "main.h"

float bright=1;
int led_stat=0;
void decode_packet (void)
{
		uint8_t msb_checksum,lsb_checksum,msg_data;

		MSG_PACK.command = Remove_Item(&RXBUFF);

		MSG_PACK.length = Remove_Item(&RXBUFF);

		//loop to take in all data
		//check if data exists
		for(int i=0;i<(MSG_PACK.length)-HEAD_PACK_SIZE;i++)
		{
			MSG_PACK.data[i] = Remove_Item(&RXBUFF);
			msg_data = MSG_PACK.data[i];
		}

		msb_checksum = Remove_Item(&RXBUFF);			//read from rx buff
		lsb_checksum = Remove_Item(&RXBUFF);
		MSG_PACK.checksum = ((uint16_t)(msb_checksum) << 8) | lsb_checksum;

												//call checksum validate
		if(checksum_validate()==CHKSUM_FAIL)
		{
												//send NACK
			ack_nack_transmit(NACK_PACKET);
			LOG_0("\r\nNACK\r\n");
		}
		else
		{
												//read command byte and call functions
			if(MSG_PACK.command == LED_ON)
				led_control(msg_data);
			else if(MSG_PACK.command == BRIGHTNESS_SET)
				brightness_control(msg_data);
			else if(MSG_PACK.command == DISCO)
				dance(msg_data);

												//send ACK
			ack_nack_transmit(ACK_PACKET);
			LOG_0("\r\nACK\r\n");
		}
}

/* Send ack or nack packet on checksum success or fail
 */
void ack_nack_transmit (Cmds packet)
{
	uint8_t msb_checksum,lsb_checksum;

	MSG_PACK.command = packet;
	MSG_PACK.length = ACK_NACK_LEN;
	MSG_PACK.checksum = packet + ACK_NACK_LEN;
	LOG_1("\r\nchecksum:\r\n",MSG_PACK.checksum);
	msb_checksum = (uint8_t)(MSG_PACK.checksum) << 8;
	lsb_checksum = MSG_PACK.checksum;

	LOG_0("\r\nResponse packet:");
	LOG_1("\t",MSG_PACK.command);
	LOG_1("\t",MSG_PACK.length);
	LOG_1("\t",msb_checksum);
	LOG_1("\t",lsb_checksum);
}

/* Calculate addition checksum
 * add all valid byte elements
 * return error or success
 */
MSG_ERR_t checksum_validate (void)
{
	uint16_t check_sum;

	check_sum = MSG_PACK.command + MSG_PACK.length;
	for(int i=0;i<((MSG_PACK.length)-HEAD_PACK_SIZE);i++)
	{
		check_sum += MSG_PACK.data[i];
	}
	if(check_sum == MSG_PACK.checksum)
		return CHKSUM_PASS;
	else
		return CHKSUM_FAIL;
}

/* Turn ON/OFF led based on enum parameter
 */
void led_control (uint8_t msg_data)
{
	if (msg_data == RED)
	{
		R_ON; G_OFF; B_OFF;
		led_stat = 1;
	}
	else if (msg_data == GREEN)
	{
		R_OFF; G_ON; B_OFF;
		led_stat = 2;
	}
	else if (msg_data == BLUE)
	{
		R_OFF; G_OFF; B_ON;
		led_stat = 3;
	}
	else if (msg_data == YELLOW)
	{
		R_ON; G_ON; B_OFF;
		led_stat = 4;
	}
	else if (msg_data == CYAN)
	{
		R_OFF; G_ON; B_ON;
		led_stat = 5;
	}
	else if (msg_data == MAGENTA)
	{
		R_ON; G_OFF; B_ON;
		led_stat = 6;
	}
	else if (msg_data == WHITE)
	{
		R_ON; G_ON; B_ON;
		led_stat = 7;
	}
	else
	{
		R_OFF; G_OFF; B_OFF;
		led_stat = 8;
	}
}

/* Control led brightness based on enum parameter
 */
void brightness_control (uint8_t msg_data)
{
	if(msg_data == TEN_PERCENT)
		bright = TEN;
	else if(msg_data == TWENTY_PERCENT)
		bright = TWENTY;
	else if(msg_data == THIRTY_PERCENT)
		bright = THIRTY;
	else if(msg_data == FORTY_PERCENT)
		bright = FORTY;
	else if(msg_data == FIFTY_PERCENT)
		bright = FIFTY;
	else if(msg_data == SIXTY_PERCENT)
		bright = SIXTY;
	else if(msg_data == SEVENTY_PERCENT)
		bright = SEVENTY;
	else if(msg_data == EIGHTY_PERCENT)
		bright = EIGHTY;
	else if(msg_data == NINTY_PERCENT)
		bright = NINTY;
	else
		bright = CENT;

	if(led_stat == 1)
		R(bright);
	else if(led_stat == 2)
		G(bright);
	else if(led_stat == 3)
		B(bright);
	else if(led_stat == 4)
	{
		R(bright);
		G(bright);
	}
	else if(led_stat == 5)
	{
		G(bright);
		B(bright);
	}
	else if(led_stat == 6)
	{
		R(bright);
		B(bright);
	}
	else
	{
		R(bright);
		G(bright);
		B(bright);
	}
}

void dance(uint8_t msg_data)
{
	int i;
	if(msg_data=DANCE){
	R_ON;
	for(i=1;i>=0;i-0.1)
		R(i);
	for(i=0;i<=1;i+0.1)
		R(i);
	B_ON;
	for(i=1;i>=0;i-0.1)
		B(i);
	for(i=0;i<=1;i+0.1)
		B(i);
	G_ON;
	for(i=1;i>=0;i-0.1)
		G(i);
	for(i=0;i<=1;i+0.1)
		G(i);
	}
	else if(msg_data=NEXT_DANCE){
		R_ON;B_ON;
		for(i=1;i>=0;i-0.1){
			R(i);B(i);}
		for(i=0;i<=1;i+0.1){
			R(i);B(i);}
		B_ON;G_ON;
		for(i=1;i>=0;i-0.1){
			B(i);G(i);}
		for(i=0;i<=1;i+0.1){
			B(i);G(i);}
		G_ON;R_ON;
		for(i=1;i>=0;i-0.1){
			G(i);R(i);}
		for(i=0;i<=1;i+0.1){
			G(i);R(i);}
		}
}
