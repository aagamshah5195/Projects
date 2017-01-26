/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/* buffer.c
 * This file contains Buffer Functions
 * 	NOTE: The structure type of Circular Buffer is defined in buffer.h
 *  Buffer_init -> To initialise the buffer parameters
 *  BufFull -> To check if the buffer is full or not
 *  BufEmpty -> To check if the buffer is empty or not
 *  Add_Item -> To add data in the buffer till it is full and it also checks if there is overflow or not
 *  Remove_Item -> To remove data in the buffer till it is empty and it also checks if there is overflow or not
 *	Allocate -> It allocates a memory space to buffer in heap
 *	Destroy -> It frees the allocated memory
 */

#include "main.h"
#include <malloc.h>

void Buffer_init(CircBuf_t *cb,uint8_t length)
{
	cb->circ_buf = malloc((length)*sizeof(uint8_t));
    cb->length = length;
    cb->circ_bufend=cb->circ_buf+length;
    cb->head = cb->circ_buf;
    cb->tail = cb->circ_buf;
    cb->count = 0;
}
uint8_t BufFull(CircBuf_t *cb)				//Function for Buffer Full
{
	if((cb->head == cb->tail) && (cb->count != 0))
    return 1;
    else
    return 0;
}

uint8_t BufEmpty(CircBuf_t *cb)			//Function for Buffer Empty
{
	 if((cb->count ==0) && (cb->head == cb->tail))
     return 1;
     else
     return 0;
}

uint8_t Add_Item(CircBuf_t *cb,uint8_t item)		//Function for adding an item
{
	if( BufFull(cb))
		{
	        return 0;
		}
//Check whether tail is pointing at the end of the buffer if yes wrap around
	if (cb->head == cb->circ_bufend)
		cb->head = cb->circ_buf;
//Adding data from where head is present and incrementing the tail pointer
    *cb->head = item;
    cb->count++;
    cb->head++;
    return 1;
}

uint8_t Remove_Item(CircBuf_t *cb)			//Function for removing an item from the buffer
{

	if(BufEmpty(cb))
	{
        return 0;
	}
//Removing data from where head is present and incrementing the head pointer

    if (cb->tail == cb->circ_bufend)
    	cb->tail = cb->circ_buf;
    uint8_t item = *cb->tail;
    cb->tail++;
    cb->count--;
    return item;

}

uint8_t *Allocate(CircBuf_t *cb,uint8_t length)
{
	cb->circ_buf = malloc((length)*sizeof(uint8_t));
	return cb->circ_buf;
}

uint8_t Destroy(CircBuf_t *cb)
{
	free(cb->circ_buf);
	return 1;
}

