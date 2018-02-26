#include "ui.h"
#include "../../proj_lib/ble_l2cap/ble_ll_ota.h"

#include "../../proj/drivers/flash.h"

static inline void send_databuf_tmp();

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


void blt_disable_latency(){
	//disable current latency
	extern u8 blt_retry ;
	blt_retry = 1;
}


u8  tbl_mac [] = {0x20, 0x17, 0x06, 0x29, 0x01, 0x09};
u8	tbl_adv [42] =
	{	0x00, 37,
		0, 0, 0, 0, 0, 0,		//mac address
		0x02, 0x01, 0x06, 							// BLE limited discoverable mode and BR/EDR not supported
		0x03, 0x02, 0x12, 0x18,		// incomplete list of service class UUIDs (0x1812, 0x180F)
		0x03,0x19,GAP_APPEARE_ROLE&0x0ff,(GAP_APPEARE_ROLE>>8)&0xff,

		19, 0x09, 	  
		'D','E','M','O','_','H','I','D','_','0','1','1','0',' ',' ',' ',' ',' ',// must be is 18 byte
		0, 0, 0			//reserve 3 bytes for CRC
	};
u8	tbl_rsp [] =
		{0x04, 6,								//type len
		  0, 0, 0, 0, 0, 0,		//mac address
		 0, 0, 0									//reserve 3 bytes for CRC
		};




///////////////////////////////////// proc_ui ///////////////////////////////////////////

////////////////////////////////////// proc send data ///////////////////////////////////

extern u16 blt_conn_inst;
extern u8 os_check;
/********************************************* user define****************/


u16 button_value_tmp=0; 
u16 button_last_value_tmp=0;

u16 normal_key_tmp=0;
u16 last_normal_key_tmp=0;

u16 consumer_key_tmp=0;
u16 last_consumer_key_tmp=0;

u16 joystic_key_tmp=0;
u16 last_joystic_key_tmp=0;
u16 joystic_buf_tmp=0;

u8 last_mouse_key_tmp=0;
u8 mouse_buf_tmp[4]={0,0,0,0};

u8 flag_has_new_event_tmp=0;

u8 device_status_tmp=0;

u8 flag_start_adv_tmp=0;

u32 tick_adv_timer_tmp=0;
u32 tick_led_timer_tmp=0;
u32 tick_app_wakeup = 0;
u32 tick_connected_timer_tmp=0;

u8  connected_idle_time_count_tmp=0;
u8  adv_start_count_tmp=0;
//u8 flag_power_key_press_tmp=0;
//u8 flag_change_mode_key_press_tmp=0;
u32 tick_power_key_press_tmp=0;

u8 cur_led_state_tmp = 0;

static u8 battLevel_tmp = 100;
u32 tick_batt_timer_tmp=0;
u8 need_low_battery_alarm_tmp=0;

u32 tick_hardware_scan_tmp=0;


#define  CFG_DEVEICE_NAME_LEN 32-1
static inline void  device_name_extern_config_init()
{
  #if 1
	int i = 0;
	u8	dev_name_len = 0;
	u32 dev_name_uburing_addr = CFG_DEVEICE_NAME_ADDR;  //3fa0 3fb0 3fc0 3fd0	64bytes
	u8 *reslut_device;
	// get device name data.
	for(i=0; i<32; i++){
		if((*(u8*)(CFG_DEVEICE_NAME_ADDR+CFG_DEVEICE_NAME_LEN-i) != 0)  && (*(u8*)(CFG_DEVEICE_NAME_ADDR+CFG_DEVEICE_NAME_LEN-i) != 0xff) ){
			if(dev_name_len == 0){
				dev_name_uburing_addr = CFG_DEVEICE_NAME_ADDR+CFG_DEVEICE_NAME_LEN-i;
			}
			dev_name_len ++;
		}else{
			if(dev_name_len){
				break;
			}
		}
	}
	reslut_device =(u8*)(dev_name_uburing_addr-dev_name_len+1);

	if(dev_name_len != 0)// no device name in device name under buring
	{
		memset((u8*)(tbl_adv+21),0x20,18);
		memcpy((u8*)(tbl_adv+21) , reslut_device, dev_name_len);
		
	}
#else
	int i = 0;
		u8	dev_name_len = 0;
		u32 dev_name_uburing_addr = CFG_DEVEICE_NAME_ADDR;	//3fa0 3fb0 3fc0 3fd0	64bytes
		

	// get device name data.
	for(i=0; i< 16; ++i){
		if((*(u8*)(CFG_DEVEICE_NAME_ADDR+i) != 0)  && (*(u8*)(CFG_DEVEICE_NAME_ADDR+i) != 0xff) ){
			if(dev_name_len == 0){
				dev_name_uburing_addr = (u8*)(CFG_DEVEICE_NAME_ADDR+i);
			}
			dev_name_len ++;
		}else{
			if(dev_name_len){
				break;
			}
		}
	}
	//reslut_device =(u8*)(dev_name_uburing_addr);

	if(dev_name_len != 0)// no device name in device name under buring
	{
			// init tb1 rsp
		tbl_adv[1] = 19 + dev_name_len;	// rf len
		tbl_adv[19] = dev_name_len + 1;
		memcpy((u8*)(tbl_adv+21) , dev_name_uburing_addr, dev_name_len);
		
	}
#endif
	
}	
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
void test_init_tmp()
{
	gpio_write(GPIO_GP4,0);
	gpio_set_output_en(GPIO_GP4,1);
	gpio_set_output_en(GPIO_GP5,1);
	gpio_set_output_en(GPIO_GP7,1);
	gpio_set_input_en(GPIO_GP10,1);
	gpio_set_output_en(GPIO_GP10,0);
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
	set_freq_offset_flash(0x58);
	set_mac_flash(tbl_mac);
//	static u32 chip_id;
//	chip_id = read_chip_ID_flash();
#else
	set_tp_OTP();
	set_freq_offset_OTP(0x58);
	set_mac_OTP(tbl_mac);
//	static u32 chip_id;
//	chip_id = read_chip_ID_OTP();
#endif
	
	device_name_extern_config_init();
	
	rf_set_power_level_tmp();
	gatt_init_tmp();

	
	tick_led_timer_tmp=clock_time();
	tick_connected_timer_tmp=tick_led_timer_tmp;
	tick_hardware_scan_tmp=clock_time();
	test_init_tmp();
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
	tick_batt_timer_tmp=tick_connected_timer_tmp;
	connected_idle_time_count_tmp=0;
	battLevel_tmp=100;

	gpio_write(ADV_LED_PORT,1);
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
	gpio_write(GPIO_GP4,1);
	// clear smp
	blt_smp_paring_req_recvd = 1;
	hid_setting_flag(0);
}

/*task_bond_finished
 * This event is returned once encryption process is finished
 * ex: HID key can be used once connection is encrypted*/

void task_bond_finished(rf_packet_connect_t* p){
	if(!blt_smp_paring_req_recvd){// reconnection
		if(os_check == 2){
			hid_setting_flag(1);
		}
	}
}
#endif


/**********************ui start ************************************/
//"KEY_BIT_VR" must be consistent with "ordinary_key_matrix"
void vr_autoSetMode(){
#if (AUTO_CKECK_OS_TYPE_FLAG)
	if(3 == os_check){
		vr_mode_tmp = IOS_ICADE_MODE;
	}else if(2 == os_check){
		vr_mode_tmp = ANDROID_GAME_MODE;
	}
#endif
}
u32 count = 0;
void test_key_tmp()
{
	if(blt_state == BLT_LINK_STATE_ADV)
		count = 0;
	if(clock_time_exceed(tick_connected_timer_tmp,1*1000*1000))// 10s timer out
	{
		tick_connected_timer_tmp=clock_time();
		count++;
		if((count < 10) || (count > 20))
			return;
		flag_has_new_event_tmp|=SEND_C_DATA;
		if(count==10)
		{
			
			reportConsumerControlIn[0]=0xea;
		}
		else if(count==11)
		{
			reportConsumerControlIn[0]=0xe9;
		}
		else 
		{
			count=22;
			reportConsumerControlIn[0]=0;
		}
		
	}
}
void test_suspend_time_tmp()
{
#if(TEST_SUSPEND_TIME_ENABLE)
static u8 test=0;
    test++;
	gpio_write(GPIO_GP5,test%2);
#endif
}

u32 button_value = 0;
u32 button_value_bcup = 0;			//back up of  button

static inline u8 button_get_status(u32 pin)
{
	u8 value=0;//no button press
#if 0
	if(gpio_read(pin))//has button press
	{
		//gpio_set_output_en(pin, 1);
		gpio_setup_up_down_resistor(pin,PM_PIN_PULLDOWN_100K);
			//gpio_set_output_en(pin, 0);
		sleep_us(20);
			
		if(gpio_read(pin))
		{
			value=1;
		}
		else
		{
			value=2;
		}
	}
	gpio_setup_up_down_resistor(pin,PM_PIN_UP_DOWN_FLOAT);
#else
	gpio_setup_up_down_resistor(pin,PM_PIN_UP_DOWN_FLOAT);
	gpio_write(pin,1);
	sleep_us(20);
	if(!gpio_read(pin))
	{
		value=1;
	}

	gpio_setup_up_down_resistor(pin,PM_PIN_PULLDOWN_100K);
	gpio_write(pin,0);
	sleep_us(20);
	if(gpio_read(pin))
	{
		value=2;
	}
#endif
 	return value;
}





u16  senddata =0;
u8 sendflag =0;
static inline u16  button_get_value()
{
	u16 status,value;

	value=0;

	status=button_get_status(GPIO_GP10);//GPIO_GP10
	value|=(status==1)?0x01:((status==2)?0x02:0x00);
	return value;	
}

static inline void hw_scan(){
	button_value = button_get_value();
	if(button_value == button_value_bcup){
		return;
	}
	button_value_bcup = button_value;
	if(button_value == 0){
		flag_has_new_event_tmp|=SEND_C_DATA;
		reportConsumerControlIn[0]=0x0;
	}
	else{
		if(button_value&0x01){
			flag_has_new_event_tmp|=SEND_C_DATA;
			reportConsumerControlIn[0]=0xea;
		}
		else if(button_value&0x02){
			flag_has_new_event_tmp|=SEND_C_DATA;
			reportConsumerControlIn[0]=0xe9;
		}
	}


}
#if 0
static inline void adv_status_poll_tmp()
{
	 if(button_value_tmp!=0)
	 {
		device_status_tmp=POWER_ON_DEVICE_STATUS;
	 }
	 
	 if(device_status_tmp==POWER_ON_DEVICE_STATUS)
	 {
		device_status_tmp=HIGH_ADV_DEVICE_STATUS;
		
		 tick_adv_timer_tmp=clock_time();
		 adv_start_count_tmp=0;
		// tick_led_timer_tmp=tick_adv_timer_tmp;
		 
		 blt_set_adv_interval(HIGH_ADV_INTERVAL*1000);
	 }
	 else if((device_status_tmp==HIGH_ADV_DEVICE_STATUS)&&clock_time_exceed(tick_adv_timer_tmp,3000*1000))
	 {
		 device_status_tmp=LOW_ADV_DEVICE_STATUS;
		 blt_set_adv_interval(LOW_ADV_INTERVAL*1000);
	 }
	 else if((device_status_tmp==LOW_ADV_DEVICE_STATUS)&&clock_time_exceed(tick_adv_timer_tmp,60*1000*1000))
	 {//timer out 
		tick_adv_timer_tmp=clock_time();
		adv_start_count_tmp++;
		if(adv_start_count_tmp>=3)
		{
			// device_status_tmp=DEEP_SLEEP_DEVICE_STATUS;
			 gpio_write(ADV_GPIO_GP7,0);
			 
			// analog_write(VR_MODE_REG,vr_mode_tmp);
			 blt_sleep_wakeup (1, PM_WAKEUP_PAD, 0);
		}
	 }

	if(clock_time_exceed(tick_led_timer_tmp,200*1000))
	{
		tick_led_timer_tmp=clock_time();
		cur_led_state_tmp = !cur_led_state_tmp; 
		gpio_write(ADV_GPIO_GP7,cur_led_state_tmp);
	}
	 
}
static inline void connection_status_poll_tmp()
{// connection_state
/******************************user application area*******************/

	if(flag_has_new_event_tmp)
	{
		tick_connected_timer_tmp=clock_time();
		//tick_app_wakeup=tick_connected_timer_tmp + 20* CLOCK_SYS_CLOCK_1MS;
#if 0
		 if(blt_conn_latency != 0)
		{
			blt_update_connPara_request(40,60,4,600);
			//blt_update_conn_para(40,60,4,600);
			//blt_update_parameter_request();
			
		}
#endif
		connected_idle_time_count_tmp=0;
		//disable current latency
		//extern u8 blt_retry ;
		//blt_retry = 1;
		//blt_wakeup_src = 0;
	}
	else
	{
		if(clock_time_exceed(tick_connected_timer_tmp,CONNECTED_IDLE_TIME*1000*1000))// 600s timer out
		{
			tick_connected_timer_tmp=clock_time();
			//tick_app_wakeup=0;
			//blt_wakeup_src = PM_WAKEUP_CORE;
			//updata parama
		#if 0
			if((vr_mode_tmp>ANDRIOD_MOUSE_MOUSE)&&(blt_conn_interval >= 40*1250*CLOCK_SYS_CLOCK_1US))
			{
				blt_update_connPara_request(40,60,4,600);
			}
			else if( (blt_conn_interval >= 20*1250*CLOCK_SYS_CLOCK_1US))
			{
				blt_update_connPara_request(40,24,4,600);
			}
		#else
				if((blt_conn_interval <CONNECT_MIN_INTERVAL*1250*CLOCK_SYS_CLOCK_1US)||(blt_conn_latency != CONNECT_LATENCY))
				{
					blt_update_connPara_request(CONNECT_MIN_INTERVAL,CONNECT_MAX_INTERVAL,CONNECT_LATENCY,CONNECT_TIMEROUT);
					//blt_update_conn_para(40,60,4,600);
					//blt_update_parameter_request();
					
				}
		#endif
			//check 10 mintinues has not button press
			connected_idle_time_count_tmp++;
			if(connected_idle_time_count_tmp>=120)
			{
				//device_status_tmp=DEEP_SLEEP_DEVICE_STATUS;
				//analog_write(VR_MODE_REG,vr_mode_tmp);
				 blt_sleep_wakeup (1, PM_WAKEUP_PAD, 0);
			}	
			
		}
	/*	else if(connected_idle_time_count_tmp==0)
		{
			//tick_app_wakeup=tick_connected_timer_tmp + 20* CLOCK_SYS_CLOCK_1MS;
			//blt_retry = 1;
		} */
		
	}
	
   
//	send_databuf_tmp();
	
}

static inline void ble_status_poll_tmp()
{

	if (blt_state == BLT_LINK_STATE_ADV)
	{
		adv_status_poll_tmp();	
		
		blt_send_adv (BLT_ENABLE_ADV_ALL);	//BLT_ENABLE_ADV_37 |BLT_ENABLE_ADV_ALL
	}
	else
	{
		connection_status_poll_tmp();
	}
}
#endif
static inline void user_ui_process()
{
#if(TEST_SUSPEND_TIME_ENABLE==0)	
//	test_key_tmp();
	hw_scan();

#endif
}
static inline void public_loop()
{
	 blt_brx_sleep (tick_app_wakeup);
   if(blt_state!=BLT_LINK_STATE_ADV)
   {
	   blt_brx ();
	   
	   if(blt_conn_inst > 20 && os_check < 2)
	   {
		   os_check = 2;
		   vr_autoSetMode();
		   hid_setting_flag(1);    //  android set ccc at default
	   }
   }
   else
   {
		// Must be on the final
		blt_send_adv (BLT_ENABLE_ADV_ALL);
		//blt_send_adv (BLT_ENABLE_ADV_38);
   }
}

void main_loop()
{
	test_suspend_time_tmp();
	if(clock_time_exceed(tick_hardware_scan_tmp,20*1000))
	{
	  	tick_hardware_scan_tmp=clock_time();
	  	extern u8 start_ota_flag;
		if(start_ota_flag==0)
		{
			user_ui_process();
		}
		
	}

	{
	if (blt_state == BLT_LINK_STATE_ADV)
	{
		blt_wakeup_src = 0;
		flag_has_new_event_tmp=0;
		blt_adv_interval= 20 * CLOCK_SYS_CLOCK_1MS;
		#if(TEST_OTA_1)
			if(clock_time_exceed(tick_led_timer_tmp,1000*1000))
		#else
			if(clock_time_exceed(tick_led_timer_tmp,200*1000))
		#endif
		{
			tick_led_timer_tmp=clock_time();
			cur_led_state_tmp = !cur_led_state_tmp; 
			gpio_write(ADV_LED_PORT,cur_led_state_tmp);
		}
	}
	else
	{
		
		send_databuf_tmp();

		if(connected_idle_time_count_tmp==0)
		{
//			blt_retry=1;
		}
	}

	
}
/******************************public area*******************/
  public_loop();	
}

static inline void send_databuf_tmp()
{

#if 1
    /******************test with dongle  used for production**************/
#if 0

	if(blt_test_dongle_conn)
    {
		
		if((flag_has_new_event_tmp)&&( blt_fifo_num()<3))
		{
			flag_has_new_event_tmp=0;
			u8 databuf[2]={0,0};
			databuf[0]=button_value_tmp&0xff;
			databuf[1]=button_value_tmp>>8; 
			blt_push_notify_data(24,databuf,2);
			
		}
		return;
    }
#endif

#if 1	
	if(get_hid_ccc_flag()==0)
	{
		return;
	}
	else 
    {
		if((device_status_tmp==CONNECTED_DEVICE_STATUS)&&( blt_fifo_num()<3))
		{
			device_status_tmp=AFTER_CONNECTED_DEVICE_STATUS;
	#if(TEST_SUSPEND_TIME_ENABLE)

			blt_update_connPara_request(16,32,4,600);
	#else
			 blt_update_connPara_request(8,16,4,600);          
	#endif
		}
    }
#endif

#if(KEYBOARD_REPORT_SUPPORT)

	if((flag_has_new_event_tmp&SEND_K_DATA)&&( blt_fifo_num()<3))
	{
		flag_has_new_event_tmp&=~SEND_K_DATA;
		
		
		blt_push_notify_data(HID_NORMAL_KB_REPORT_INPUT_DP_H,reportKeyIn,8);
	}
#endif

#if(CONSUME_REPORT_SUPPORT)

	if((flag_has_new_event_tmp&SEND_C_DATA)&&( blt_fifo_num()<3))
	{
		flag_has_new_event_tmp&=~SEND_C_DATA;
		
		blt_push_notify_data(HID_CONSUME_KB_REPORT_INPUT_DP_H,reportConsumerControlIn,2);
	}

#endif

#if(MOUSE_REPORT_SUPPORT)
	if((flag_has_new_event_tmp&SEND_M_DATA)&&( blt_fifo_num()<3))
	{
		flag_has_new_event_tmp&=~SEND_M_DATA;
		
		blt_push_notify_data(HID_MOUSE_REPORT_INPUT_DP_H,reportMouseIn,4);	
	}
#endif

#if(JOYSTIC_REPORT_SUPPORT)

	if((flag_has_new_event_tmp&SEND_J_DATA)&&( blt_fifo_num()<3))
	{
		
		flag_has_new_event_tmp&=~SEND_J_DATA;
		
		blt_push_notify_data(HID_JOYSTIC_REPORT_INPUT_DP_H,reportJoyStickIn,9);
	}
#endif

	
	#endif
}


