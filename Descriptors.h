/*
             LUFA Library
     Copyright (C) Dean Camera, 2010.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2010  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this 
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in 
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting 
  documentation, and that the name of the author not be used in 
  advertising or publicity pertaining to distribution of the 
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Header file for Descriptors.c.
 */
 
#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

    /* Includes: */
        #include <avr/pgmspace.h>

        #include <LUFA/Drivers/USB/USB.h>
        #include <LUFA/Drivers/USB/Class/CDC.h>

        /* Enums */
        enum registry_props_type
        {
            REG_SZ = 1,
            REG_EXPAND_SZ,
            REG_BINARY,
            REG_DWORD_LITTLE_ENDIAN,
            REG_DWORD_BIG_ENDIAN,
            REG_LINK,
            REG_MULTI_SZ,
        };

    /* Product-specific definitions: */
        #define ARDUINO_UNO_PID             0x0001
        #define ARDUINO_MEGA2560_PID        0x0010

        /** Device control request used for retrieving the OS Feature descriptors of the device. */
        #define REQ_GetOSFeatureDescriptor       0x20

        /** Descriptor index for a Microsoft Proprietary Extended Device Compatibility descriptor. */
        #define EXTENDED_COMPAT_ID_DESCRIPTOR    0x0004

        /** Descriptor index for a Microsoft Proprietary Extended Device Properties OS Feature Descriptor. */
        #define EXTENDED_PROPERTIES_DESCRIPTOR   0x0005

        #define WCID_IF_NUMBER         0

		#define NB_PROPERTIES 1

    	/* Macros: */
        /** Endpoint number of the CDC device-to-host notification IN endpoint. */
        #define CDC_NOTIFICATION_EPNUM         2

        /** Endpoint number of the CDC device-to-host data IN endpoint. */
        #define CDC_TX_EPNUM                   3    

        /** Endpoint number of the CDC host-to-device data OUT endpoint. */
        #define CDC_RX_EPNUM                   4    

        /** Size in bytes of the CDC device-to-host notification IN endpoint. */
        #define CDC_NOTIFICATION_EPSIZE        8

        /** Size in bytes of the CDC data IN and OUT endpoints. */
        #define CDC_TXRX_EPSIZE                64   

    	/* Type Defines: */
        /** Type define for the device configuration descriptor structure. This must be defined in the
         *  application code, as the configuration descriptor contains several sub-descriptors which
         *  vary between devices, and which describe the device's usage to the host.
         */
        typedef struct
        {
            USB_Descriptor_Configuration_Header_t    Config;
            USB_Descriptor_Interface_t               CDC_CCI_Interface;
            CDC_FUNCTIONAL_DESCRIPTOR(2)             CDC_Functional_IntHeader;
            CDC_FUNCTIONAL_DESCRIPTOR(1)             CDC_Functional_AbstractControlManagement;
            CDC_FUNCTIONAL_DESCRIPTOR(2)             CDC_Functional_Union;
            USB_Descriptor_Endpoint_t                CDC_NotificationEndpoint;
            USB_Descriptor_Interface_t               CDC_DCI_Interface;
            USB_Descriptor_Endpoint_t                CDC_DataOutEndpoint;
            USB_Descriptor_Endpoint_t                CDC_DataInEndpoint;
        } USB_Descriptor_Configuration_t;

        typedef struct
        {
            USB_Descriptor_Header_t                Header;
            int                                    Signature[7];
            uint8_t                                VendorCode;
            uint8_t                                Reserved;
        } USB_OSDescriptor_t;

        typedef struct
        {
            uint8_t                                FirstInterfaceNumber;
            uint8_t                                Reserved;
            uint8_t                                CompatibleID[8];
            uint8_t                                SubCompatibleID[8];
            uint8_t                                Reserved2[6];
        } USB_OSCompatibleSection_t;

        typedef struct
        {
            uint32_t                               TotalLength;
            uint16_t                               Version;
            uint16_t                               Index;
            uint8_t                                TotalSections;
            uint8_t                                Reserved[7];
            USB_OSCompatibleSection_t              CompatID;
        } USB_OSCompatibleIDDescriptor_t;

        typedef struct
        {
            uint16_t                               Length;
            wchar_t                                Value[];
        } USB_OSPropertiesName_t;

        typedef struct
        {
            uint32_t                               Length;
            wchar_t                                Value[];
        } USB_OSPropertiesData_t;

        typedef struct
        {
            uint32_t                               TotalLength;
            uint16_t                               Version;
            uint16_t                               Index;
            uint16_t                               TotalSections;
        } USB_OSPropertiesHeader_t;

        typedef struct
        {
            uint32_t                               Length;
            uint32_t                               Type;
            USB_OSPropertiesName_t                 Name;
            USB_OSPropertiesData_t                 Data;
        } USB_OSPropertiesSection_t;

        typedef struct
        {
            USB_OSPropertiesHeader_t               Header;
            USB_OSPropertiesSection_t              Property[NB_PROPERTIES];
        } USB_OSPropertiesDescriptor_t;

    /* Function Prototypes: */
        uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                            const uint8_t wIndex,
                                            void** const DescriptorAddress) ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

        uint16_t USB_GetOSFeatureDescriptor(const uint8_t InterfaceNumber,
            const uint8_t wIndex,
            const uint8_t Recipient,
            const void** const DescriptorAddress)
            ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(4);

#endif
