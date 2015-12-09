#define MS3DPRINT_CONFIG_SIZE 24


#define OS_STRING_DESCRIPTOR_SIZE (1+1+14+1+1)
static const uint8_t PROGMEM msos_descriptor[OS_STRING_DESCRIPTOR_SIZE] = {
    0x12,                                               // bLength
    0x03,                                               // bDescriptorType (MSOS20_FEATURE_COMPATIBLE_ID)
    'M', 0x00, 'S', 0x00, 'F', 0x00, 'T', 0x00,         // qwSignature ("MSFT100")
    '1', 0x00, '0', 0x00, '0', 0x00,          
    0x33,                                               // bMS_VendorCode
    0x00                                                // bPad
};

#define MS3DPRINT_OSP_SIZE (4+4+2+0x20+4+MS3DPRINT_CONFIG_SIZE)

#define MS3DPRINT_XPROP_SIZE (4+2+2+2+MS3DPRINT_OSP_SIZE)

#define SIZE_TO_DW(__size)                \
        ((uint32_t)__size) & 0xFF,        \
        (((uint32_t)__size)>>8) & 0xFF,   \
        (((uint32_t)__size)>>16) & 0xFF,  \
        (((uint32_t)__size)>>24) & 0xFF 

// CompatibleID and SubCompatibleID
static const uint8_t PROGMEM ms3dprint_descriptor[40] = {
    0x28, 0x00, 0x00, 0x00,                          // dwLength
    0x00, 0x01,                                      // bcdVersion
    0x04, 0x00,                                      // wIndex
    0x01,                                            // bCount
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,        // RESERVED
    0x00,                                            // bFirstInterfaceNumber
    0x01,                                            // RESERVED
    '3', 'D', 'P', 'R', 'I', 'N', 'T', 0x00,         // compatibleID ("3DPRINT")
                                                     // subCompatibleID
    0x41, 0x78, 0x69, 0x6F, 0x6D, 0x00, 0x00, 0x00   /* Axiom    */  
,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00               // RESERVED
};

// Modifiers to the base configuration
static const uint8_t PROGMEM ms3dprint_properties_descriptor[MS3DPRINT_XPROP_SIZE] = {
    SIZE_TO_DW(MS3DPRINT_XPROP_SIZE),                   // dwLength
    0x00, 0x01,                                         // bcdVersion
    0x05, 0x00,                                         // wIndex
    0x01, 0x00,                                         // wCount
    
    SIZE_TO_DW(MS3DPRINT_OSP_SIZE),                     // dwSize
    0x07, 0x00, 0x00, 0x00,                             // dwPropertyDataType  (1=REG_SZ, 4=REG_DWORD, 7=REG_MULTI_SZ)

    0x20, 0x00,                                         // wPropertyNameLength
    'M', 0x0, 'S', 0x0, '3', 0x0, 'D', 0x0,             // bPropertyName
    'P', 0x0, 'r', 0x0, 'i', 0x0, 'n', 0x0,
    't', 0x0, 'C', 0x0, 'o', 0x0, 'n', 0x0,
    'f', 0x0, 'i', 0x0, 'g', 0x0, 0x0, 0x0,

    SIZE_TO_DW(MS3DPRINT_CONFIG_SIZE),                  // dwPropertyDataLength

    // Data
    0x42, 0x00, 0x61, 0x00, 0x73, 0x00, 0x65, 0x00, 0x3D, 0x00, 0x41, 0x00, 0x78, 0x00, 0x69, 0x00,  /* Base=Axi */  
    0x6F, 0x00, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00                                                   /* om       */  

};

