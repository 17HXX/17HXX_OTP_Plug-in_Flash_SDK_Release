
#ifndef 	_UI_H_
#define	_UI_H_


#include "../../proj/tl_common.h"
#include "../../proj_lib/rf_drv.h"
#include "../../proj_lib/pm.h"
#include "../../proj_lib/blt_ll/blt_ll.h"
#include "../../proj/drivers/usbkeycode.h"
#include "../../proj/mcu_spec/adc_17H26.h"


///////////////////////////////////////////////////////////////////////////////////////
//						External Variable
///////////////////////////////////////////////////////////////////////////////////////
//extern ui_type_t led_ui_buffer_MS[4];
extern u8		 blt_suspend_mask;
extern u8 		 blt_terminate_pending;
extern u32 		 blt_adv_interval;
extern u32		 blt_conn_interval_next;
extern rf_packet_version_ind_t	pkt_version_ind;
extern u16		 blt_conn_latency_next;;
extern u8 blt_test_dongle_conn  ;   // master type in current connection: 1/ test dongle     0/other test dongle
extern int				blt_wakeup_src;
extern u8 		blt_smp_paring_req_recvd;
extern u8		blt_retry ;





extern  u8 reportKeyIn[];
extern  u8 reportConsumerControlIn[];
extern   u8 reportMouseIn[];
extern  u8 reportJoyStickIn[];

extern  u8 flag_has_new_event_tmp;
extern  u8  connected_idle_time_count_tmp;



///////////////////////////////////////////////////////////////////////////////////////
//						External fuction
///////////////////////////////////////////////////////////////////////////////////////

extern void shutter_att_init ();
extern int blt_sleep_wakeup (int deepsleep, int wakeup_src, u32 wakeup_tick);
extern void blt_update_connPara_request (u16 min_interval, u16 max_interval, u16 latency, u16 timeout);
extern void hid_setting_flag(u16 en);

/************************************user define **************/

#define BIT0                            0x1
#define BIT1                            0x2
#define BIT2                            0x4
#define BIT3                            0x8
#define BIT4                            0x10
#define BIT5                            0x20
#define BIT6                            0x40
#define BIT7                            0x80
#define BIT8                            0x100
#define BIT9                            0x200
#define BIT10                           0x400
#define BIT11                           0x800
#define BIT12                           0x1000
#define BIT13                           0x2000
#define BIT14                           0x4000
#define BIT15                           0x8000
#define BIT16                           0x10000
#define BIT17                           0x20000
#define BIT18                           0x40000
#define BIT19                           0x80000
#define BIT20                           0x100000
#define BIT21                           0x200000
#define BIT22                           0x400000
#define BIT23                           0x800000
#define BIT24                           0x1000000
#define BIT25                           0x2000000
#define BIT26                           0x4000000
#define BIT27                           0x8000000
#define BIT28                           0x10000000
#define BIT29                           0x20000000
#define BIT30                           0x40000000
#define BIT31                           0x80000000










typedef enum
{
	POWER_ON_DEVICE_STATUS,
	DEEP_SLEEP_DEVICE_STATUS,
	HIGH_ADV_DEVICE_STATUS,
	LOW_ADV_DEVICE_STATUS,
	CONNECTED_DEVICE_STATUS,
	AFTER_CONNECTED_DEVICE_STATUS,
	KEY_PRESS_DEVICE_STATUS,
}DEVICE_STATUS;
#if 1
typedef enum
{
    N_TYPE=0x00,//non type 
	K_TYPE=0x2000,//keyboard type
	C_TYPE=0x4000,//consumer type
	M_TYPE=0x6000,//mouse
	J_TYPE=0x8000,//joystic
	CLEAR_TYPE=0X1FFF,
}KEY_DATA_TYPE;
#endif
typedef enum
{  
	SEND_K_DATA=BIT0,  
	SEND_C_DATA=BIT1,  
	SEND_M_DATA=BIT2,  
	SEND_J_DATA=BIT3,
	SEND_S_DATA=BIT4,
}SEND_DATA_TYPE;
#if 1
// ordinary keys
#define K_A				(0x04|K_TYPE)
#define K_B				(0x05|K_TYPE)
#define K_C				(0x06|K_TYPE)
#define K_D				(0x07|K_TYPE)
#define K_E				(0x08|K_TYPE)
#define K_F				(0x09|K_TYPE)
#define K_G				(0x0a|K_TYPE)
#define K_H				(0x0b|K_TYPE)
#define K_I				(0x0c|K_TYPE)
#define K_J				(0x0d|K_TYPE)
#define K_K				(0x0e|K_TYPE)
#define K_L				(0x0f|K_TYPE)
#define K_M				(0x10|K_TYPE)
#define K_N				(0x11|K_TYPE)
#define K_O				(0x12|K_TYPE)
#define K_P				(0x13|K_TYPE)
#define K_Q				(0x14|K_TYPE)
#define K_R				(0x15|K_TYPE)
#define K_S				(0x16|K_TYPE)
#define K_T				(0x17|K_TYPE)
#define K_U				(0x18|K_TYPE)
#define K_V				(0x19|K_TYPE)
#define K_W				(0x1a|K_TYPE)
#define K_X				(0x1b|K_TYPE)
#define K_Y				(0x1c|K_TYPE)
#define K_Z				(0x1d|K_TYPE)
#define K_1				(0x1e|K_TYPE)
#define K_2				(0x1f|K_TYPE)
#define K_3				(0x20|K_TYPE)
#define K_4				(0x21|K_TYPE)
#define K_5				(0x22|K_TYPE)
#define K_6				(0x23|K_TYPE)
#define K_7				(0x24|K_TYPE)
#define K_8				(0x25|K_TYPE)
#define K_9				(0x26|K_TYPE)
#define K_0				(0x27|K_TYPE)
#define K_ENTER			(0x28|K_TYPE)
#define K_ESC			(0x29|K_TYPE)
#define K_BACKSPACE		(0x2a|K_TYPE)
#define K_TAB			(0x2b|K_TYPE)
#define K_SPACE			(0x2c|K_TYPE)
#define K_MINUS			(0x2d|K_TYPE)
#define K_EQUAL			(0x2e|K_TYPE)
#define K_LBRACE		(0x2f|K_TYPE)
#define K_RBRACE		(0x30|K_TYPE)
#define K_BACKSLASH		(0x31|K_TYPE)
#define K_NUMBER		(0x32|K_TYPE)
#define K_SEMICOLON		(0x33|K_TYPE)
#define K_QUOTE			(0x34|K_TYPE)
#define K_TILDE			(0x35|K_TYPE)
#define K_COMMA			(0x36|K_TYPE)
#define K_PERIOD		(0x37|K_TYPE)
#define K_SLASH			(0x38|K_TYPE)
#define K_CAPITAL		(0x39|K_TYPE)
#define K_F1			(0x3a|K_TYPE)
#define K_F2			(0x3b|K_TYPE)
#define K_F3			(0x3c|K_TYPE)
#define K_F4			(0x3d|K_TYPE)
#define K_F5			(0x3e|K_TYPE)
#define K_F6			(0x3f|K_TYPE)
#define K_F7			(0x40|K_TYPE)
#define K_F8			(0x41|K_TYPE)
#define K_F9			(0x42|K_TYPE)
#define K_F10			(0x43|K_TYPE)
#define K_F11			(0x44|K_TYPE)
#define K_F12			(0x45|K_TYPE)
#define K_PRINTSCREEN	(0x46|K_TYPE)
#define K_SCR_LOCK		(0x47|K_TYPE)
#define K_PAUSE			(0x48|K_TYPE)
#define K_INSERT		(0x49|K_TYPE)
#define K_HOME			(0x4a|K_TYPE)
#define K_PAGE_UP		(0x4b|K_TYPE)
#define K_DELETE		(0x4c|K_TYPE)
#define K_END			(0x4d|K_TYPE)
#define K_PAGE_DOWN		(0x4e|K_TYPE)
#define K_RIGHT			(0x4f|K_TYPE)
#define K_LEFT			(0x50|K_TYPE)
#define K_DOWN			(0x51|K_TYPE)
#define K_UP			(0x52|K_TYPE)
#define K_NUM_LOCK		(0x53|K_TYPE)
#define K_PAD_SLASH		(0x54|K_TYPE)
#define K_PAD_ASTERIX	(0x55|K_TYPE)
#define K_PAD_MINUS		(0x56|K_TYPE)
#define K_PAD_PLUS		(0x57|K_TYPE)
#define K_PAD_ENTER		(0x58|K_TYPE)
#define K_PAD_1			(0x59|K_TYPE)
#define K_PAD_2			(0x5a|K_TYPE)
#define K_PAD_3			(0x5b|K_TYPE)
#define K_PAD_4			(0x5c|K_TYPE)
#define K_PAD_5			(0x5d|K_TYPE)
#define K_PAD_6			(0x5e|K_TYPE)
#define K_PAD_7			(0x5f|K_TYPE)
#define K_PAD_8			(0x60|K_TYPE)
#define K_PAD_9			(0x61|K_TYPE)
#define K_PAD_0			(0x62|K_TYPE)
#define K_PAD_PERIOD	(0x63|K_TYPE)
#define K_K45			(0x64|K_TYPE)
#define K_APP			(0x65|K_TYPE)
// below KEY is for ELAN's application matrix
#define K_C9R1			(0xf0|K_TYPE)	//C9R1 00
#define K_C9R6			(0xf1|K_TYPE)	//C9R6 000
#define K_RMB			(0xf2|K_TYPE)	//C7R3
#define K_EURO			(0xf3|K_TYPE)	//C0R2
#define K_MMODE			(0xf4|K_TYPE)	//C9R4

#define K_K107			(0x85|K_TYPE)	//ok
#define K_K56			(0x87|K_TYPE)	//ok
#define K_ROMA			(0x88|K_TYPE)	//ok
#define	K_K14			(0x89|K_TYPE)	//ok
#define K_CHG			(0x8a|K_TYPE)	//ok
#define K_NCHG			(0x8b|K_TYPE)	//ok
#define K_KCR			(0x90|K_TYPE)	//ok,K151
#define K_KCL			(0x91|K_TYPE)	//ok,K150

typedef enum
{
    M_LEFT=(M_TYPE|BIT0),
	M_RIGHT=(M_TYPE|BIT1),	
}MOUSE_BUTTON_DATA;
typedef enum
{  
	C_VOL_UP=(C_TYPE|BIT0), 
	C_VOL_DEC=(C_TYPE|BIT1),  
	C_PLAY_PAUSE=(C_TYPE|BIT2), 
	C_MUTE=(C_TYPE|BIT3),	
	C_SCAN_PRE_TRACK=(C_TYPE|BIT4), 
	C_SCAN_NEXT_TRACK=(C_TYPE|BIT5),
	C_WWW_HOME=(C_TYPE|BIT6),	
}CONSUME_DATA;
typedef enum
{  
	
	J_B1=(J_TYPE|BIT0),  
	J_B2=(J_TYPE|BIT1),  
	J_B3=(J_TYPE|BIT2),  
	J_B4=(J_TYPE|BIT3),
	J_B5=(J_TYPE|BIT4),  
	J_B6=(J_TYPE|BIT5),
	J_B7=(J_TYPE|BIT6),  
	J_B8=(J_TYPE|BIT7),

	
	J_UP=(J_TYPE|BIT8),
	J_DOWN=(J_TYPE|BIT9),
	J_LEFT=(J_TYPE|BIT10),
	J_RIGHT=(J_TYPE|BIT11),
	
}JOYSTIC_DATA;

#endif







#define VR_MODE_REG 0X19
#define POWER_TYPE_REG 0X1A
#define POWER_SWTICH_REG  0X1B










#endif

