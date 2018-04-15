#pragma once

#include "gatt.h"

#if 0
typedef enum
{
	ONLY_UUID16,
	SUPPORT_UUID128,	
};
#else
	#define ONLY_UUID16 0
	#define SUPPORT_UUID128 1
#endif

#define UUID_SUPPORT_TYPE 1

/** @addtogroup  GATT_Server_Module GATT server
 *  @{
 */

/** @addtogroup  GATT_Server_Types GATT server types
 *  @{
 */

/**
 *  @brief  Definition for client characteristic configuration change callback function
 */

typedef u8* (*att_handler_t)(u8 * p);
typedef int (*att_readwrite_callback_t)(void* p);

typedef struct attribute
{
#if(UUID_SUPPORT_TYPE==ONLY_UUID16)	
	  u8  attNum;
	//  u8  uuidLen;
	  u8  attrLen;
	//  u8  attrMaxLen;
	  u16 uuid;
	  u8* pAttrValue;
#else
	  u8  attNum;
	  u8  uuidLen;
	  u8  attrLen;
	//  u8  attrMaxLen;
	  u8* uuid;
	  u8* pAttrValue;
#endif
} attribute_t;




/** @addtogroup GATT_Attr_Num_Calc GATT attribute number calculation
 * @{
 */
#define GATT_CALC_ATTR_NUM( attrArray )       (sizeof(attrArray) / sizeof(attribute_t))
/** @} end of group GATT_Attr_Num_Calc */

