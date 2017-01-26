/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*memory.h*/

#ifndef _MEMORY_H
#define _MEMORY_H
#include <stdint.h>

int8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length);
int8_t my_memzero(uint8_t * src, uint32_t length);
int8_t my_reverse(uint8_t * src, uint32_t length);

#endif // _MEMORY_H
