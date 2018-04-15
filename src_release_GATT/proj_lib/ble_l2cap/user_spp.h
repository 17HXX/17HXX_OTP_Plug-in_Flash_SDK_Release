#pragma once


/** @addtogroup  TELINK_BLE_STACK TELINK BLE Stack
 *  @{
 */

/** @addtogroup  SERVICE_MODULE Service
 *  @{
 */


/** @addtogroup  TELINK_SPP_Module Telink Spp
 *  @{
 */
 
/** @addtogroup  TELINK_SPP_Constant Telink Spp Constants
 *  @{
 */

#define TELINK_SPP_UUID_SERVICE   0x1910    //!< TELINK_SPP service
#define TELINK_SPP_DATA_SERVER2CLIENT 0x2B10 //!< TELINK_SPP data from server to client
#define TELINK_SPP_DATA_CLIENT2SERVER 0x2B11 //!< TELINK_SPP data from client to server

// Define Spp Telink_Spp_AttrTbl index
#define SPP_ATTRTBL_S2CVALUE_INDEX 2
#define SPP_ATTRTBL_C2SVALUE_INDEX 4

#define SPP_MSGTYPE_CLIENT2SERVER  1
#define SPP_MSGTYPE_SERVER2CLIENT  2

/** @} end of group TELINK_SPP_Constant */



/** @addtogroup  SPP_SERVICE_Callbacks SPP Service Callbacks
 *  @{
 */

/**
 *  @brief  Definition for SPP data format
 */
typedef struct {
    u8 type;
    u8 len;
    u8 data[1];
} spp_data_t;

/**
 *  @brief  Definition SPP Data writted by client callback function type for user application
 */
typedef void (*spp_clientWrite2ServerCb_t)(spp_data_t* pReq);

/**
 *  @brief  Definition for foundation command callbacks.
 */
typedef struct {
	spp_clientWrite2ServerCb_t  spp_clientWrite2ServerFunc;    //!< client write data to server
} spp_callbacks_t;


/** @} end of group SPP_SERVICE_Callbacks */



 /** @addtogroup  TELINK_SPP_Variables Telink Spp Variables
 *  @{
 */
 
 /**
 *  @brief  External variable for Telink Spp service Attribute tables
 */
//extern attribute_t Telink_Spp_AttrTbl[];

/**
 *  @brief  External variable for Telink Spp service attribute size
 */
extern u16         Telink_Spp_attrSize;


/** @} end of group TELINK_SPP_Variables */


 /** @addtogroup  TELINK_SPP_Functions Telink Spp APIs
 *  @{
 */
 
/**
 * @brief       API to add telink spp service to gatt.
 *
 * @param[in]   None
 *
 * @return      Status
 */
ble_sts_t Telink_Spp_AddService(spp_callbacks_t *sppCb);


/**
 * @brief       API to set Spp type
 *
 * @param[in]   type - The specified Spp Type
 *
 * @return      None
 */

void Telink_SendSppData(u16 connHandle, u8* data, u8 len);

/**
 * @brief       API to send the contol bit
 *
 * @param[in]   connHandle - The handle will send data to
 * @param[in]   ctrl - 1 indication START, 0 indicating STOP
 *
 * @return      Status
 */
