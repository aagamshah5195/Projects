/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/
/*
 * USBHAL.H
 *  Created on: Nov 30, 2016
 *  USB header files are leveraged from "Mbed.com" and written in C
 */

#ifndef INCLUDES_USBHAL_H_
#define INCLUDES_USBHAL_H_

#ifndef USBBUSINTERFACE_H
#define USBBUSINTERFACE_H

//#include "mbed.h"
#include "USBEndpoints.h"

#ifdef __GNUC__
#define __packed __attribute__ ((__packed__))
#endif

#define false 0
//class USBHAL {
//public:
    /* Configuration */
    void USBHAL();
    //~USBHAL();
    void connect(void);
    void disconnect(void);
    void configureDevice(void);
    void unconfigureDevice(void);
    void setAddress(uint8_t address);
    void remoteWakeup(void);

    /* Endpoint 0 */
    void EP0setup(uint8_t *buffer);
    void EP0read(void);
    void EP0readStage(void);
    uint32_t EP0getReadResult(uint8_t *buffer);
    void EP0write(uint8_t *buffer, uint32_t size);
    void EP0getWriteResult(void);
    void EP0stall(void);

    /* Other endpoints */
    EP_STATUS endpointRead(uint8_t endpoint, uint32_t maximumSize);
    EP_STATUS endpointReadResult(uint8_t endpoint, uint8_t *data, uint32_t *bytesRead);
    EP_STATUS endpointWrite(uint8_t endpoint, uint8_t *data, uint32_t size);
    EP_STATUS endpointWriteResult(uint8_t endpoint);
    void stallEndpoint(uint8_t endpoint);
    void unstallEndpoint(uint8_t endpoint);
    uint8_t realiseEndpoint(uint8_t endpoint, uint32_t maxPacket, uint32_t options);
    uint8_t getEndpointStallState(unsigned char endpoint);
    uint32_t endpointReadcore(uint8_t endpoint, uint8_t *buffer);

//protected:
/*      void busReset(void){};
      void EP0setupCallback(void){};
      void EP0out(void){};
      void EP0in(void){};
      void connectStateChanged(unsigned int connected){};
      void suspendStateChanged(unsigned int suspended){};
      void SOF(int frameNumber){};

      uint8_t EP1_OUT_callback(){return false;};
      uint8_t EP1_IN_callback(){return false;};
      uint8_t EP2_OUT_callback(){return false;};
      uint8_t EP2_IN_callback(){return false;};
      uint8_t EP3_OUT_callback(){return false;};
      uint8_t EP3_IN_callback(){return false;};
      uint8_t EP4_OUT_callback(){return false;};
      uint8_t EP4_IN_callback(){return false;};

#if !defined(TARGET_LPC11U24)
      uint8_t EP5_OUT_callback(){return false;};
      uint8_t EP5_IN_callback(){return false;};
      uint8_t EP6_OUT_callback(){return false;};
      uint8_t EP6_IN_callback(){return false;};
      uint8_t EP7_OUT_callback(){return false;};
      uint8_t EP7_IN_callback(){return false;};
      uint8_t EP8_OUT_callback(){return false;};
      uint8_t EP8_IN_callback(){return false;};
      uint8_t EP9_OUT_callback(){return false;};
      uint8_t EP9_IN_callback(){return false;};
      uint8_t EP10_OUT_callback(){return false;};
      uint8_t EP10_IN_callback(){return false;};
      uint8_t EP11_OUT_callback(){return false;};
      uint8_t EP11_IN_callback(){return false;};
      uint8_t EP12_OUT_callback(){return false;};
      uint8_t EP12_IN_callback(){return false;};
      uint8_t EP13_OUT_callback(){return false;};
      uint8_t EP13_IN_callback(){return false;};
      uint8_t EP14_OUT_callback(){return false;};
      uint8_t EP14_IN_callback(){return false;};
      uint8_t EP15_OUT_callback(){return false;};
      uint8_t EP15_IN_callback(){return false;};
#endif
*/
//private:
    void usbisr(void);
  //  static void _usbisr(void);
  //  static USBHAL * instance;

/*#if defined(TARGET_LPC11U24)
        uint8_t (USBHAL::*epCallback[10 - 2])(void);
#else
        uint8_t (USBHAL::*epCallback[32 - 2])(void);
#endif


};*/
#endif




#endif /* INCLUDES_USBHAL_H_ */
