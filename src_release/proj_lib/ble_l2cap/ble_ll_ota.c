/*
 * ble_ll_ota.c
 *
 *  Created on: 2015-7-20
 *      Author: Administrator
 */

//   OTA ///////////////////////////////////////

#include "../../proj/tl_common.h"
#include "../../proj_lib/ble_l2cap/blueLight.h"
#include "../../proj_lib/pm_17H26.h"
#include "../../proj/drivers/flash.h"
#include "ble_ll_ota.h"
u8 start_ota_flag=0;

#if(OTA_ENABLE)

STATIC_ASSERT(OTA_FLASH_ADDR_START >= FLASH_BLOCK_SECTOR_SIZE);
static u16 otaPktIndex;
_attribute_ram_code_ _attribute_no_inline_ int otaDone(){
	u8 data[16];
	flash_erase_block(0);
	for(int index = 0; index <= otaPktIndex; ++index){
		u32 flash_addr = index << 4;
		flash_read_page(OTA_FLASH_ADDR_START + flash_addr, 16, data);
		flash_write_page(flash_addr, 16, data);
//		flash_read_page(OTA_FLASH_ADDR_START + flash_addr, 16, data);
//		flash_write_page(flash_addr, 16, data);
//		u8 flash_check[16];
//		flash_read_page(flash_addr, 16, flash_check);
//		if(memcmp(data, flash_check, 16)){ 	// !!!!  memcmp must reside in RAM
//			return -1;
//		}
	}
	
#if(!WATCHDOG_ENABLE)
		reg_pwdn_ctrl = FLD_PWDN_CTRL_REBOOT;
	#endif
		while(1);
	
}

extern u8 ota_data[20];
extern void blt_disable_latency();


int otaWrite(rf_packet_att_write_t * p){
	u8 *data = &p->value;
	u16 index = data[0] | (data[1] << 8);
	if(CMD_OTA_START == index){
		start_ota_flag=1;
		blt_disable_latency();	// should not use latency
	}else if(CMD_OTA_END == index){
		otaDone();
	}else if(start_ota_flag==1){
		memcpy(ota_data, data, 20);
		blt_disable_latency();	// should not use latency
		u8 flash_check[16];
		u32 flash_addr = OTA_FLASH_ADDR_START + (index << 4);
		flash_write_page(flash_addr, 16, &data[2]);
		flash_read_page(flash_addr, 16, flash_check);
		if(memcmp(&data[2], flash_check, 16)){		//  write fail
			return -1;
		}
		otaPktIndex = index;
	}
	return 0;
}
#endif

