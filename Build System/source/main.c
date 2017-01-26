/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/
/*main.c*/

#include<stdint.h>
#ifdef FRDM
	#include "projectFRDM_1.h"
#else 
	#include "project_1.h"
#endif

int main()
{
	project_1_report();
	return 1;
}
