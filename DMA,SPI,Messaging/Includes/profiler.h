/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/
/*
 * profiler.h
 *
 *  Created on: Oct 11, 2016
 */
 
#ifndef INCLUDES_PROFILER_H_
#define INCLUDES_PROFILER_H_

#include "system_MKL25Z4.h"


#define MOD_VAL 65535
#define T1CLK  	21

void start(void);
void end(void);
void profiler(void);
void profile_BBB(void);

#endif /* INCLUDES_PROFILER_H_ */
