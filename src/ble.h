/*
 * ble.h
 *
 *  Created on: 1 Oct 2021
 *      Author: nihalt
 *      Attribute: Prof. David Sluiter
 *                 UINT8_TO_BITSTREAM
 *                 UINT32_TO_BITSTREAM
 *                 UINT32_TO_FLOAT
 */

#ifndef SRC_BLE_H_
#define SRC_BLE_H_

// Including header files
#include "sl_bt_api.h"
#include <stdint.h>
#include "sl_bluetooth.h"
#include "gatt_db.h"
#include "timers.h"
#include "app.h"
#include "lcd.h"
#include <math.h>


// Macros
#define UINT8_TO_BITSTREAM(p, n)        { *(p)++ = (uint8_t)(n); } // Converts the 8 bit data into a bit stream
#define UINT32_TO_BITSTREAM(p, n)       { *(p)++ = (uint8_t)(n); *(p)++ = (uint8_t)((n) >> 8); \
                                          *(p)++ = (uint8_t)((n) >> 16); *(p)++ = (uint8_t)((n) >> 24); } // Converts the 32 bit data into a bit stream
#define UINT32_TO_FLOAT(m, e)           (((uint32_t)(m) & 0x00FFFFFFU) | (uint32_t)((int32_t)(e) << 24)) // Converts the 32 bit data into float

// A structure to store the variables and flags
typedef struct {
  // Common for both
  bd_addr myAddress;
  uint8_t myAddressType;


  // For the server implementation
  uint8_t advertisingSetHandle;
  uint8_t connectionHandle;

  bool flag_conection;
  bool flag_indication_temp;
  bool flag_indication_in_progress;

  bool flag_indication_button_state;
  bool flag_bonded;
  bool button_0_flag;
  bool button_1_flag;

  uint8_t button_state_value;

  // For the client implementation
  uint16_t myCharacteristicHandle_temp;
  uint32_t myServiceHandle_temp;


  uint16_t myCharacteristicHandle_button_state;
  uint32_t myServiceHandle_button_state;

} ble_data_struct_t;

// Structure to define the UUID data structure
typedef struct {
  uint8_t id[2];
} uuid;

// Structure to define the UUID data structure
typedef struct {
  uint8_t id[16];
} uuid_custom;


typedef struct
{
  uint32_t charHandle;
  size_t bufferLen;
  uint8_t buffer[5];
} buffer_seq;

// Using the above struct to define the UUID for service and characteristic
static const uuid htm_service_uuid = { .id = {0x09, 0x18}};
static const uuid htm_characterstic_uuid = { .id = {0x1C, 0x2A}};

// Using the above struct to define the UUID for service and characteristic
static const uuid_custom button_state_service_uuid = { .id = {0x89, 0x62, 0x13, 0x2D, 0x2A, 0x65, 0xEC, 0x87, 0x3E, 0x43, 0xC8, 0x38, 0x01, 0x00, 0x00, 0x00}};
static const uuid_custom button_state_characterstic_uuid = { .id = {0x89, 0x62, 0x13, 0x2D, 0x2A, 0x65, 0xEC, 0x87, 0x3E, 0x43, 0xC8, 0x38, 0x02, 0x00, 0x00, 0x00}};



// Function Definition
void ble_handler(sl_bt_msg_t *evt);                                 // Function deals with the blue booting and events
ble_data_struct_t* getBleDataPtr();                                 // Function to get the pointer to the function ble_data_struct_t
void ble_Init(void);                                                // Initializing the blue tooth event
bool serverFound();                                                 // Function to check if the desired server is found or NO
float FLOAT_TO_INT32(const uint8_t *value_start_little_endian);     // Converting the numbers in the buffer to the floating point or integer number

#endif /* SRC_BLE_H_ */
