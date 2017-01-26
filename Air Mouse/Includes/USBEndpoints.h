/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/
/*
 * USBEndpoints.h
 *  Created on: Nov 30, 2016
 *  USB header files are leveraged from "Mbed.org" and written in C
 */

#ifndef INCLUDES_USBENDPOINTS_H_
#define INCLUDES_USBENDPOINTS_H_

#ifndef USBENDPOINTS_H
#define USBENDPOINTS_H

/* SETUP packet size */
#define SETUP_PACKET_SIZE (8)

/* Options flags for configuring endpoints */
#define DEFAULT_OPTIONS     (0)
#define SINGLE_BUFFERED     (1U << 0)
#define ISOCHRONOUS         (1U << 1)
#define RATE_FEEDBACK_MODE  (1U << 2) /* Interrupt endpoints only */

/* Endpoint transfer status, for endpoints > 0 */
typedef enum {
    EP_COMPLETED,   /* Transfer completed */
    EP_PENDING,     /* Transfer in progress */
    EP_INVALID,     /* Invalid parameter */
    EP_STALLED,     /* Endpoint stalled */
} EP_STATUS;

/* Include configuration for specific target */
#if defined(TARGET_LPC1768) || defined(TARGET_LPC2368) || defined(TARGET_LPC4088)
#include "USBEndpoints_LPC17_LPC23.h"
#elif defined(TARGET_LPC11U24)
#include "USBEndpoints_LPC11U.h"
#elif defined(TARGET_KL25Z)
#include "USBEndpoints_KL25Z.h"
//#else
//#error "Unknown target type"
#endif

#endif




#endif /* INCLUDES_USBENDPOINTS_H_ */
