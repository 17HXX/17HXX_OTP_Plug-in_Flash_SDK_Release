/*
 * ble_ll_ota.h
 *
 *  Created on: 2015-7-20
 *      Author: Administrator
 */

#ifndef BLE_LL_OTA_H_
#define BLE_LL_OTA_H_

#define CMD_OTA_VERSION			0xff00
#define CMD_OTA_START			0xff01
#define CMD_OTA_END				0xff02
#define OTA_FLASH_ADDR_START	0x20000
#define FLASH_BLOCK_SECTOR_SIZE	0x10000	// !!!! 要按实际的spec 写
int otaWrite(rf_packet_att_write_t * p);


#endif /* BLE_LL_OTA_H_ */
