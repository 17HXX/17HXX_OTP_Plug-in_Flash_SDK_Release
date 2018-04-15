#include "ui.h"
#include "../../proj_lib/ble_l2cap/ble_ll_ota.h"

#include "../../proj/drivers/flash.h"
#include "slave_dev.h"

static u32 BLE_write_time = 0;
static u8 gp18_level_can_Read = 1;
extern u8 read_ask;
extern u8 app_send_flag;
extern u8 length_read;
extern u8 after_master_write;
extern u8 put_len;
extern u8 temp_buff_send_app[20];
extern u8 can_suspend_flag;
extern u8 allow_read;
extern u8 ask_mode_flag;
extern u8 run_where;
extern u8 from_app_step;

//static inline void send_databuf_tmp();
// Enable TAIL_BOOT_CODE_PRESET to embed bootcode to bin file, 
// such make bin file size to be exact 16K
#define  TAIL_BOOT_CODE_PRESET		0
#if(TAIL_BOOT_CODE_PRESET)
volatile static u8 test_boot_code = 0;
_attribute_custom_code_  volatile u8 const boot_code[] = {
0x02,0x00,0x00,0xC5,0xFF,0xFF,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0x0F,0xFC,
0xBF,0x98,0x02,0x06,0xBF,0x01,0x03,0x06,0x3F,0xF8,0x00,0x00,0xFF,0xFF,0xFF,0xFF
};
#endif


////////////////////////////////cfg address  /////////////

#if (1)
#define		SUSPEND_STATE			SUSPEND_CONN | SUSPEND_ADV
#else
#define		SUSPEND_STATE			0
#endif

#if(OTA_ENABLE)
#define TEST_OTA_1 0
#endif

#define  TEST_SUSPEND_TIME_ENABLE 0

#define ADV_LED_PORT  			GPIO_GP7


#define LOW_ADV_INTERVAL 		50	//700	//700	///50//700//20//20  //
#define PRODUCT_UUIDH 			0xFF
#define PRODUCT_UUIDL			0xE0
#define PRODUCT_ID1				0x06
#define PRODUCT_ID2				0x01
#define ADDRESS_OFFSET			19


void blt_disable_latency(){
	//disable current latency
	extern u8 blt_retry ;
	blt_retry = 1;
}

u8  tbl_mac [] = {0x11, 0x10, 0x11, 0x01, 0x32, 0x23};
u8	tbl_rsp [] =
{
	0x00, 30,								//type len
	0, 0, 0, 0, 0, 0,		//mac address
	23,0x09, 'T', 'h', 'e', ' ', 'I', 'I', 'C', ' ', 'S', 'L',
	'A', 'V', 'E', '_', 'D', 'e', 'v', ' ', 'D', 'e', 'm', 'o',
	0, 0, 0									//reserve 3 bytes for CRC
};

u8	tbl_adv [] =
{
	0x00, 25,		// length must <=37
	0, 0, 0, 0, 0, 0,		//mac address
	0x02, 0x01, 0x06,
	0x03, 0x02, PRODUCT_UUIDL, PRODUCT_UUIDH,		// incomplete list of service class UUIDs (0x1812, 0x180F)
	0x0b, 0xff, PRODUCT_ID1, PRODUCT_ID2, 0xFF, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0, 0, 0,			//reserve 3 bytes for CRC
};





static inline void user_define_by_mac_address()
{
	u8 temp_mac[6]={0x00};
	u32 *pmac = (u32 *) CFG_ADR_MAC_ADDR;
	if (*pmac != 0xffffffff) {
		memcpy (temp_mac, pmac, 6);
	}
	else {
		memcpy (temp_mac, tbl_mac, 6);
	}
	tbl_adv[ADDRESS_OFFSET] = temp_mac[5];
	tbl_adv[ADDRESS_OFFSET+1] = temp_mac[4];
	tbl_adv[ADDRESS_OFFSET+2] = temp_mac[3];
	tbl_adv[ADDRESS_OFFSET+3] = temp_mac[2];
	tbl_adv[ADDRESS_OFFSET+4] = temp_mac[1];
	tbl_adv[ADDRESS_OFFSET+5] = temp_mac[0];
}


///////////////////////////////////// proc_ui ///////////////////////////////////////////

////////////////////////////////////// proc send data ///////////////////////////////////

//extern u16 blt_conn_inst;
//extern u8 os_check;
/********************************************* user define****************/

u8 device_status_tmp=0;
u32 tick_app_wakeup = 0;
u32 tick_connected_timer_tmp=0;

static inline void gatt_init_tmp()
{
	blt_init (tbl_mac, tbl_adv, tbl_rsp);			//get mac addr
	shutter_att_init ();
	blt_suspend_mask = SUSPEND_STATE;

	//////////////////// enable different event call back functions /////////
	 /*Decide whether event cb should be called by SDK,should be defined in user_init*/

		 
	//////////////////// enable attribute table write/read call back functions /////////
	/*Use l2cap_att_read_write_cb_flag to decide whether sdk should call att_read_cb/att_write_cb
	 * when remote device process read/write operation ,should be defined in user_init*/
//	extern u8 l2cap_att_read_write_cb_flag ;
//	l2cap_att_read_write_cb_flag = 0;//ATT_READ_CB_ENABLE  | ATT_WRITE_CB_ENABLE | ATT_RSP_CB_ENABLE
}

static inline void rf_set_power_level_tmp()
{
	/*
	0x25, 0x7c, 0x67, 0x67,		// 7 dBm
	0x0a, 0x7c, 0x67, 0x67,		// 5 dBm
	0x06, 0x74, 0x43, 0x61,		// -0.6
	0x06, 0x64, 0xc2, 0x61,		// -4.3
	0x06, 0x64, 0xc1, 0x61,		// -9.5
	0x05, 0x7c, 0x67, 0x67,		// -13.6
	0x03, 0x7c, 0x67, 0x67,		// -18.8
	0x02, 0x7c, 0x67, 0x67,		// -23.3
	0x01, 0x7c, 0x67, 0x67,		// -27.5
	0x00, 0x7c, 0x67, 0x67,		// -30
	0x00, 0x64, 0x43, 0x61,		// -37
	0x00, 0x64, 0xcb, 0x61,		// -max	power down PA & PAD
*/	
	analog_write (0xa2, 0x06);
	analog_write (0x04, 0x74);
	analog_write (0xa7, 0x43);
	analog_write (0x8d, 0x61);
}

void OTA_init_tmp()
{
#if(OTA_ENABLE)	
	u8 buf[4] = {0};
	flash_read_page(OTA_FLASH_ADDR_START, 4, buf);
	u32 tmp = buf[0] | (buf[1]<<8) |(buf[2]<<16) | (buf[3]<<24);
	if(tmp != ONES_32){
		flash_erase_block(OTA_FLASH_ADDR_START);
		//ota_reboot_tmp();
		sleep_us(1*1000*1000);	// because flash_erase_block may exit premature, becuase of flash_wait_done
	}
#endif
}
void user_init()
{
#if(TAIL_BOOT_CODE_PRESET)
	if(test_boot_code){
		int i;
		att_response_cb(boot_code + i);
	}
#endif
	
#if(DEBUG_FROM_FLASH)
	OTA_init_tmp();
	set_tp_flash();
	set_freq_offset_flash(0x56);
	set_mac_flash(tbl_mac);
//	static u32 chip_id;
//	chip_id = read_chip_ID_flash();
#else
	set_tp_OTP();
	set_freq_offset_OTP(0x56);
	set_mac_OTP(tbl_mac);
//	static u32 chip_id;
//	chip_id = read_chip_ID_OTP();
#endif
	
	rf_set_power_level_tmp();
	user_define_by_mac_address();
	gatt_init_tmp();

	slave_dev_init();		//slave device init
}


//ATT_OP_READ_REQ:
//rf_packet_att_read_t

int att_read_cb(void*p ){
	rf_packet_att_read_t *req= (rf_packet_att_read_t*)p;

     return ATT_NO_HANDLED;

}


/*Master write my_Attributes,  sdk firstly call att_write_cb. So user shall decide here 
 * to allow or disallow the write operation and return different value 
 * User should not modify the name of function and shall not delete it even if user don't
 * need this function
 *
 * Return: ATT_NO_HANDLED means user has not processed the write operation,
 *              SDK should also write the value automatically
 *             ATT_HANDLED means user has processed the write operation,
 *             SDK should not re-write the value*/
int att_write_cb(void*p)
{
	rf_packet_att_write_t *src = (rf_packet_att_write_t*)p;
	u8 *value;
	value=&src->value;
	read_ask = 1;
	can_suspend_flag = 0;
	app_send_flag = 1;
	allow_read = 0;
	length_read = src->l2capLen;
	#if(OTA_ENABLE)
	 if(src->handle == OTA_CMD_OUT_DP_H){
		u8 result=otaWrite(src);
		
		return ATT_HANDLED;
	}
#endif
     return ATT_NO_HANDLED;
}
/*
 other opcode
 * */
void att_response_cb( u8 *p){
	rf_packet_l2cap_req_t * req = (rf_packet_l2cap_req_t *)p;
	return;
}


 /*Following functions are used to define different events, details please refers to blt_ll.h, user
  * can use flag ll_event_cb_flag to decide whether call this event*/
#if (LOW_COST_EVENT_CB_MODE)
  
  /*Decide whether event cb should be called by SDK,should be defined in user_init*/
  //ll_event_cb_flag = BLT_EV_FLAG_CONNECT  | BLT_EV_FLAG_TERMINATE | BLT_EV_FLAG_BOND_START;

/*task_connection_established
 * This event is returned once module receives a connection request packet
 * and establishs a connection successfully
 * ex: start send connection parameter update request after a time from 
 * the connection event; notify application connection establishment state*/
 
void task_connection_established(rf_packet_connect_t* p){
	//adv_start_tick = last_update_paramter_time = clock_time();// in bond state better
	//adv_time_cnt = 0;
	tick_connected_timer_tmp=clock_time();
	device_status_tmp=CONNECTED_DEVICE_STATUS;
}

/*task_connection_terminated
 * This event is returned once connection is terminated
 * ex:notify application connection terminated; reset connection para*/
//volatile u8 aa_cnt = 0;
void task_connection_terminated(rf_packet_connect_t* p){
	//app_wakeup_tick = adv_start_tick = clock_time();
	//adv_time_cnt = 0;
	device_status_tmp=POWER_ON_DEVICE_STATUS;
}

/*task_bond_finished
 * This event is returned once encryption process is finished
 * ex: HID key can be used once connection is encrypted*/

void task_bond_finished(rf_packet_connect_t* p){
}
#endif


/**********************ui start ************************************/
//"KEY_BIT_VR" must be consistent with "ordinary_key_matrix"
void vr_autoSetMode(){
//#if (AUTO_CKECK_OS_TYPE_FLAG)
//	if(3 == os_check){
//		vr_mode_tmp = IOS_ICADE_MODE;
//	}else if(2 == os_check){
//		vr_mode_tmp = ANDROID_GAME_MODE;
//	}
//#endif
}
static inline void TC_IIC_process()
{
	//slave device mode 从机模式
/********************************************************************************
 * 		The GP18 used as a signal pin
 * 		write 50ms high level ask the master to read it
 * *****************************************************************************/
	static u32 delay_50ms_time = 0;
	static u32 GP18_wait_600ms = 0;
	static u8 gp18_FLAG = 0;
	if(allow_read || read_ask)
	{
		if(allow_read)
		{
			ask_mode_flag = 0;		//master下发数据
		}
		else
		{
			ask_mode_flag = 1;		//APP	下发数据
		}
		run_where = 2;
		read_ask = 0;
		allow_read = 0;
		gp18_level_can_Read = 0;
		gpio_set_output_en(GPIO_GP18,1);
		gpio_set_input_en(GPIO_GP18,0);
		gpio_write(GPIO_GP18,1);
		BLE_write_time = clock_time();
	}
	if(BLE_write_time != 0)
	{
		if(clock_time_exceed(BLE_write_time,50*1000))		//GP18  send 50ms high level, and then close output ,enable input;
		{
			BLE_write_time = 0;
			gpio_write(GPIO_GP18,0);
			gpio_set_output_en(GPIO_GP18,0);
			gpio_set_input_en(GPIO_GP18,1);
			gp18_level_can_Read = 1;
		}
	}
/***************************when master write IIC,slave receive over and send data to APP*****************************/
	//
	if(after_master_write == 1 && (from_app_step == 0) && (put_len!= 0 )&& (delay_50ms_time == 0))
	{
		delay_50ms_time = clock_time();

	}
	if(after_master_write == 1 && (from_app_step != 1) && (put_len!= 0) && (clock_time_exceed(delay_50ms_time,100*1000)))
	{
		run_where = 3;
		delay_50ms_time = 0;
		after_master_write = 0;
		blt_push_notify_data(17, temp_buff_send_app , put_len);
		put_len = 0;
	}
/***********************The flag that can use to allow suspends mode or no****************************/
	if((gp18_level_can_Read && (!!gpio_read(GPIO_GP18))))
	{
		if(GP18_wait_600ms == 0)
		{
			GP18_wait_600ms = clock_time();
		}
		if(GP18_wait_600ms != 0 && gp18_FLAG == 0 && clock_time_exceed(GP18_wait_600ms , 10*1000))
		{
			GP18_wait_600ms = clock_time();
			gp18_FLAG = 1;
		}
	}
	if(GP18_wait_600ms != 0 && clock_time_exceed(GP18_wait_600ms , 200*1000))
	{
		GP18_wait_600ms = 0;
		gp18_FLAG = 0;
	}
	if(gp18_FLAG == 1 || can_suspend_flag == 0){
		blt_suspend_mask = 0;
	}
	else{
		blt_suspend_mask = SUSPEND_STATE;
	}
/*****************************deal with the data from app or master********************************/
	deal_rev_data_from_app();  	//deal with data from app
	deal_send_data_to_app();	//deal with data to app

}
static inline void user_ui_process()
{

	//user code
}
static inline void public_loop()
{
	blt_brx_sleep (tick_app_wakeup);
	if(blt_state!=BLT_LINK_STATE_ADV){
		blt_brx ();
	}
	else {
		// Must be on the final
		blt_send_adv (BLT_ENABLE_ADV_ALL);
		//blt_send_adv (BLT_ENABLE_ADV_38);
	}
}

void main_loop()
{
//	extern u8 start_ota_flag;
//	if(start_ota_flag==0)
//	{
//		user_ui_process();
//	}
	TC_IIC_process();	// IIC_SLAVE process
	//work LED --- GP7
	static u32 work_time = 0;
	static u8 work_state = 0;
	if(work_time == 0)
	{
		work_time = clock_time();
	}
	if(clock_time_exceed(work_time,500*1000))
	{
		gpio_write(GPIO_GP7,work_state);
		work_state ^= 1;
		work_time = 0;
	}
	user_ui_process();		//user code
	if (blt_state == BLT_LINK_STATE_ADV)
	{
		blt_adv_interval = ((rand()% 10) + LOW_ADV_INTERVAL-1)*CLOCK_SYS_CLOCK_1MS;
	}
	else {
		if((device_status_tmp==CONNECTED_DEVICE_STATUS)&& clock_time_exceed(tick_connected_timer_tmp,1*1000*1000))
		{
			device_status_tmp=AFTER_CONNECTED_DEVICE_STATUS;
			blt_update_connPara_request(160,180,4,400);
		}
	}
/******************************public area*******************/
	public_loop();
}
