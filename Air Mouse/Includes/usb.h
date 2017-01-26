/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/
/*
 * usb.h
 *  Created on: Nov 30, 2016
 *  USB header files are leveraged from "Mbed.org" and written in C
 */
#ifndef USBMOUSE_H
#define USBMOUSE_H

#include "USBHID.h"

#define REPORT_ID_MOUSE   2

/* Common usage */

enum MOUSE_BUTTON
{
    MOUSE_LEFT = 1,
    MOUSE_RIGHT = 2,
    MOUSE_MIDDLE = 4,
};

typedef enum
{
    ABS_MOUSE,
    REL_MOUSE,
}MOUSE_TYPE;

/* X and Y limits */
/* These values do not directly map to screen pixels */
/* Zero may be interpreted as meaning 'no movement' */
#define X_MIN_ABS    (1)        /*!< Minimum value on x-axis */
#define Y_MIN_ABS    (1)        /*!< Minimum value on y-axis */
#define X_MAX_ABS    (0x7fff)   /*!< Maximum value on x-axis */
#define Y_MAX_ABS    (0x7fff)   /*!< Maximum value on y-axis */

#define X_MIN_REL    (-127)     /*!< The maximum value that we can move to the left on the x-axis */
#define Y_MIN_REL    (-127)     /*!< The maximum value that we can move up on the y-axis */
#define X_MAX_REL    (127)      /*!< The maximum value that we can move to the right on the x-axis */
#define Y_MAX_REL    (127)      /*!< The maximum value that we can move down on the y-axis */



#define NUMBER_OF_LOGICAL_ENDPOINTS (16)
#define NUMBER_OF_PHYSICAL_ENDPOINTS (NUMBER_OF_LOGICAL_ENDPOINTS * 2)



/*      Endpoint    No.   */
typedef enum{
  EP0OUT=0,
  EP0IN=1,
  EP1OUT=2,
  EP1IN=3,
  EP2OUT=4,
  EP2IN=5,
  EP3OUT=6,
  EP3IN=7,
  EP4OUT=8,
  EP4IN=9,
  EP5OUT=10,
  EP5IN=11,
  EP6OUT=12,
  EP6IN=13,
  EP7OUT=14,
  EP7IN=15,
  EP8OUT=16,
  EP8IN=17,
  EP9OUT=18,
  EP9IN=19,
  EP10OUT=20,
  EP10IN=21,
  EP11OUT=22,
  EP11IN=23,
  EP12OUT=24,
  EP12IN=25,
  EP13OUT=26,
  EP13IN=27,
  EP14OUT=28,
  EP14IN=29,
  EP15OUT=30,
  EP15IN=31}ENDPOINT_NO;

/* Maximum Packet sizes */

#define MAX_PACKET_SIZE_EP0  (64)
#define MAX_PACKET_SIZE_EP1  (64)
#define MAX_PACKET_SIZE_EP2  (64)
#define MAX_PACKET_SIZE_EP3  (1023)
#define MAX_PACKET_SIZE_EP4  (64)
#define MAX_PACKET_SIZE_EP5  (64)
#define MAX_PACKET_SIZE_EP6  (64)
#define MAX_PACKET_SIZE_EP7  (64)
#define MAX_PACKET_SIZE_EP8  (64)
#define MAX_PACKET_SIZE_EP9  (64)
#define MAX_PACKET_SIZE_EP10 (64)
#define MAX_PACKET_SIZE_EP11 (64)
#define MAX_PACKET_SIZE_EP12 (64)
#define MAX_PACKET_SIZE_EP13 (64)
#define MAX_PACKET_SIZE_EP14 (64)
#define MAX_PACKET_SIZE_EP15 (64)

/* Generic endpoints - intended to be portable accross devices */
/* and be suitable for simple USB devices. */

/* Bulk endpoints */
#define EPBULK_OUT  (EP2OUT)
#define EPBULK_IN   (EP2IN)
/* Interrupt endpoints */
#define EPINT_OUT   (EP1OUT)
#define EPINT_IN    (EP1IN)
/* Isochronous endpoints */
#define EPISO_OUT   (EP3OUT)
#define EPISO_IN    (EP3IN)

#define MAX_PACKET_SIZE_EPBULK  (MAX_PACKET_SIZE_EP2)
#define MAX_PACKET_SIZE_EPINT   (MAX_PACKET_SIZE_EP1)
#define MAX_PACKET_SIZE_EPISO   (MAX_PACKET_SIZE_EP3)

uint8_t update(int16_t x, int16_t y, uint8_t buttons, int8_t z);
uint8_t move(int16_t x, int16_t y);
uint8_t press(uint8_t button);
uint8_t release(uint8_t button);
uint8_t doubleClick();
uint8_t click(uint8_t button);
uint8_t scroll(int8_t z);
uint8_t * reportDesc();
uint8_t * configurationDesc();
uint8_t mouseSend(int8_t x, int8_t y, uint8_t buttons, int8_t z);

#endif
