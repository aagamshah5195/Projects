/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * message.h
 *  Created on: Nov 1, 2016
 *  
 */

#ifndef INCLUDES_MESSAGE_H_
#define INCLUDES_MESSAGE_H_

#define ACK_NACK_LEN 4			//packet length for ack/nack packet
#define MAX_DATA_SIZE 20

typedef enum CMD {					//commands set
	LED_ON = 0xC1,
	BRIGHTNESS_SET = 0xC2,
	DISCO=0xC3,
	ACK_PACKET = 0xA1,
	NACK_PACKET = 0xA0
}Cmds;

typedef struct CI_Msg {
	Cmds command; 					// Command operation
	uint8_t length; 				// Size of message
	uint8_t data[MAX_DATA_SIZE]; 	// Generic data payload
	uint16_t checksum; 				// Error detection checksum
}CI_Msg_t;

CI_Msg_t MSG_PACK;

typedef enum LED_brightness {		//brightness control
	TEN_PERCENT = 0x10,
	TWENTY_PERCENT = 0x20,
	THIRTY_PERCENT = 0x30,
	FORTY_PERCENT = 0x40,
	FIFTY_PERCENT = 0x50,
	SIXTY_PERCENT = 0x60,
	SEVENTY_PERCENT = 0x70,
	EIGHTY_PERCENT = 0x80,
	NINTY_PERCENT = 0x90,
	CENT_PERCENT = 0xFF
}LED_bright_t;

#define TEN 0.1						//brightness levels
#define TWENTY 0.2
#define THIRTY 0.3
#define FORTY 0.4
#define FIFTY 0.5
#define SIXTY 0.6
#define SEVENTY 0.7
#define EIGHTY 0.8
#define NINTY 0.9
#define CENT 1.0

typedef enum LED_CNTRL {			//led on off
	RED = 0x01,
	GREEN = 0x02,
	BLUE = 0x04,
	YELLOW = 0x03,
	CYAN = 0x06,
	MAGENTA = 0x05,
	WHITE = 0x07,
	OFF = 0x00
}LED_control_t;

typedef enum DISCO_DANCE{
	DANCE=0x01,
	NEXT_DANCE=0x02,
}DISCO_t;
typedef enum MSG_ERR {
	CHKSUM_FAIL = 0xE0,
	CHKSUM_PASS = 0xE1
}MSG_ERR_t;

//function definations
void decode_packet (void);
void ack_nack_transmit (Cmds packet);
MSG_ERR_t checksum_validate (void);

void led_control (uint8_t payload);
void brightness_control (uint8_t payload);
void blink (Cmds blink_cmd);
void dance (uint8_t msg_data);

#define HEAD_PACK_SIZE 4


#endif /* INCLUDES_MESSAGE_H_ */
