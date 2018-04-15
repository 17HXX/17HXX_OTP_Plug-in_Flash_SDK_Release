
#include "../tl_common.h"
#include "../drivers/spi.h"
#include "flash.h"
#include "spi_i.h"

// !!!!  In the case of being used, disable the following can save some RAM
#define FLASH_WRITE_ENABLE		1
#define FLASH_READ_ENABLE		1
// !!!!

#if(OTA_ENABLE)
_attribute_ram_code_ static inline int flash_is_busy(){
	return mspi_read() & 0x01;				//  the busy bit, pls check flash spec
}

_attribute_ram_code_ static void flash_send_cmd(u8 cmd){
	mspi_high();
	sleep_us(1);
	mspi_low();
	mspi_write(cmd);
	mspi_wait();
}

_attribute_ram_code_ static void flash_wait_done(){
	flash_send_cmd(FLASH_READ_STATUS_CMD);
	while(flash_is_busy());
	mspi_high();
}

_attribute_ram_code_ void flash_erase_read_write (u32 addr, u32 len, u8 *buf, u8 cmd){
	if(FLASH_READ_CMD != cmd){ 
		flash_send_cmd(FLASH_WRITE_ENABLE_CMD);
	}
	flash_send_cmd(cmd);

	//--   send address ---
	mspi_write((u8)(addr>>16));
	mspi_wait();
	mspi_write((u8)(addr>>8));
	mspi_wait();
	mspi_write((u8)(addr));
	mspi_wait();

	if(FLASH_WRITE_ENABLE && (FLASH_WRITE_CMD == cmd)){
		for(int i = 0; i < len; ++i){
			mspi_write(buf[i]);		/* write data */
			mspi_wait();
		}
	}else if(FLASH_READ_ENABLE && (FLASH_READ_CMD == cmd)){
		mspi_write(0x00);		/* dummy,  to issue clock */
		mspi_wait();
		mspi_ctrl_write(0x0a);	/* auto mode */
		mspi_wait();
		/* get data */
		for(int i = 0; i < len; ++i){
			*buf++ = mspi_get();
			mspi_wait();
		}
	}
	mspi_high();
	flash_wait_done();
	
}


void flash_erase_sector(u32 addr){
	u8 r = irq_disable();
	flash_erase_read_write(addr, 0, 0, FLASH_SECT_ERASE_CMD);
	irq_restore(r);
}

_attribute_ram_code_ void flash_erase_block(u32 addr){
	u8 r = irq_disable();
	flash_erase_read_write(addr, 0, 0, FLASH_BLK_ERASE_CMD);
	irq_restore(r);
}
#if(FLASH_WRITE_ENABLE)
_attribute_ram_code_ void flash_write_page(u32 addr, u32 len, u8 *buf){
	u8 r = irq_disable();
	flash_erase_read_write(addr, len, buf, FLASH_WRITE_CMD);
	irq_restore(r);
}
#endif

#if(FLASH_READ_ENABLE)
_attribute_ram_code_ void flash_read_page(u32 addr, u32 len, u8 *buf){
	u8 r = irq_disable();
	flash_erase_read_write(addr, len, buf, FLASH_READ_CMD);
	irq_restore(r);
}
#endif

#if 0
_attribute_ram_code_ u32 flash_get_jedec_id(){
	u8 r = irq_disable();
	flash_send_cmd(FLASH_GET_JEDEC_ID);
	u8 manufacturer = mspi_read();
	u8 mem_type = mspi_read();
	u8 cap_id = mspi_read();
	mspi_high();
	irq_restore(r);
	return (u32)((manufacturer << 24 | mem_type << 16 | cap_id));
}
#endif
#endif


