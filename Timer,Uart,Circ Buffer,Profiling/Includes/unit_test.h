/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * unit_test.h
 *
 *  Created on: Oct 12, 2016
 */

#ifndef INCLUDES_UNIT_TEST_H_
#define INCLUDES_UNIT_TEST_H_


void buffer_test(void);
void empty_buffer(CircBuf_t *cptr);
void full_buffer(CircBuf_t *cptr,uint8_t data);

#endif /* INCLUDES_UNIT_TEST_H_ */
