/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*data.h*/

#ifndef _DATA_H
#define _DATA_H
#include<stdint.h>

int8_t *my_iitoa(int8_t * str, int32_t data, int32_t base);
int32_t my_atoi(uint8_t * str);
void dump_memory(uint8_t * start, uint32_t length);
int32_t big_to_little(int32_t data);
int32_t little_to_big(int32_t data);

#endif
