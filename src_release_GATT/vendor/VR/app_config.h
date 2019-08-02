#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif
/**************************the follow must define (public)***************************/
#define _USER_CONFIG_DEFINED_   1   // must define this macro to make others known
#define __LOG_RT_ENABLE__       0



#define OTA_ENABLE				0



//////////// product  Information  //////////////////////////////
#define ID_VENDOR               0x248a          // for report
#define ID_PRODUCT_BASE         0x880C
// If ID_PRODUCT left undefined, it will default to be combination of ID_PRODUCT_BASE and the USB config USB_SPEAKER_ENABLE/USB_MIC_ENABLE...
// #define ID_PRODUCT           0x8869

#define STRING_VENDOR           L"PHIL"
#define STRING_PRODUCT          L"BLE SHUTTER"
#define STRING_SERIAL           L"phil"

#define CHIP_TYPE               CHIP_TYPE_17H26      // 8866-24, 8566-32

#define FLOW_NO_OS              1
#define     RF_FAST_MODE_1M     1

/////////////////// Clock  /////////////////////////////////
#define CLOCK_SYS_TYPE          CLOCK_TYPE_PLL  //  one of the following:  CLOCK_TYPE_PLL, CLOCK_TYPE_OSC, CLOCK_TYPE_PAD, CLOCK_TYPE_ADC
#define CLOCK_SYS_CLOCK_HZ      32000000

//////////////////Extern Crystal Type///////////////////////
#define CRYSTAL_TYPE			XTAL_12M		//  extern 16M crystal


////////////////Moudule Enable  ////////////////////////////
#define MODULE_ADC_ENABLE		1

///////////////////  ADC  /////////////////////////////////
#if(MODULE_ADC_ENABLE)

#define ADC_CHNM_ANA_INPUT      ADC_CHN_GP18  //others parameters (ADC_CHN_GP17 ADC_CHN_GP18 ADC_CHN_GP22 ADC_CHN_GP23)
#define ADC_CHNM_REF_SRC        ADC_REF_1P3V  //others parameters (ADC_REF_1P3V ADC_REF_VDDH)

#endif

///////////////////  RAM&OTP Optimization    /////////////////////////////////
/*Disable interrupt for 17H26_remote application*/
#define ENABLE_INTERRUPT  0

#if ENABLE_INTERRUPT  
#define FLASH_OP_DISABLE_IRQ 				1 /*1 Means flash operation needs to disable IRQ*/
#define ANALOG_OP_DISABLE_IRQ				1
#define KEYSCAN_OP_DISABLE_IRQ                     1
#define RING_BUF_OP_DISABLE_IRQ                   1
#define BLT_LL_OP_DISABLE_IRQ                        1

#else
#define FLASH_OP_DISABLE_IRQ 				0
#define ANALOG_OP_DISABLE_IRQ				0
#define KEYSCAN_OP_DISABLE_IRQ                     0
#define RING_BUF_OP_DISABLE_IRQ                   0
#define BLT_LL_OP_DISABLE_IRQ                        0
#endif

/*Define low resource cost event call back functions*/
#define LOW_COST_EVENT_CB_MODE  1


//if device is hid map is real value ,other define 0xff;
#define SUPPORT_HID_YKQ  TRUE


#define BATT_ALARM_LEVEL_YKQ  32


#define UNKOWN_ROLE     961
#define KB_ROLE     961
#define MOUSE_ROLE     962
#define JOYSTIC_ROLE     963
#define GAMEPAD_ROLE     964

#define GAP_APPEARE_ROLE                     GAMEPAD_ROLE //!< Unknown

/*********************************************************************************/

#define	PULL_WAKEUP_SRC_GPIO0	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO0_DATA_OUT			0
#define GPIO0_INPUT_ENABLE 		0
#define GPIO0_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO1	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO1_DATA_OUT			0
#define GPIO1_INPUT_ENABLE 		0
#define GPIO1_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO2	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO2_DATA_OUT			0
#define GPIO2_INPUT_ENABLE 		0
#define GPIO2_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO3	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO3_DATA_OUT			0
#define GPIO3_INPUT_ENABLE 		0
#define GPIO3_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO4	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO4_DATA_OUT			0
#define GPIO4_INPUT_ENABLE 		0
#define GPIO4_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO5	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO5_DATA_OUT			0
#define GPIO5_INPUT_ENABLE 		0
#define GPIO5_OUTPUT_ENABLE 	0


#define	PULL_WAKEUP_SRC_GPIO6	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO6_DATA_OUT			0
#define GPIO6_INPUT_ENABLE 		0
#define GPIO6_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO7	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO7_DATA_OUT			0
#define GPIO7_INPUT_ENABLE 		0
#define GPIO7_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO8	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO8_DATA_OUT			0
#define GPIO8_INPUT_ENABLE 		0
#define GPIO8_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO9	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO9_DATA_OUT			0
#define GPIO9_INPUT_ENABLE 		0
#define GPIO9_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO10	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO10_DATA_OUT			0
#define GPIO10_INPUT_ENABLE 	0
#define GPIO10_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO11	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO11_DATA_OUT			0
#define GPIO11_INPUT_ENABLE 	0
#define GPIO11_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO12	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO12_DATA_OUT			0
#define GPIO12_INPUT_ENABLE 	0
#define GPIO12_OUTPUT_ENABLE 	0


#define	PULL_WAKEUP_SRC_GPIO13	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO13_DATA_OUT			0
#define GPIO13_INPUT_ENABLE 	0
#define GPIO13_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO14	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO14_DATA_OUT			0
#define GPIO14_INPUT_ENABLE 	0
#define GPIO14_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO15	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO15_DATA_OUT			0
#define GPIO15_INPUT_ENABLE 	0
#define GPIO15_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO16	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO16_DATA_OUT			0
#define GPIO16_INPUT_ENABLE 	0
#define GPIO16_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO17	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO17_DATA_OUT			0
#define GPIO17_INPUT_ENABLE 	0
#define GPIO17_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO18	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO18_DATA_OUT			0
#define GPIO18_INPUT_ENABLE 	0
#define GPIO18_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO19	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO19_DATA_OUT			0
#define GPIO19_INPUT_ENABLE 	0
#define GPIO19_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO20	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO20_DATA_OUT			0
#define GPIO20_INPUT_ENABLE 	0
#define GPIO20_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO21	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO21_DATA_OUT			0
#define GPIO21_INPUT_ENABLE 	0
#define GPIO21_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO22	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO22_DATA_OUT			0
#define GPIO22_INPUT_ENABLE 	0
#define GPIO22_OUTPUT_ENABLE 	0


#define	PULL_WAKEUP_SRC_GPIO23	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO23_DATA_OUT			0
#define GPIO23_INPUT_ENABLE 	0
#define GPIO23_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO24	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO24_DATA_OUT			0
#define GPIO24_INPUT_ENABLE 	0
#define GPIO24_OUTPUT_ENABLE 	0

//low vcc  lock led
#define	PULL_WAKEUP_SRC_GPIO25	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO25_DATA_OUT			0
#define GPIO25_INPUT_ENABLE 	0
#define GPIO25_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO26	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO26_DATA_OUT			0
#define GPIO26_INPUT_ENABLE 	0
#define GPIO26_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO27	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO27_DATA_OUT			0
#define GPIO27_INPUT_ENABLE 	0
#define GPIO27_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO28	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO28_DATA_OUT			0
#define GPIO28_INPUT_ENABLE 	0
#define GPIO28_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO29	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO29_DATA_OUT			0
#define GPIO29_INPUT_ENABLE 	0
#define GPIO29_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO30	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO30_DATA_OUT			0
#define GPIO30_INPUT_ENABLE 	0
#define GPIO30_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO31	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO31_DATA_OUT			0
#define GPIO31_INPUT_ENABLE 	0
#define GPIO31_OUTPUT_ENABLE 	0

#define	PULL_WAKEUP_SRC_GPIO32	PM_PIN_UP_DOWN_FLOAT//PM_PIN_PULLDOWN_100K// for power on
#define GPIO32_DATA_OUT			0
#define GPIO32_INPUT_ENABLE 	0
#define GPIO32_OUTPUT_ENABLE 	0

/*********************************************************************************/


#ifndef 	DEBUG_FROM_FLASH
#define 	DEBUG_FROM_FLASH		0
#endif

#if(DEBUG_FROM_FLASH)   // firmware in flash (flash max size decided by flash type)
#define	CFG_DEVEICE_NAME_ADDR		0x76020  //16 bytes uese maybe change
#else					// firmware in otp(otp max size is (0x3fff - 20))
#define	CFG_DEVEICE_NAME_ADDR			0x3FC0   //16 bytes uese maybe change
#endif


//these address can not be changed at any time
#define	CFG_ADR_MAC_ADDR   				0x3FE0	// 4bytes
#define	CFG_TP_ORDER_ADDR_OTP				0x3FE6	// 2 bytes
#define	CFG_TP_ORDER_ADDR_FLASH			0x76006	// 2 bytes	if  otp is not written, read flash instead
#define	CFG_CHIP_ID_ADDR_OTP				0x3FE9	// 4bytes
#define	CFG_CHIP_ID_ADDR_FLASH			0x76011	// 4bytes	if  otp is not written, read flash instead
#define	CFG_ADR_MAC_ADDR_OTP   			0x3FE0	// 4bytes
#define	CFG_ADR_MAC_ADDR_FLASH			0x76000	//6 bytes
#define	CFG_FREQUENCY_OFFSET_ADDR_OTP	0x3FE8	// 1byte	default 0xff,  if 0xfe or 0x00,turn off internal cap.
#define	CFG_FREQUENCY_OFFSET_ADDR_FLASH   0x76010	// 1byte	default 0xff,  if 0xfe or 0x00,turn off internal cap.


/****************************must be sect the folllow Public Config******************************/

/*******************************************************************************/
///////////////////  RAMCODE  optimize  ////////////////////////


/////////////////// set default   ////////////////

#include "../common/default_config.h"


/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif
