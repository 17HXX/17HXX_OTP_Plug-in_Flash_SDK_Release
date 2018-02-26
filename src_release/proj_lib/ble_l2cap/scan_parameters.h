
#pragma once

#include "../../proj/tl_common.h"
#include "service.h"

/** @addtogroup  
 *  @{
 */

/** @addtogroup  SERVICE_MODULE Service
 *  @{
 */


/** @addtogroup  SCAN_PARAMETERS_Module scan parameters
 *  @{
 */
 
/** @addtogroup  SCAN_PARAMETERS_Constant Scan Parameters Constants
 *  @{
 */

/**
 *  @brief  Definition for Characteristics UUID
 */

/** @addtogroup Scan_Parameters_uuid Scan Parameters Charactersitc UUID
 * @{
 */

#define CHARACTERISTIC_UUID_SCAN_INTERVAL_WINDOW                0x2A4F
#define CHARACTERISTIC_UUID_SCAN_REFRESH                        0x2A31

/** @} end of group Scan_Parameters_uuid */


/** @} end of group SCAN_PARAMETERS_Constant */



/** @addtogroup SCAN_PARAMETERS_Callbacks Scan Parameters Callbacks
 *  @{
 */
 
 /**
 *  @brief   
 */
 typedef struct {
	u16 scanInterval;
	u16 scanWindow;
} scan_intervalWindow_t;

/**
 *  @brief  Definition intercal window write callback function type for user application. 
 */
typedef void (*scanParam_intervalWin_t)(scan_intervalWindow_t value);

/**
 *  @brief  Definition for foundation command callbacks.
 */
typedef struct {
	scanParam_intervalWin_t  intervalWinCbFunc;    //!< proximity state change callback function
} scanParam_callbacks_t;

/** @} end of group SCAN_PARAMETERS_Callbacks */



 /** @addtogroup  SCAN_PARAMETERS_Varibales Scan Parameters Variables
 *  @{
 */
 
 /**
 *  @brief  External variable for scan parameter service Attribute tables
 */
extern attribute_t scanPara_attrTbl[];

/**
 *  @brief  External variable for scan parameter service attribute size
 */
extern u16         scanPara_attrSize;

/** @} end of group SCAN_PARAMETERS_Varibales */


 /** @addtogroup  SCAN_PARAMETERS_Functions Scan Parameters APIs
 *  @{
 */
 
/**
 * @brief       API to add scan parameter service to gatt.
 *
 * @param[in]   scanParamCb - The callback function of scan parameter service
 *
 * @return      Status
 */
ble_sts_t scanPara_addService(scanParam_callbacks_t* scanParamCb);

/** @} end of group SCAN_PARAMETERS_Functions */

/** @} end of group SCAN_PARAMETERS_Module */

/** @} end of group SERVICE_MODULE */
