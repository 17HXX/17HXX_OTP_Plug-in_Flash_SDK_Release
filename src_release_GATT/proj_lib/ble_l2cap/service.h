
#pragma once

#include "../../proj/tl_common.h"



/*********************************************************************
 * CONSTANTS
 */


/**
 *  @brief  Definition for Services UUID
 */
#define SERVICE_UUID_ALERT_NOTIFICATION                           0x1811
#define SERVICE_UUID_BATTERY                                      0x180F
#define SERVICE_UUID_BLOOD_PRESSURE                               0x1810
#define SERVICE_UUID_CURRENT_TIME                                 0x1805
#define SERVICE_UUID_CYCLING_POWER                                0x1818
#define SERVICE_UUID_CYCLING_SPEED_AND_CADENCE                    0x1816
#define SERVICE_UUID_DEVICE_INFORMATION                           0x180A
#define SERVICE_UUID_GENERIC_ACCESS                               0x1800
#define SERVICE_UUID_GENERIC_ATTRIBUTE                            0x1801
#define SERVICE_UUID_GLUCOSE                                      0x1808
#define SERVICE_UUID_HEALTH_THERMOMETER                           0x1809
#define SERVICE_UUID_HEART_RATE                                   0x180D
#define SERVICE_UUID_HUMAN_INTERFACE_DEVICE                       0x1812
#define SERVICE_UUID_IMMEDIATE_ALERT                              0x1802
#define SERVICE_UUID_LINK_LOSS                                    0x1803
#define SERVICE_UUID_LOCATION_AND_NAVIGATION                      0x1819
#define SERVICE_UUID_NEXT_DST_CHANGE                              0x1807
#define SERVICE_UUID_PHONE_ALERT_STATUS                           0x180E
#define SERVICE_UUID_REFERENCE_TIME_UPDATE                        0x1806
#define SERVICE_UUID_RUNNING_SPEED_AND_CADENCE                    0x1814
#define SERVICE_UUID_SCAN_PARAMETER                               0x1813
#define SERVICE_UUID_TX_POWER                                     0x1804
#define SERVICE_UUID_USER_DATA                                    0x181C




/*********************************************************************
 * ENUMS
 */



/*********************************************************************
 * TYPES
 */




/*********************************************************************
 * GLOBAL VARIABLES
 */


/*********************************************************************
 * Public Functions
 */
ble_sts_t service_init(void);

#ifndef UUID_LENGTH_16_BYTES
#define UUID_LENGTH_16_BYTES  				0
#endif

#if UUID_LENGTH_16_BYTES

#define SPP_UUID_SERVICE   			{0x10,0x19,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00}		//!< SPP service
#define AUDIO_UUID_SERVICE  		    {0x11,0x19,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00}		//!< SPP service
#define OTA_UUID_SERVICE   			{0x12,0x19,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00}		//!< OTA service
#define MESH_UUID_SERVICE  			{0x20,0x19,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00}		//!< SPP service
#define MESH_LT_UUID_SERVICE  		{0x21,0x19,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00}		//!< SPP service

#define SPP_DATA_SERVER2CLIENT 		{0x10,0x2B,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00} 		//!< SPP data from server to client
#define SPP_DATA_CLIENT2SERVER 		{0x11,0x2B,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00} 		//!< SPP data from client to server
#define SPP_DATA_OTA 				{0x12,0x2B,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00} 		//!< SPP data for ota
#define SPP_DATA_PAIR 				{0x13,0x2B,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00} 		//!< SPP data for ota

#define MIC_DATA	 					{0x18,0x2B,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00} 		//!< SPP data from server to client
#define SPEAKER_DATA			 		{0x19,0x2B,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00} 		//!< SPP data from client to server

#else

#define SPP_UUID_SERVICE   			0x1910		//!< SPP service
#define AUDIO_UUID_SERVICE  			0x1911		//!< SPP service
#define MESH_UUID_SERVICE  			0x1920		//!< SPP service
#define MESH_LT_UUID_SERVICE  		0x1921		//!< SPP service

#define SPP_DATA_SERVER2CLIENT 		0x2B10 		//!< SPP data from server to client
#define SPP_DATA_CLIENT2SERVER 		0x2B11 		//!< SPP data from client to server
#define SPP_DATA_OTA 				0x2B12 		//!< SPP data for ota
#define SPP_DATA_PAIR 				0x2B13 		//!< SPP data for ota

#define MIC_DATA	 					0x2B18 		//!< SPP data from server to client
#define SPEAKER_DATA			 		0x2B19 		//!< SPP data from client to server

#endif
