#pragma once


/** @addtogroup  TELINK_BLE_STACK TELINK BLE Stack
 *  @{
 */

/** @addtogroup  SERVICE_MODULE Service
 *  @{
 */


/** @addtogroup  TELINK_AUDIO_Module Telink Audio
 *  @{
 */
 
/** @addtogroup  TELINK_AUDIO_Constant Telink Audio Constants
 *  @{
 */

#define TA_UUID_SERVICE           0x1900    //!< TA service
#define TA_UUID_AUDIO_TYPE        0x2B00    //!< TA audio type
#define TA_UUID_AUDIO_CTRL        0x2B01    //!< TA audio control
#define TA_UUID_AUDIO_DATA        0x2B02    //!< TA audio data

/** @} end of group TELINK_AUDIO_Constant */

 /** @addtogroup  TELINK_AUDIO_Variables Telink Audio Variables
 *  @{
 */
 
 /**
 *  @brief  External variable for Telink Audio service Attribute tables
 */
extern attribute_t ta_AttrTbl[];

/**
 *  @brief  External variable for Telink Audio service attribute size
 */
extern u16         ta_attrSize;


/** @} end of group TELINK_AUDIO_Variables */

 /** @addtogroup  TELINK_AUDIO_Functions Telink Audio APIs
 *  @{
 */
 
/**
 * @brief       API to add telink audio service to gatt.
 *
 * @param[in]   None
 *
 * @return      Status
 */
ble_sts_t ta_addService(void);


/**
 * @brief       API to set audio type
 *
 * @param[in]   type - The specified Audio Type
 *
 * @return      None
 */
void ta_setAudioType(u8 type);

/**
 * @brief       API to set the contol bit
 *
 * @param[in]   ctrl - 1 indication START, 0 indicating STOP
 *
 * @return      None
 */
void ta_setAudioCtrl(u8 ctrl);

/**
 * @brief       API to send audio data
 *
 * @param[in]   connHandle - The handle will send data to
 * @param[in]   data - The audio data
 * @param[in]   len  - The audio length
 *
 * @return      None
 */
void ta_sendAudioData(u16 connHandle, u8* data, u8 len);

/**
 * @brief       API to send the contol bit
 *
 * @param[in]   connHandle - The handle will send data to
 * @param[in]   ctrl - 1 indication START, 0 indicating STOP
 *
 * @return      Status
 */
ble_sts_t ta_sendAudioCtrl(u16 connHandle, u8 ctrl);

/** @} end of group TELINK_AUDIO_Functions */

/** @} end of group TELINK_AUDIO_Module */

/** @} end of group SERVICE_MODULE */

/** @} end of group TELINK_BLE_STACK */