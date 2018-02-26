
#pragma once

#include "../../proj/tl_common.h"
#include "../../proj_lib/rf_drv.h"
#include "../../proj_lib/pm.h"

#include "../../proj_lib/ble_l2cap/ble_common.h"
#include "../../proj_lib/ble_l2cap/att.h"
#include "../../proj_lib/ble_l2cap/gatt_uuid.h"
#include "../../proj_lib/ble_l2cap/service.h"
#include "../../proj_lib/ble_l2cap/gatt_server.h"
#include "../../proj_lib/ble_l2cap/gap_const.h"
#include "../../proj_lib/ble_l2cap/blueLight.h"
#include "../../proj_lib/ble_l2cap/hids.h"
#include "../../proj_lib/ble_l2cap/battery_service.h"
#include "../../proj_lib/ble_l2cap/device_information.h"
#include "../../proj_lib/ble_l2cap/immediate_alert.h"
#include "../../proj_lib/ble_l2cap/link_loss.h"
#include "../../proj_lib/ble_l2cap/scan_parameters.h"
#include "../../proj_lib/ble_l2cap/user_spp.h"
#include "../../proj_lib/ble_l2cap/txpower.h"


/////////////////////////////////////////////////////////////////////////////
#define				MESH_COMMAND_FROM_PHONE					1
#define				MESH_COMMAND_FROM_DEVICE				2

#define         VENDOR_ID                       0x0211

// op cmd 11xxxxxxzzzzzzzzzzzzzzzz z's=VENDOR_ID  xxxxxx=LGT_CMD_
#define			LGT_CMD_LIGHT_ONOFF				0x10
#define			LGT_CMD_LIGHT_ON				0x10
#define			LGT_CMD_LIGHT_OFF				0x11//internal use
#define			LGT_CMD_LIGHT_SET				0x12//set lumen
#define			LGT_CMD_SWITCH_CONFIG	        0x13//internal use
#define         LGT_CMD_LIGHT_GRP_RSP1          0x14//get group rsp: 8groups low 1bytes
#define         LGT_CMD_LIGHT_GRP_RSP2          0x15//get group rsp: front 4groups 2bytes
#define         LGT_CMD_LIGHT_GRP_RSP3          0x16//get group rsp: behind 4groups 2bytes
#define 		LGT_CMD_LIGHT_CONFIG_GRP 		0x17//add or del group
#define			LGT_CMD_LUM_UP					0x18//internal use
#define			LGT_CMD_LUM_DOWN				0x19//internal use
#define 		LGT_CMD_LIGHT_READ_STATUS 		0x1a//get status req
#define 		LGT_CMD_LIGHT_STATUS 			0x1b//get status rsp
#define 		LGT_CMD_LIGHT_ONLINE 			0x1c//get online status req//internal use
#define         LGT_CMD_LIGHT_GRP_REQ           0x1d//get group req
#define			LGT_CMD_LEFT_KEY				0x1e//internal use
#define			LGT_CMD_RIGHT_KEY				0x1f//internal use
#define			LGT_CMD_CONFIG_DEV_ADDR         0x20//add device address
#define         LGT_CMD_DEV_ADDR_RSP            0x21//rsp
#define         LGT_CMD_SET_RGB_VALUE           0x22//params[0]:1=R 2=G 3=B params[1]:percent of lumen 0~100
#define         LGT_CMD_KICK_OUT                0x23//
#define         LGT_CMD_SET_TIME                0x24//
#define         LGT_CMD_ALARM                   0x25//
#define         LGT_CMD_READ_ALARM              0x26//
#define         LGT_CMD_ALARM_RSP               0x27//
#define         LGT_CMD_GET_TIME                0x28//
#define         LGT_CMD_TIME_RSP                0x29//


/////////////////////////////////////////////////////////////////////////////
#define		MASTER_CONNECT_ANY_DEVICE			BIT(6)

/////////////////////////////////////////////////////////////////////////////
#define					LL_CONNECTION_UPDATE_REQ	0x00
#define					LL_CHANNEL_MAP_REQ			0x01
#define					LL_TERMINATE_IND			0x02

#define					LL_UNKNOWN_RSP				0x07

#define 				LL_FEATURE_REQ              0x08
#define 				LL_FEATURE_RSP              0x09

#define 				LL_VERSION_IND              0x0C

#define 				LL_PING_REQ					0x12
#define					LL_PING_RSP					0x13


#define					SLAVE_LL_ENC_OFF			0
#define					SLAVE_LL_ENC_REQ			1
#define					SLAVE_LL_ENC_RSP_T			2
#define					SLAVE_LL_ENC_START_REQ_T	3
#define					SLAVE_LL_ENC_START_RSP		4
#define					SLAVE_LL_ENC_START_RSP_T	5
#define					SLAVE_LL_ENC_PAUSE_REQ		6
#define					SLAVE_LL_ENC_PAUSE_RSP_T	7
#define					SLAVE_LL_ENC_PAUSE_RSP		8
#define					SLAVE_LL_REJECT_IND_T		9

#define					LL_ENC_REQ					0x03
#define					LL_ENC_RSP					0x04
#define					LL_START_ENC_REQ			0x05
#define					LL_START_ENC_RSP			0x06

#define					LL_PAUSE_ENC_REQ			0x0a
#define					LL_PAUSE_ENC_RSP			0x0b
#define					LL_REJECT_IND				0x0d

#define			BLT_ENABLE_ADV_37			BIT(0)
#define			BLT_ENABLE_ADV_38			BIT(1)
#define			BLT_ENABLE_ADV_39			BIT(2)
#define			BLT_ENABLE_ADV_ALL			(BLT_ENABLE_ADV_37 | BLT_ENABLE_ADV_38 | BLT_ENABLE_ADV_39)

#define			BLT_LINK_STATE_ADV			0
#define			BLT_LINK_STATE_CONN			1
#define			BLT_LINK_STATE_CONNECTED	2
#define			BLT_LINK_STATE_IDLE			0
#define			BLT_LINK_STATE_START		8
#define			BLT_LINK_STATE_LOST			9

enum {
	FLG_SYS_LINK_IDLE					= 0,
	FLG_SYS_LINK_ADV					= 1,
	//FLG_SYS_LINK_SCAN					= 2,
	FLG_SYS_LINK_WAKEUP					= 3,
	FLG_SYS_LINK_LISTEN					= 4,
	FLG_SYS_LINK_BROADCAST				= 5,
	FLG_SYS_LINK_CONNECTTING			= 6,
	FLG_SYS_LINK_CONNECTED				= 7,
	FLG_SYS_LINK_BRIDGE					= FLG_SYS_LINK_BROADCAST,

	FLG_SYS_LINK_START					= 8,
	FLG_SYS_LINK_LOST					= 9,
	FLG_SYS_LINK_STOP					= 10,
	FLG_SYS_LINK_MISSING				= 11,
	FLG_SYS_DEVICE_FOUND				= 0x40,
};

/* Advertisement Type */
typedef enum{
  ADV_TYPE_CONNECTABLE_UNDIRECTED             = 0x00,  // ADV_IND
  ADV_TYPE_CONNECTABLE_DIRECTED_HIGH_DUTY    = 0x01,  // ADV_INDIRECT_IND (high duty cycle)
  ADV_TYPE_NONCONNECTABLE_UNDIRECTED             = 0x02 , // ADV_NONCONN_IND
  ADV_TYPE_SCANNABLE_UNDIRECTED                      = 0x03 , // ADV_SCAN_IND
  ADV_TYPE_CONNECTABLE_DIRECTED_LOW_DUTY     = 0x04,  // ADV_INDIRECT_IND (low duty cycle)
}advertising_type;

typedef void (*irq_st_func) (void);

#define						BLT_BRX_CRC_ERROR			2
#define						BLT_BRX_CRC_OK				1
#define						BLT_BRX_TIMEOUT				0

#define			SUSPEND_ADV				BIT(0)
#define			SUSPEND_CONN			BIT(1)
#define			DEEPSLEEP_ADV			BIT(2)
#define			DEEPSLEEP_CONN			BIT(3)
#define			SUSPEND_DISABLE			BIT(7)


#define 		LOWPOWER_ADV			( SUSPEND_ADV  | DEEPSLEEP_ADV  )
#define 		LOWPOWER_CONN			( SUSPEND_CONN | DEEPSLEEP_CONN )

//This mode is only available for 17H26 new SDK, by yizan
#if LOW_COST_EVENT_CB_MODE
//extern void task_beacon_done(rf_packet_connect_t* p);
//extern void task_before_advertising(rf_packet_connect_t* p);
extern void task_connection_established(rf_packet_connect_t* p);
extern void task_connection_terminated(rf_packet_connect_t* p);
extern void task_bond_finished(rf_packet_connect_t* p);

/*************Because of OTP resource limites, only following events are available for current SDK**************/
/*task_beacon_done
 *This event is returned when one beacon packet has been sent, 
 *ex:it is usually called while beacon packet is changed every period*/
#define			BLT_EV_FLAG_BEACON_DONE				BIT(0)

/*task_before_advertising
 * This event is returned before the advertising packet has been sent, 
 * ex: turn on led before advertising
 */
#define			BLT_EV_FLAG_ADV_PRE					BIT(1)

/*task_connection_established
 * This event is returned once module receives a connection request packet
 * and establishs a connection successfully
 * ex: start send connection parameter update request after a time from 
 * the connection event; notify application connection establishment state*/
#define			BLT_EV_FLAG_CONNECT					BIT(2)

/*task_connection_terminated
 * This event is returned once connection is terminated
 * ex:notify application connection terminated; reset connection para*/
#define			BLT_EV_FLAG_TERMINATE				BIT(3)

/*task_bond_finished
 * This event is returned once encryption process is finished
 * ex: HID key can be used once connection is encrypted*/
#define			BLT_EV_FLAG_BOND_START				BIT(4)

/*************Because of OTP resource limites, following events are not available for current SDK**************/
#if 0
/*task_after_advertising
  *This event is returned after the advertising packet has been sent,
  *ex: turn on led after advertising
  **/
#define			BLT_EV_FLAG_ADV_POST				2

/*task_scan_response_received
 * This event is returned once module receives a scan request packet*/
#define			BLT_EV_FLAG_SCAN_RSP				3



/*task_sleep_wakeup
 *This event is returned once sleep is waked up as expected(not by button)*/
#define			BLT_EV_FLAG_WAKEUP					6

/*task_connection_event_finished
  *This event is returned one connection event is finished(RX&TX with remote),
  *ex: start process some other tasks, like audio collection*/
#define			BLT_EV_FLAG_BRX						7

/*task_sleep_start
 * This event is returned before entering sleep*/
#define			BLT_EV_FLAG_SLEEP					8

/*task_idle
 * This event is returned while cpu in idle state
 * ex: start ADC collection, or receive uart data, etc*/
#define			BLT_EV_FLAG_IDLE					9

/*task_sleep_wakeup_early
 * This event is returned when sleep is waked up in advance(ex,by button)
 * ex: key scan immediately to aquire the current key pressed */
#define			BLT_EV_FLAG_EARLY_WAKEUP			10

/*task_channel_update_req
 * This event is returned when master device has sent a channel 
 * map update request*/
#define			BLT_EV_FLAG_CHN_MAP_REQ				11

/*task_connection_para_update_req
 * This event is returned when master device has sent a connection
 * parameter update request*/
#define			BLT_EV_FLAG_CONN_PARA_REQ			12

/*task_channel_update_start
 * Master send a channel map update request and leave slave a buffer
 * period (ex, dozes of connection intervals). The new channel map would
 * be taken effect after the buffer period and this event will be returned*/
#define			BLT_EV_FLAG_CHN_MAP_UPDATE			13

/*task_connection_para_update_start
 * Master send a connection parameter update request and leave slave a buffer
 * period (ex, dozes of connection intervals). The new connection para would
 * be taken effect after the buffer period and this event will be returned*/
#define			BLT_EV_FLAG_CONN_PARA_UPDATE		14


/*task_set_wakeup_source
  * This event is returned before entering sleep and user needs to set
  * wakeup source in high layer*/
#define			BLT_EV_FLAG_SET_WAKEUP_SOURCE		16
#endif

#else
typedef void (*blt_event_callback_t)(u8 e, u8 *p);
#define			BLT_EV_FLAG_BEACON_DONE				0
#define			BLT_EV_FLAG_ADV_PRE					1
#define			BLT_EV_FLAG_ADV_POST				2
#define			BLT_EV_FLAG_SCAN_RSP				3
#define			BLT_EV_FLAG_CONNECT					4
#define			BLT_EV_FLAG_TERMINATE				5
#define			BLT_EV_FLAG_WAKEUP					6
#define			BLT_EV_FLAG_BRX						7
#define			BLT_EV_FLAG_SLEEP					8
#define			BLT_EV_FLAG_IDLE					9
#define			BLT_EV_FLAG_EARLY_WAKEUP			10
#define			BLT_EV_FLAG_CHN_MAP_REQ				11
#define			BLT_EV_FLAG_CONN_PARA_REQ			12
#define			BLT_EV_FLAG_CHN_MAP_UPDATE			13
#define			BLT_EV_FLAG_CONN_PARA_UPDATE		14
#define			BLT_EV_FLAG_BOND_START				15
#define			BLT_EV_FLAG_SET_WAKEUP_SOURCE		16

#endif



extern u8				blt_state;
extern u32				blt_next_event_tick;
extern u32				blt_conn_interval;
extern u16				blt_conn_latency;

void	blt_init (u8 *p_mac, u8 *p_adv, u8 *p_rsp);
void	blt_init_timing_hid ();
void	blt_init_timing ();

void	blt_adv_init ();

void	blt_set_channel (signed char chn);

int		blt_packet_tx_crc (u8 *pd, u8 *ps);

void	blt_get_crc_table (u8 *p, u32 *pt);

void	blt_connection_init (int crc, u8 * paccesscode);

void	blt_pn_init (int pn_init,u32* pn_tbl_ptr);
static inline void blt_pn_tbl_calc( int pn_init, u32 *pt);

void	blt_set_crc_init (int init);

void	blt_packet_tx_pn (u32 *pd, u32 *ps);
void	blt_packet_tx_pn_calc (u32 *pd, u32 *ps, u32 *px);

//u8		blt_packet_rx (u32 timeout, int send_tx);

void	blt_set_adv (u8 *p, u8 *pr);

void	blt_set_adv_interval (u32 t_us);

u8*		blt_send_adv (int mask);

//u8		blt_connect ();

u8		blt_brx ();

u8		blt_brx_proc ();

u8		blt_push_fifo (u8 *p);

void	blt_set_att_table (u8 *p);

void	blt_set_att_default ();

void	blt_set_connParaUpReq (u8 *p);

void	blt_brx_timing_update (u32 t, int st);

u8		blt_push_notify (u16 handle, u32 val, int len);

u8		blt_push_notify_data (u16 handle, u8 *p, int len);

u8		blt_push_notify_data_split (u16 handle, u8 *p, int len);


u8		blt_enable_suspend (u8 en);
u8 		blt_get_suspend_mask (void);

#if(!LOW_COST_EVENT_CB_MODE)
void blt_register_event_callback (u8 e, blt_event_callback_t p);
#endif

u8		blt_fifo_num ();

void	blt_conn_para_request (u16 min_interval, u16 max_interval, u16 latency, u16 timeout);

void 	blt_update_conn_para (u16 min_interval, u16 max_interval, u16 latency, u16 timeout);
void 	blt_update_parameter_request ();
void	blt_set_adv_channel (u8 m);
void    blt_set_adv_enable(u8 en);

void 	blt_set_wakeup_source(int src);
void 	blt_set_latency_off(void);

void    blt_reject_conn_para_update_req(void);

void 	blt_enable_muc_stall(u8 en);

u32 blt_get_wakeup_time(void);



#if(MCU_CORE_TYPE == MCU_CORE_8266 || MCU_CORE_TYPE == MCU_CORE_17H26)

void 		blt_set_adv_type(u8 type);

#endif


void beacon_register_connreq_cb (void *p);  //Only used by beacon app



//adv filter policy
#define ALLOW_SCAN_WL								BIT(0)
#define ALLOW_CONN_WL								BIT(1)

#define ADV_FP_ALLOW_SCAN_ANY_ALLOW_CONN_ANY        0x00  // Process scan and connection requests from all devices
#define ADV_FP_ALLOW_SCAN_WL_ALLOW_CONN_ANY         0x01  // Process connection requests from all devices and only scan requests from devices that are in the White List.
#define ADV_FP_ALLOW_SCAN_ANY_ALLOW_CONN_WL         0x02  // Process scan requests from all devices and only connection requests from devices that are in the White List..
#define ADV_FP_ALLOW_SCAN_WL_ALLOW_CONN_WL          0x03  // Process scan and connection requests only from devices in the White List.


//clear whitelist
void ll_whiteList_reset(void);

//get current whitelist addr num (0 for empty, MAX_WHITE_LIST_SIZE for max)
int ll_whiteList_getCurNum(void);

//search if addr is in whitelist: return 1 for  in, 0 for not in
int ll_addrTable_search(u8 type, u8 *addr);

//add addr to whitelist, return 1 OK(if addr already in whitelist, not add again, also return 1),
//						 return 0 ERR(whitelist full)
int ll_whiteList_add(u8 type, u8 *addr);

//delete addr from whitelist,  if addr not in whitelist, do nothing
//it is recommended that to see if addr is in whitelist before delete it
void ll_whiteList_delete(u8 type, u8 *addr);

void blt_adv_filterpolicy_set(u8 policy);
