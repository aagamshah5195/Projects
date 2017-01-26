/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/
/*
 * USBDevice.h
 *  Created on: Nov 30, 2016
 *  USB header files are leveraged from "Mbed.org" and written in C
 */

#ifndef INCLUDES_USBDEVICE_H_
#define INCLUDES_USBDEVICE_H_


#ifndef USBDEVICE_H
#define USBDEVICE_H

//#include "mbed.h"
#include "USBDevice_Types.h"
#include "USBHAL.h"

//class USBDevice: public USBHAL
//{
//public:
    int USBDevice(uint16_t vendor_id, uint16_t product_id, uint16_t product_release);

    /*
    * Check if the device is configured
    *
    * @returns true if configured, false otherwise
    */
    uint8_t configured(void);

    /*
    * Connect a device
    */
    void connect(void);

    /*
    * Disconnect a device
    */
    void disconnect(void);

    /*
    * Add an endpoint
    *
    * @param endpoint endpoint which will be added
    * @param maxPacket Maximum size of a packet which can be sent for this endpoint
    * @returns true if successful, false otherwise
    */
    uint8_t addEndpoint(uint8_t endpoint, uint32_t maxPacket);

    /*
    * Start a reading on a certain endpoint.
    * You can access the result of the reading by USBDevice_read
    *
    * @param endpoint endpoint which will be read
    * @param maxSize the maximum length that can be read
    * @return true if successful
    */
    uint8_t readStart(uint8_t endpoint, uint32_t maxSize);

    /*
    * Read a certain endpoint. Before calling this function, USBUSBDevice_readStart
    * must be called.
    *
    * Warning: blocking
    *
    * @param endpoint endpoint which will be read
    * @param buffer buffer will be filled with the data received
    * @param size the number of bytes read will be stored in *size
    * @param maxSize the maximum length that can be read
    * @returns true if successful
    */
    uint8_t readEP(uint8_t endpoint, uint8_t * buffer, uint32_t * size, uint32_t maxSize);

    /*
    * Read a certain endpoint.
    *
    * Warning: non blocking
    *
    * @param endpoint endpoint which will be read
    * @param buffer buffer will be filled with the data received (if data are available)
    * @param size the number of bytes read will be stored in *size
    * @param maxSize the maximum length that can be read
    * @returns true if successful
    */
    uint8_t readEP_NB(uint8_t endpoint, uint8_t * buffer, uint32_t * size, uint32_t maxSize);

    /*
    * Write a certain endpoint.
    *
    * Warning: blocking
    *
    * @param endpoint endpoint to write
    * @param buffer data contained in buffer will be write
    * @param size the number of bytes to write
    * @param maxSize the maximum length that can be written on this endpoint
    */
    uint8_t write(uint8_t endpoint, uint8_t * buffer, uint32_t size, uint32_t maxSize);


    /*
    * Write a certain endpoint.
    *
    * Warning: non blocking
    *
    * @param endpoint endpoint to write
    * @param buffer data contained in buffer will be write
    * @param size the number of bytes to write
    * @param maxSize the maximum length that can be written on this endpoint
    */
    uint8_t writeNB(uint8_t endpoint, uint8_t * buffer, uint32_t size, uint32_t maxSize);


    /*
    * Called by USBDevice layer on bus reset. Warning: Called in ISR context
    *
    * May be used to reset state
    */
   //   void USBCallback_busReset(void) {};

    /*
    * Called by USBDevice on Endpoint0 request. Warning: Called in ISR context
    * This is used to handle extensions to standard requests
    * and class specific requests
    *
    * @returns true if class handles this request
    */
   //   uint8_t USBCallback_request() { return false; };

    /*
    * Called by USBDevice on Endpoint0 request completion
    * if the 'notify' flag has been set to true. Warning: Called in ISR context
    *
    * In this case it is used to indicate that a HID report has
    * been received from the host on endpoint 0
    *
    * @param buf buffer received on endpoint 0
    * @param length length of this buffer
    */
    //  void USBCallback_requestCompleted(uint8_t * buf, uint32_t length) {};

    /*
    * Called by USBDevice layer. Set configuration of the device.
    * For instance, you can add all endpoints that you need on this function.
    *
    * @param configuration Number of the configuration
    */
   //   uint8_t USBCallback_setConfiguration(uint8_t configuration) { return false; };

    /*
     * Called by USBDevice layer. Set interface/alternate of the device.
     *
     * @param interface Number of the interface to be configured
     * @param alternate Number of the alternate to be configured
     * @returns true if class handles this request
     */
    //  uint8_t USBCallback_setInterface(uint16_t interface, uint8_t alternate) { return false; };

    /*
    * Get device descriptor. Warning: this method has to store the length of the report descriptor in reportLength.
    *
    * @returns pointer to the device descriptor
    */
      uint8_t * deviceDesc();

    /*
    * Get configuration descriptor
    *
    * @returns pointer to the configuration descriptor
    */
//      uint8_t * configurationDesc(){return 0;};

    /*
    * Get string lang id descriptor
    *
    * @return pointer to the string lang id descriptor
    */
      uint8_t * stringLangidDesc();

    /*
    * Get string manufacturer descriptor
    *
    * @returns pointer to the string manufacturer descriptor
    */
      uint8_t * stringImanufacturerDesc();

    /*
    * Get string product descriptor
    *
    * @returns pointer to the string product descriptor
    */
      uint8_t * stringIproductDesc();

    /*
    * Get string serial descriptor
    *
    * @returns pointer to the string serial descriptor
    */
      uint8_t * stringIserialDesc();

    /*
    * Get string configuration descriptor
    *
    * @returns pointer to the string configuration descriptor
    */
      uint8_t * stringIConfigurationDesc();

    /*
    * Get string interface descriptor
    *
    * @returns pointer to the string interface descriptor
    */
      uint8_t * stringIinterfaceDesc();

    /*
    * Get the length of the report descriptor
    *
    * @returns length of the report descriptor
    */
  //    uint16_t reportDescLength() { return 0; };



//protected:
      void busReset(void);
      void EP0setupCallback(void);
      void EP0out(void);
      void EP0in(void);
      void connectStateChanged(unsigned int connected);
      void suspendStateChanged(unsigned int suspended);
    uint8_t * findDescriptor(uint8_t descriptorType);
    CONTROL_TRANSFER * getTransferPtr(void);

    uint16_t VENDOR_ID;
    uint16_t PRODUCT_ID;
    uint16_t PRODUCT_RELEASE;

//private:
    uint8_t addRateFeedbackEndpoint(uint8_t endpoint, uint32_t maxPacket);
    uint8_t requestGetDescriptor(void);
    uint8_t controlOut(void);
    uint8_t controlIn(void);
    uint8_t requestSetAddress(void);
    uint8_t requestSetConfiguration(void);
    uint8_t requestSetFeature(void);
    uint8_t requestClearFeature(void);
    uint8_t requestGetStatus(void);
    uint8_t requestSetup(void);
    uint8_t controlSetup(void);
    void decodeSetupPacket(uint8_t *data, SETUP_PACKET *packet);
    uint8_t requestGetConfiguration(void);
    uint8_t requestGetInterface(void);
    uint8_t requestSetInterface(void);

    CONTROL_TRANSFER transfer;
    USB_DEVICE device;

    uint16_t currentInterface;
    uint8_t currentAlternate;
//};


#endif

#endif /* INCLUDES_USBDEVICE_H_ */
