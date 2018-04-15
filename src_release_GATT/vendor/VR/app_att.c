#include "../../proj/tl_common.h"
#include "../../proj_lib/blt_ll/blt_ll.h"
#include "ui.h"


#define FW_VERSION_ID1 0x01
#define FW_VERSION_ID2 0x10

#define FW_Soft_VERSION_ID1 00
#define FW_Soft_VERSION_ID2 01

typedef struct
{
  /** Minimum value for the connection event (interval. 0x0006 - 0x0C80 * 1.25 ms) */
  u16 intervalMin;
  /** Maximum value for the connection event (interval. 0x0006 - 0x0C80 * 1.25 ms) */
  u16 intervalMax;
  /** Number of LL latency connection events (0x0000 - 0x03e8) */
  u16 latency;
  /** Connection Timeout (0x000A - 0x0C80 * 10 ms) */
  u16 timeout;
} gap_periConnectParams_t;

const u16 clientCharacterCfgUUID = GATT_UUID_CLIENT_CHAR_CFG;

//const u16 extReportRefUUID = GATT_UUID_EXT_REPORT_REF;

const u16 reportRefUUID = GATT_UUID_REPORT_REF;

//const u16 characterPresentFormatUUID = GATT_UUID_CHAR_PRESENT_FORMAT;

const u16 my_primaryServiceUUID = GATT_UUID_PRIMARY_SERVICE;

const u16 my_characterUUID = GATT_UUID_CHARACTER;

const u16 my_devServiceUUID = SERVICE_UUID_DEVICE_INFORMATION;

const u16 my_PnPUUID = CHARACTERISTIC_UUID_PNP_ID;

const u16 my_devNameUUID = GATT_UUID_DEVICE_NAME;

const u16 my_serviceChangeUUID = GATT_UUID_SERVICE_CHANGE;

const u16 my_appearanceUIID = 0x2a01;
const u16 my_periConnParamUUID = 0x2a04;


const u16 my_gattServiceUUID = SERVICE_UUID_GENERIC_ATTRIBUTE; //0x1801

extern u8 tbl_adv[];



const u8 PROP_READ = CHAR_PROP_READ;

const u8 PROP_WRITE = CHAR_PROP_WRITE;

const u8 PROP_INDICATE = CHAR_PROP_INDICATE;

const u8 PROP_WRITE_NORSP = CHAR_PROP_WRITE_WITHOUT_RSP;

const u8 PROP_READ_NOTIFY = CHAR_PROP_READ | CHAR_PROP_NOTIFY;

const u8 PROP_READ_WRITE_NORSP = CHAR_PROP_READ | CHAR_PROP_WRITE_WITHOUT_RSP;

const u8 PROP_READ_WRITE_WRITENORSP = CHAR_PROP_READ | CHAR_PROP_WRITE | CHAR_PROP_WRITE_WITHOUT_RSP;

const u8 PROP_READ_WRITE = CHAR_PROP_READ|CHAR_PROP_WRITE;

const u8 PROP_READ_WRITE_NORSP_NOTIFY = CHAR_PROP_READ | CHAR_PROP_WRITE_WITHOUT_RSP|CHAR_PROP_NOTIFY;

const u8    my_PnPtrs [] = {0x02, 0x12, 0x34, FW_Soft_VERSION_ID1, FW_Soft_VERSION_ID2, FW_VERSION_ID2, FW_VERSION_ID1};

//const u8    my_PnPtrs [] = {0x02, 0x5e, 0x04, 0x8e, 0x02, FW_VERSION_ID2, FW_VERSION_ID1};

u16 serviceChangeVal[4] = {0};
static u8 serviceChangeCCC[2]={0,0};

const u16 my_gapServiceUUID = SERVICE_UUID_GENERIC_ACCESS;
const u16 my_appearance = GAP_APPEARE_ROLE;//global
const gap_periConnectParams_t my_periConnParameters = {30, 60, 4, 1000};

//////////////////////// HID /////////////////////////////////////////////////////

//const u16 my_hidServiceUUID                 = SERVICE_UUID_HUMAN_INTERFACE_DEVICE;
//const u16 my_SppDataServer2ClientUUID       = SPP_DATA_SERVER2CLIENT;
//const u16 my_SppDataClient2ServiceUUID      = AUDIO_UUID_SERVICE ;
//
//const u16 hidServiceUUID           = SERVICE_UUID_HUMAN_INTERFACE_DEVICE;
//const u16 hidProtocolModeUUID      = CHARACTERISTIC_UUID_HID_PROTOCOL_MODE;
//const u16 hidReportUUID            = CHARACTERISTIC_UUID_HID_REPORT;
//const u16 hidReportMapUUID         = CHARACTERISTIC_UUID_HID_REPORT_MAP;
//const u16 hidbootKeyInReportUUID   = CHARACTERISTIC_UUID_HID_BOOT_KEY_INPUT;
//const u16 hidbootKeyOutReportUUID  = CHARACTERISTIC_UUID_HID_BOOT_KEY_OUTPUT;
//const u16 hidbootMouseInReportUUID = CHARACTERISTIC_UUID_HID_BOOT_MOUSE_INPUT;
//const u16 hidinformationUUID       = CHARACTERISTIC_UUID_HID_INFORMATION;
//const u16 hidCtrlPointUUID         = CHARACTERISTIC_UUID_HID_CONTROL_POINT;
//const u16 hidIncludeUUID           = GATT_UUID_INCLUDE;
//
//static u8 protocolMode = DFLT_HID_PROTOCOL_MODE;
//
const u16 my_batServiceUUID       			= SERVICE_UUID_BATTERY;
const u16 my_batCharUUID       				= CHARACTERISTIC_UUID_BATTERY_LEVEL;
u8 my_batVal 						= {100};
//
//u8  generalValInCCC[2];
//
//#if(KEYBOARD_REPORT_SUPPORT)
//u8 reportKeyIn[8]={0,0,0,0,0,0,0,0};//globle
////u8 generalValInCCC[2];
//const static u8 reportRefKeyIn[2] ={HID_REPORT_ID_KEYBOARD_INPUT,HID_REPORT_TYPE_INPUT };
//
//u8 reportKeyOut;
//const static u8 reportRefKeyOut[2]={HID_REPORT_ID_KEYBOARD_INPUT, HID_REPORT_TYPE_OUTPUT };
//
//#endif
//
//#if(JOYSTIC_REPORT_SUPPORT)
//u8 reportJoyStickIn[9];//globle
////u8 generalValInCCC[2];
//const static u8 reportRefJoyStickIn[2] ={HID_REPORT_ID_JOYSTIC_INPUT, HID_REPORT_TYPE_INPUT };
//#endif
//
//#if(CONSUME_REPORT_SUPPORT)
//u8 reportConsumerControlIn[2];
////u8 generalValInCCC[2];
//const static u8 reportRefConsumerControlIn[2] = { HID_REPORT_ID_CONSUME_CONTROL_INPUT, HID_REPORT_TYPE_INPUT };
//#endif
//
//#if(MOUSE_REPORT_SUPPORT)
//u8 reportMouseIn[4];
//// u8 generalValInCCC[2];
//const static u8 reportRefMouseIn[2] = { HID_REPORT_ID_MOUSE_INPUT, HID_REPORT_TYPE_INPUT };
//#endif
//
//
//// HID Information characteristic
//const u8 hidInformation[] =
//{
//  U16_LO(0x0111), U16_HI(0x0111),             // bcdHID (USB HID version)
//  0x00,                                       // bCountryCode
//  0x01                                        // Flags
//};
//
//static u8 controlPoint;
//
//const u8 my_newGameServiceUUID[16]={0XAB,0X89,0X67,0X45,0X23,0X01,0X88,0X88,0x66,0x66,0x11,0x11,0x01,0x00,0x68,0x91};
//
//const u8 my_newGameNotifyUUID[16]={0XAB,0X89,0X67,0X45,0X23,0X01,0X88,0X88,0x66,0x66,0x11,0x11,0x03,0x00,0x68,0x91};
////u8  generalValInCCC[2];
//u8 my_newGameNotifyIn[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//
//const u8 my_newGameWriteCmdUUID[16]={0XAB,0X89,0X67,0X45,0X23,0X01,0X88,0X88,0x66,0x66,0x11,0x11,0x02,0x00,0x68,0x91};
//u8 my_newGameWriteCmdOut[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//
//const u8 my_newGameWriteDataUUID[16]={0XAB,0X89,0X67,0X45,0X23,0X01,0X88,0X88,0x66,0x66,0x11,0x11,0x04,0x00,0x68,0x91};
//u8 my_newGameWriteDataOut[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//
//
//const u8 my_W24ServiceUUID[2]={0x00,0xFF};
//const u8 my_W24NotifyUUID[2]={0x01,0xFF};
////u8  generalValInCCC[2];
//u8 my_W24NotifyIn[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//
//
//static const u8 reportMapIos[] =
//{
//
///************************************keyboard*************************/
//#if(KEYBOARD_REPORT_SUPPORT)
//
//0x05, 0x01,  // Usage Pg (Generic Desktop)
//0x09, 0x06,  // Usage (Keyboard)
//0xA1, 0x01,  // Collection: (Application)
//0x85, HID_REPORT_ID_KEYBOARD_INPUT,  // Report Id (2)
////
//0x05, 0x07,  // Usage Pg (Key Codes)
//0x19, 0xE0,  // Usage Min (224)
//0x29, 0xE7,  // Usage Max (231)
//0x15, 0x00,  // Log Min (0)
//0x25, 0x01,  // Log Max (1)
////
////	Modifier byte
//0x75, 0x01,  // Report Size (1)
//0x95, 0x08,  // Report Count (8)
//0x81, 0x02,  // Input: (Data, Variable, Absolute)
////
////	Reserved byte
//0x95, 0x01,  // Report Count (1)
//0x75, 0x08,  // Report Size (8)
//0x81, 0x01,  // Input: (Constant)
////
////	LED report
//0x95, 0x05,  // Report Count (5)
//0x75, 0x01,  // Report Size (1)
//0x05, 0x08,  // Usage Pg (LEDs)
//0x19, 0x01,  // Usage Min (1)
//0x29, 0x05,  // Usage Max (5)
//0x91, 0x02,  // Output: (Data, Variable, Absolute)
////
////	LED report padding
//0x95, 0x01,  // Report Count (1)
//0x75, 0x03,  // Report Size (3)
//0x91, 0x01,  // Output: (Constant)
////
////	Key arrays (6 bytes)
//0x95, 0x06,  // Report Count (6)
//0x75, 0x08,  // Report Size (8)
//0x15, 0x00,  // Log Min (0)
//0x25, 0x65,  // Log Max (101)
//0x05, 0x07,  // Usage Pg (Key Codes)
//0x19, 0x00,  // Usage Min (0)
//0x29, 0x65,  // Usage Max (101)
//0x81, 0x00,  // Input: (Data, Array)
////
//0xC0,	   // End Collection
//
//
//#endif
///**********************consumer control*************************/
//#if(CONSUME_REPORT_SUPPORT)
//
//0x05, 0x0C,		// USAGE_PAGE (Consumer Devices)
//0x09, 0x01,		// USAGE (Consumer Control)
//0xA1, 0x01,		// COLLECTION (Application)
//0x85, HID_REPORT_ID_CONSUME_CONTROL_INPUT,		 // Report ID (2)
//0x75, 0x10,		// REPORT_SIZE (10)
//0x95, 0x01,		// REPORT_COUNT (2)
//0x15, 0x01,		// LOGICAL_MINIMUM (1)
//0x26, 0x8c, 0x02, // LOGICAL_MAXIMUM (28c)
//0x19, 0x01,		// USAGE_MINIMUM (Button 1)
//0x2a, 0x8c, 0x02, // USAGE_MAXIMUM (Button 28c)
//0x81, 0x60,		// INPUT (data, array, abs)
//0xc0,   // END COLLECTION
//
//
//#endif
//};
//
//static const u8 reportMapAndroid[] =
//{
//#if 1
///*******************************keyboard(65)*************************/
//#if(KEYBOARD_REPORT_SUPPORT)
//
//0x05, 0x01,  // Usage Pg (Generic Desktop)
//0x09, 0x06,  // Usage (Keyboard)
//0xA1, 0x01,  // Collection: (Application)
//0x85, HID_REPORT_ID_KEYBOARD_INPUT,  // Report Id (2)
////
//0x05, 0x07,  //	Usage Pg (Key Codes)
//0x19, 0xE0,  //	Usage Min (224)
//0x29, 0xE7,  //	Usage Max (231)
//0x15, 0x00,  //	Log Min (0)
//0x25, 0x01,  //	Log Max (1)
////
////	Modifier byte
//0x75, 0x01,  //	Report Size (1)
//0x95, 0x08,  //	Report Count (8)
//0x81, 0x02,  //	Input: (Data, Variable, Absolute)
////
////	Reserved byte
//0x95, 0x01,  //	Report Count (1)
//0x75, 0x08,  //	Report Size (8)
//0x81, 0x01,  //	Input: (Constant)
////
////	LED report
//0x95, 0x05,  //	Report Count (5)
//0x75, 0x01,  //	Report Size (1)
//0x05, 0x08,  //	Usage Pg (LEDs)
//0x19, 0x01,  //	Usage Min (1)
//0x29, 0x05,  //	Usage Max (5)
//0x91, 0x02,  //	Output: (Data, Variable, Absolute)
////
////	LED report padding
//0x95, 0x01,  //	Report Count (1)
//0x75, 0x03,  //	Report Size (3)
//0x91, 0x01,  //	Output: (Constant)
////
////	Key arrays (6 bytes)
//0x95, 0x06,  //	Report Count (6)
//0x75, 0x08,  //	Report Size (8)
//0x15, 0x00,  //	Log Min (0)
//0x25, 0x65,  //	Log Max (101)
//0x05, 0x07,  //	Usage Pg (Key Codes)
//0x19, 0x00,  //	Usage Min (0)
//0x29, 0x65,  //	Usage Max (101)
//0x81, 0x00,  //	Input: (Data, Array)
////
//0xC0, 	   // End Collection
//
//#endif
///**********************consumer control(25)*************************/
//#if(CONSUME_REPORT_SUPPORT)
//
//
//0x05, 0x0C, 	  // USAGE_PAGE (Consumer Devices)
//0x09, 0x01, 	  // USAGE (Consumer Control)
//0xA1, 0x01, 	  // COLLECTION (Application)
//0x85, HID_REPORT_ID_CONSUME_CONTROL_INPUT, 	   // Report ID (2)
//0x75, 0x10, 	  // REPORT_SIZE (10)
//0x95, 0x01, 	  // REPORT_COUNT (2)
//0x15, 0x01, 	  // LOGICAL_MINIMUM (1)
//0x26, 0x8c, 0x02, // LOGICAL_MAXIMUM (28c)
//0x19, 0x01, 	  // USAGE_MINIMUM (Button 1)
//0x2a, 0x8c, 0x02, // USAGE_MAXIMUM (Button 28c)
//0x81, 0x60, 	  // INPUT (data, array, abs)
//0xc0,			  // END COLLECTION
//
//#endif
//
///******************************mouse *************************/
//#if(MOUSE_REPORT_SUPPORT)
//
//  0x05, 0x01,  // Usage Page (Generic Desktop)
//  0x09, 0x02,  // Usage (Mouse)
//  0xA1, 0x01,  // Collection (Application)
//  0x85, HID_REPORT_ID_MOUSE_INPUT,  // Report Id (1)
//  0x09, 0x01,  //	Usage (Pointer)
//  0xA1, 0x00,  //	Collection (Physical)
//  0x05, 0x09,  //	  Usage Page (Buttons)
//  0x19, 0x01,  //	  Usage Minimum (01) - Button 1
//  0x29, 0x03,  //	  Usage Maximum (03) - Button 3
//  0x15, 0x00,  //	  Logical Minimum (0)
//  0x25, 0x01,  //	  Logical Maximum (1)
//  0x75, 0x01,  //	  Report Size (1)
//  0x95, 0x03,  //	  Report Count (3)
//  0x81, 0x02,  //	  Input (Data, Variable, Absolute) - Button states
//  0x75, 0x05,  //	  Report Size (5)
//  0x95, 0x01,  //	  Report Count (1)
//  0x81, 0x01,  //	  Input (Constant) - Padding or Reserved bits
//  0x05, 0x01,  //	  Usage Page (Generic Desktop)
//  0x09, 0x30,  //	  Usage (X)
//  0x09, 0x31,  //	  Usage (Y)
//  0x09, 0x38,  //	  Usage (Wheel)
//  0x15, 0x81,  //	  Logical Minimum (-127)
//  0x25, 0x7F,  //	  Logical Maximum (127)
//  0x75, 0x08,  //	  Report Size (8)
//  0x95, 0x03,  //	  Report Count (3)
//  0x81, 0x06,  //	  Input (Data, Variable, Relative) - X & Y coordinate
//  0xC0, 	   //	End Collection
//  0xC0, 	   // End Collection
//
//#endif
//
///**********************Game Pad*************************/
//#if(JOYSTIC_REPORT_SUPPORT)
//
//0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
//0x09, 0x05,                    // USAGE (Game Pad)
//0xA1, 0x01,   				// Collection (Application)
//0x85, HID_REPORT_ID_JOYSTIC_INPUT,   				//     Report Id (4)
//0x05, 0x01, 				   // USAGE_PAGE (Generic Desktop)
//0x09, 0x01,                    //   USAGE (Pointer)
//0xA1, 0x00,                    //   COLLECTION (Physical)
//
//
//0x09, 0x30, 				   //	  USAGE (X)
//0x09, 0x31, 				   //	  USAGE (Y)
//0x09, 0x32, 				   //	  USAGE (Z)
//0x09, 0x35, 				   //	  USAGE (RZ)
////0x09, 0x33, 				   //	  USAGE (RX)
////0x09, 0x34, 				   //	  USAGE (RY)
//0x15, 0x00,  //	  Logical Minimum (-127)
//0x26, 0xff,0x00 , //	  Logical Maximum (127)
//0x75, 0x08,  //	  Report Size (8)
//0x95, 0x04,  //	  Report Count (3)
//0x81, 0x02,  //     INPUT (Data,Var,Abs)
//0XC0,
//
//0x09, 0x39, //	  USAGE (Hat switch)
//0x15, 0x00,  //   Logical Minimum (-127)
//0x25, 0x07,  //   Logical Maximum (127)
//0x35, 0x00,
//0x46, 0x3b,0x01,
//0x65, 0x14,
//0x75, 0x04,  //   Report Size (8)
//0x95, 0x01,  //   Report Count (1)
//0x81, 0x42,  // 	INPUT (Data,Var,Abs)
//0x75, 0x04,  //   Report Size (8)
//0x95, 0x01,  //   Report Count (1)
//0x81, 0x01,
//
//
//0x05, 0x09,                    //   USAGE_PAGE (Button)
//0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
//0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
//0x19, 0x01, 				   //	USAGE_MINIMUM (Button 1)
//0x29, 0x10, 				   //	USAGE_MAXIMUM (Button 12)
//0x75, 0x01,                    //   REPORT_SIZE (1)
//0x95, 0x10,                    //   REPORT_COUNT (12)
//0x81, 0x02,                    //   INPUT (Data,Var,Abs)
//
//0x05, 0x02,                    // USAGE_PAGE
//0x15, 0x00,
//0x26, 0xff,0x00,
//0x09, 0xc4,
//0x09, 0xc5,
//0x75, 0x08,
//0x95, 0x02,
//0x81, 0x02,
//0xc0,
//
//
//#endif
//
//#else
//
//0x05,0x01,
//0x09,0x05,
//0xa1,0x01,
////0x85,0x01,
//
//0xa1,0x00,
//0x09,0x30,
//0x09,0x31,
//0x15,0x00,
//0x26,0xff,0xff,
//0x35,0x00,
//0x46,0xff,0xff,
//0x95,0x02,
//0x75,0x10,
//0x81,0x02,
//0xc0,
//
//0xa1,0x00,
//0x09,0x33,
//0x09,0x34,
//0x15,0x00,
//0x26,0xff,0xff,
//0x35,0x00,
//0x46,0xff,0xff,
//0x95,0x02,
//0x75,0x10,
//0x81,0x02,
//0xc0,
//
//0xa1,0x00,
//0x09,0x32,
//0x15,0x00,
//0x26,0xff,0xff,
//0x35,0x00,
//0x46,0xff,0xff,
//0x95,0x01,
//0x75,0x10,
//0x81,0x02,
//0xc0,
//
//0x05,0x09,
//0x19,0x01,
//0x29,0x0a,
//0x95,0x0a,
//0x75,0x01,
//0x81,0x02,
//
//0x05,0x01,
//0x09,0x39,
//0x15,0x01,
//0x25,0x08,
//0x35,0x00,
//0x46,0x3b,0x10,
//0x66,0x0e,0x00,
//0x75,0x04,
//0x95,0x01,
//0x81,0x42,
//0x75,0x02,
//0x95,0x01,
//0x81,0x03,
//0x75,0x08,
//0x95,0x02,
//0x81,0x03,
//0xc0,
//
//#endif
//
//};
//
//
extern u8 os_check;
u8* att_get_reportMap(){

//	if(os_check == 2){
//		return (u8*)(reportMapAndroid);
//	}else{
//		return (u8*)(reportMapIos);
//	}
	return 0;
}
int att_get_reportMapSize(){
//	if(os_check == 2){
//		return sizeof(reportMapAndroid);
//	}else{
//		return sizeof(reportMapIos);
//	}
	return 0;
	}

const u8 ota_service_uuid[16] = {0x11,0x19,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00};
const u8 ota_write_char_uuid[16] ={0x12,0x2B,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00} ;

u8 ota_data[20];

const attribute_t my_Attributes[] = 
{
//DFSADF
	{13,0,0,0,0}, //

/**************************************************************************
						GenericAttribute(Services)
***************************************************************************/
	{4,2,2,(u8*)(&my_primaryServiceUUID),		   (u8*)(&my_gattServiceUUID)},
	{0,2,1,(u8*)(&my_characterUUID),			   (u8*)(&PROP_INDICATE)},
	{0,2,4,(u8*)(&my_serviceChangeUUID),		   (u8*)(serviceChangeVal)},
	{0,2,2,(u8*)(&clientCharacterCfgUUID),		   (u8*)(serviceChangeCCC)},
/**************************************************************************
					   GenericAccess(Services)
***************************************************************************/
	// gap, 5
	{5,2,2,(u8*)(&my_primaryServiceUUID),	   (u8*)(&my_gapServiceUUID)},
	{0,2,1,(u8*)(&my_characterUUID),	  (u8*)(&PROP_READ)},
	{0,2,sizeof (my_appearance), (u8*)(&my_appearanceUIID),  (u8*)(&my_appearance)},
	{0,2,1,(u8*)(&my_characterUUID),	  (u8*)(&PROP_READ)},
	{0,2,sizeof (my_periConnParameters),(u8*)(&my_periConnParamUUID),   (u8*)(&my_periConnParameters)},
/**************************************************************************
						DeviceInformation(Services)
***************************************************************************/
	{3,2,2,(u8*)(&my_primaryServiceUUID), 	(u8*)(&my_devServiceUUID)},
	{0,2,1,(u8*)(&my_characterUUID),	   (u8*)(&PROP_READ)},
	{0,2,sizeof (my_PnPtrs),	(u8*)(&my_PnPUUID),  (u8*)(my_PnPtrs)},
/**************************************************************************
							OTA (Services)
***************************************************************************/
#if(OTA_ENABLE)
	{4,2,16,		(u8*)(&my_primaryServiceUUID),	(u8*)(&ota_service_uuid)},
	{0,2,1,		(u8*)(&my_characterUUID),		(u8*)(&PROP_READ_WRITE_NORSP_NOTIFY)},			//prop
	{0,16,20,	(u8*)(&ota_write_char_uuid),			ota_data}, 		//value
	{0,2,2, (u8*)(&clientCharacterCfgUUID),    (u8*)(generalValInCCC)},  //value
#endif
		
};

void    shutter_att_init ()
{
    /*blt_set_att_table ((u8 *)my_Attributes);*/
    extern attribute_t* gAttributes;
    gAttributes = (attribute_t *)my_Attributes;

	//blt_smp_set_pairing_type(1,0);
	
//     blt_smp_func_init ();
}

//void hid_setting_flag(u16 en)
//{
//
//	 generalValInCCC[0] = en;
//}
//u8  get_hid_ccc_flag()
//{
//	return generalValInCCC[0];
//}
