
#pragma once

#include "../../proj/tl_common.h"
#include "service.h"

/** @addtogroup  
 *  @{
 */

/** @addtogroup  SERVICE_MODULE Service
 *  @{
 */


/** @addtogroup  TXPOWER_Module Txpower
 *  @{
 */
 
/** @addtogroup  TXPOWER_Constant Txpower Constants
 *  @{
 */

/**
 *  @brief  Definition for Characteristics UUID
 */

/** @addtogroup Txpower_uuid Txpower Charactersitc UUID
 * @{
 */
#define CHARACTERISTIC_UUID_TX_POWER_LEVEL                    0x2A07

/**
 *  @brief  Definition for TX Power Level Range
 */
#define TX_POWER_MIN                                          -100
#define TX_POWER_MAX                                          20


/** @} end of group Txpower_uuid */

/** @} end of group SCAN_PARAMETERS_Constant */

 /** @addtogroup  TXPOWER_Varibales Txpower Variables
 *  @{
 */
 
 /**
 *  @brief  External variable for TX power service Attribute tables
 */
extern attribute_t txPower_attrTbl[];

 /**
 *  @brief  External variable for TX power service attribute size
 */
extern u16         txPower_attrSize;

/** @} end of group TXPOWER_Varibales */


 /** @addtogroup  TXPOWER_Functions Txpower APIs
 *  @{
 */
 
/**
 * @brief       API to add TXPOWER service to gatt.
 *
 * @param[in]   None
 *
 * @return      Status
 */
ble_sts_t txPower_addService(void);

/**
 * @brief       API to set TX power level
 *
 * @param[in]   level - The specifed power level
 *
 * @return      Status
 */
ble_sts_t txPower_setLevel(u8 level);

/** @} end of group TXPOWER_Functions */

/** @} end of group TXPOWER_Module */

/** @} end of group SERVICE_MODULE */
