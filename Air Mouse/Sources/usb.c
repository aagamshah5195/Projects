/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/* usb.c
 * This file contains USB driver for  mouse application
 * It controls update of direction and movement of mouse pointer
 * Functions of clicking, scrolling and double clicking are also described here
 * Other USBHID header files are leveraged from "Mbed.com"
 */

#include "stdint.h"
#include "usb.h"
#include "USBHID_Types.h"

HID_REPORT report;
MOUSE_TYPE mouse_type;
uint8_t button;

/*
 * Function to update the direction of mouse pointer
 * Parameters:X,Y,Z coordinates of accelerometer
 * 				Button: Left,Right or Center which is pressed
 */
uint8_t update(int16_t x, int16_t y, uint8_t button, int8_t z) {
    switch (mouse_type) {
        case REL_MOUSE:
            while (x > 127) {
                if (!mouseSend(127, 0, button, z)) return false;
                x = x - 127;
            }
            while (x < -128) {
                if (!mouseSend(-128, 0, button, z)) return false;
                x = x + 128;
            }
            while (y > 127) {
                if (!mouseSend(0, 127, button, z)) return false;
                y = y - 127;
            }
            while (y < -128) {
                if (!mouseSend(0, -128, button, z)) return false;
                y = y + 128;
            }
            return mouseSend(x, y, button, z);

        case ABS_MOUSE:

            report.data[0] = x & 0xff;
            report.data[1] = (x >> 8) & 0xff;
            report.data[2] = y & 0xff;
            report.data[3] = (y >> 8) & 0xff;
            report.data[4] = -z;
            report.data[5] = button & 0x07;

            report.length = 6;

            return send(&report);
        default:
            return false;
    }
}

/*
 * Function to update the direction of mouse pointer
 * Parameters:X,Y,Z coordinates of accelerometer
 * 				Button: Left,Right or Center which is pressed
 */
uint8_t mouseSend(int8_t x, int8_t y, uint8_t buttons, int8_t z) {
    HID_REPORT report;
    report.data[0] = buttons & 0x07;
    report.data[1] = x;
    report.data[2] = y;
    report.data[3] = -z; // >0 to scroll down, <0 to scroll up

    report.length = 4;

    return send(&report);
}

/*
 * Function to move the direction of mouse pointer
 * Parameters:X,Y coordinates of accelerometer
 *
 */
uint8_t move(int16_t x, int16_t y) {
    return update(x, y, button, 0);
}

/*
 * Function to scroll the pointer
 * Parameters: Z coordinate of the accelerometer
 */
uint8_t scroll(int8_t z) {
    return update(0, 0, button, z);
}

//Function to check for double click for selecting an option
uint8_t doubleClick() {
    if (!click(MOUSE_LEFT))
        return false;
   // wait(0.1);
    return click(MOUSE_LEFT);
}
//Function to check for click for selecting an option
uint8_t click(uint8_t button) {
    if (!update(0, 0, button, 0))
        return false;
  //  wait(0.01);
    return update(0, 0, 0, 0);
}

//Function to detect if button is pressed
uint8_t press(uint8_t button_) {
    button = button_ & 0x07;
    return update(0, 0, button, 0);
}

//Function to detect is button is released after pressing
uint8_t release(uint8_t button_) {

    button = (button & (~button_)) & 0x07;
    return update(0, 0, button, 0);
}


