/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * main.h
 *  Created on: Oct 7, 2016
 */
 
#ifndef INCLUDES_MAIN_H_
#define INCLUDES_MAIN_H_

#include "uart.h"
#include <stdint.h>
#include <sys/time.h>
#include <MKL25Z4.h>
#include "math.h"
#include "buffer.h"
#include "log.h"
#include <string.h>
#include "profiler.h"
#include "memory.h"
#include "data.h"
#include "unit_test.h"

#define Max 20
extern int data;
extern int8_t next_colour;
extern float B;

/*------------------------------------------------------------------------------*/
 // SWITCH CASES
  #define DEBUG 			// macro to enable log function (FRDM/BBB)
  #define FRDM	 			// macro for serial debug (FRDM)
 // #define BBB   			// macro for printf debug (BBB)
 // #define RGB_TEST	   	// macro to test RGB LED
 // #define BUFFER			// macro to attach circular buffers to uart
 // #define LOGGER_TEST		// macro to disable log test samples
  #define PROFILE_TEST	// macro to disable profile test
 // #define UNIT_TEST		// macro to disable unit test for circular buffer
/*---------------------------------------------------------------------------------*/

#endif /* INCLUDES_MAIN_H_ */
