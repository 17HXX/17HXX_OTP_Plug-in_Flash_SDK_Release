
#pragma once

#include "../../proj/tl_common.h"
#include "service.h"


/** @addtogroup  
 *  @{
 */

/** @addtogroup  SERVICE_MODULE Service
 *  @{
 */


/** @addtogroup  BATTERY_SERVICE_Module Battery Service
 *  @{
 */
 
/** @addtogroup  BATTERY_SERVICE_Constant Battery Service Constants
 *  @{
 */

/**
 *  @brief  Definition for Characteristics UUID
 */

/** @addtogroup battery_char_uuid Battery Characteristic UUID
 * @{
 */
#define CHARACTERISTIC_UUID_BATTERY_LEVEL                    0x2A19

/** @} end of group battery_char_uuid */


/** @} end of group BATTERY_SERVICE_Constant */


/** @addtogroup  BATTERY_SERVICE_Callbacks Battery Service Callbacks
 *  @{
 */


/**
 *  @brief  Definition Battery level client characterist configuration change callback function type for user application
 */
typedef void (*battery_clientCharCfgChangeCb_t)(u32 fNoti);

/**
 *  @brief  Definition for foundation command callbacks.
 */
typedef struct {
	battery_clientCharCfgChangeCb_t  cccChangedCbFunc;    //!< ccc of battery level change callback function
} battery_callbacks_t;


/** @} end of group BATTERY_SERVICE_Callbacks */




/** @addtogroup  BATTERY_SERVICE_Variables Battery Service Variables
 *  @{
 */

/**
 *  @brief  External variable for battery Attribute tables
 */
extern attribute_t battery_attrTbl[];

/**
 *  @brief  External variable for battery attribute size
 */
extern u16         battery_attrSize;

/** @} end of group BATTERY_SERVICE_Variables */



/** @addtogroup  BATTERY_SERVICE_Fountions Battery Service APIs
 *  @{
 */


/**
 * @brief       API to add battery service to gatt.
 *
 * @param[in]   batteryCb - The callback function of battery service
 *
 * @return      Status
 */
ble_sts_t battery_addService(battery_callbacks_t* batteryCb);


/**
 * @brief       API to send battery level notification
 *
 * @param[in]   connHandle - The connection handle this notification will send to.
 *
 * @return      Status
 */
ble_sts_t battery_levelNotify(u16 connHandle);


/** @} end of group BATTERY_SERVICE_Fountions */

/** @} end of group BATTERY_SERVICE_Module */

/** @} end of group SERVICE_MODULE */
