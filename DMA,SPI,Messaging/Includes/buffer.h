/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/
/*buffer.h*/

#ifndef _CIRCBUF_H
#define _CIRCBUF_H
#include<stdint.h>

typedef struct circbuf{
     uint8_t* circ_buf;
     uint8_t* head;
     uint8_t* tail;
     int16_t count;
     int16_t length;
     uint8_t *circ_bufend;
 }CircBuf_t;

 CircBuf_t RXBUFF;

void Buffer_init(CircBuf_t *cb,uint8_t length);

uint8_t BufFull(CircBuf_t *cb);		//Buffer Full with a return

uint8_t BufEmpty(CircBuf_t *cb);		//Buffer Empty with a return

uint8_t Add_Item(CircBuf_t *cb,uint8_t item);	//Adding an item to buffer without overfill

uint8_t Remove_Item(CircBuf_t *cb);		//Removing an item from the buffer

uint8_t *Allocate(CircBuf_t *cb,uint8_t length);

uint8_t Destroy(CircBuf_t *cb);
#endif // _CIRCBUF_H

