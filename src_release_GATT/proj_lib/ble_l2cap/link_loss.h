
#pragma once

#include "../../proj/tl_common.h"
#include "service.h"

/** @addtogroup  
 *  @{
 */

/** @addtogroup  SERVICE_MODULE Service
 *  @{
 */


/** @addtogroup  LINK_LOST_Module Link Lost
 *  @{
 */
 
/** @addtogroup  LINK_LOST_Constant Link Lost Constants
 *  @{
 */

/**
 *  @brief  Definition for Characteristics UUID
 */

/** @addtogroup Link_Lost_uuid Link Lost Charactersitc UUID
 * @{
 */

#define CHARACTERISTIC_UUID_ALERT_LEVEL                    0x2A06


/**
 *  @brief  Definiton for Alert Level
 */
#define ALERT_LEVEL_NO_ALERT                               0
#define ALERT_LEVEL_MILD_ALERT                             1
#define ALERT_LEVEL_HIGH_ALERT                             2

/** @} end of group Link_Lost_uuid */


/** @} end of group LINK_LOST_Constant */



/** @addtogroup  LINK_LOST_Callbacks Link Lost Callbacks
 *  @{
 */
 
/**
 *  @brief  Definition argument type for Link Loss Level changed callback function
 */
typedef struct {
	u8 level;
} linkLoss_arg_t;


/**
 *  @brief  Definition Link Loss callback function type for user application
 */
typedef void (*linkLoss_levelChangeCb_t)( linkLoss_arg_t *pNewLevel );

/**
 *  @brief  Definition for Service Callbacks
 */
typedef struct {
	linkLoss_levelChangeCb_t  levelChangedCbFunc;    //!< proximity state change callback function
} linkLoss_callbacks_t;

/** @} end of group LINK_LOST_Callbacks */



 /** @addtogroup  LINK_LOST_variables Link Lost Variables
 *  @{
 */
 
 /**
 *  @brief   External variable for link loss service Attribute tables
 */
// extern attribute_t linkLoss_attrTbl[];

/**
 *  @brief   External variable for link loss service attribute size
 */
extern u16         linkLoss_attrSize;


/** @} end of group LINK_LOST_variables */


 /** @addtogroup  LINK_LOST_Functions Link Lost APIs
 *  @{
 */
 
/**
 * @brief       API to add Link Loss service to gatt.
 *
 * @param[in]   linkLossCb - The callback function of link loss service
 *
 * @return      Status
 */
ble_sts_t linkLoss_addService(linkLoss_callbacks_t* linkLossCb);

/**
 * @brief       API to set alert level.
 *              This function will set the attribute value first and check
 *              whether need to notify the Server
 *
 * @param[in]   level - The new alert level
 *
 * @return      Status
 */
ble_sts_t linkLoss_setAlertLevel(u8 level);

/** @} end of group LINK_LOST_Functions */

/** @} end of group LINK_LOST_Module */

/** @} end of group SERVICE_MODULE */
