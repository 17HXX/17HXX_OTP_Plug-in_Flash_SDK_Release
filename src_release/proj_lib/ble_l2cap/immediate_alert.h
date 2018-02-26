
#pragma once

#include "../../proj/tl_common.h"
#include "service.h"
#include "link_loss.h"

/** @addtogroup  
 *  @{
 */

/** @addtogroup  SERVICE_MODULE Service
 *  @{
 */


/** @addtogroup  Immediate_Alert_Module Immediate Alert
 *  @{
 */
 

/** @addtogroup  IMMEDIATE_ALERT_Callbacks Immediate Alert Callbacks
 *  @{
 */

/**
 *  @brief  Definition argument type for level change callback function
 */
typedef struct {
	u8 level;
} immediateAlert_arg_t;


/**
 *  @brief  Definition Immediate Alert callback function type for user application
 */
typedef void (*immediateAlert_levelChangeCb_t)( immediateAlert_arg_t *pNewLevel );

/**
 *  @brief  Definition for Service Callbacks
 */
typedef struct {
	immediateAlert_levelChangeCb_t  levelChangedCbFunc;    //!< proximity state change callback function
} immediateAlert_callbacks_t;

/** @} end of group IMMEDIATE_ALERT_Callbacks */



 /** @addtogroup  IMMEDIATE_ALERT_Variables Immediate Alert Variables
 *  @{
 */
 
 /**
 *  @brief External variable for immediate alert service Attribute tables
 */
extern attribute_t immediateAlert_attrTbl[];

/**
 *  @brief External variable for immediate alert service attribute size
 */
extern u16         immediateAlert_attrSize;

/** @} end of group IMMEDIATE_ALERT_Variables */


 /** @addtogroup  IMMEDIATE_ALERT_Functions Immediate Alert APIs
 *  @{
 */
 
/**
 * @brief       API to add Immediate Alert service to gatt.
 *
 * @param[in]   immediateAlertCb - The callback function of Immediate Alert service
 *
 * @return      Status
 */
ble_sts_t immediateAlert_addService(immediateAlert_callbacks_t* immediateAlertCb);

/**
 * @brief       API to set alert level.
 *              This function will set the attribute value first and check
 *              whether need to notify the Server
 *
 * @param[in]   level - The new alert level
 *
 * @return      Status
 */
ble_sts_t immediateAlert_setLevel(u8 level);

/** @} end of group IMMEDIATE_ALERT_Functions */

/** @} end of group Immediate_Alert_Module */

/** @} end of group SERVICE_MODULE */
