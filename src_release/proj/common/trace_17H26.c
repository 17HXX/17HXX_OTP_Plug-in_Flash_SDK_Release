/*
 * 17H26_trace.c
 *
 *  Created on: 2015-7-9
 *      Author: Administrator
 */

#include "../../proj/tl_common.h"

#include "trace_17H26.h"


#define  FIFO_ITEM_SIZE    8
#define  FIFO_NUM 		   16




u8 fifo_addr[FIFO_ITEM_SIZE*FIFO_NUM];
u8 fifo_wptr;


#define SWIRE_CHECK_ENABLE		0


void trace_init(void)
{
	u8 check = ( ((u16)&fifo_addr[0])&0xff)  + (((u16)&fifo_addr[0])>>8) + FIFO_NUM;
	write_reg16(0x8000,(u16)&fifo_addr[0]);
	write_reg8(0x8002,FIFO_NUM);
	write_reg8(0x8003,check);

	write_reg8(0x8004,fifo_wptr);  //
	write_reg8(0x8005,0xff);
}


_attribute_ram_code_ void trace_write(int id, int type, u32 dat)
{
	if(read_reg8(0x800f) != 0x13){
		return;
	}
	u16 adr = fifo_addr + (fifo_wptr*FIFO_ITEM_SIZE);

	write_reg32(adr,dat);
	write_reg8(adr+3,type| id);
	write_reg8(adr+4,read_reg8(adr) ^ read_reg8(adr+1) ^ read_reg8(adr+2) ^ read_reg8(adr+3));

	write_reg8(0x8004,fifo_wptr);
	write_reg8(0x8005,~fifo_wptr);

	fifo_wptr = (fifo_wptr+1)&(FIFO_NUM - 1);
}




_attribute_ram_code_ void trace_task_begin(int id){
	trace_write(id,LOG_MASK_BEGIN,clock_time());
}


_attribute_ram_code_ void trace_task_end(int id){
	trace_write(id,LOG_MASK_END,clock_time());
}


_attribute_ram_code_ void trace_event(int id){
	trace_write(id,LOG_MASK_TGL,clock_time());
}


_attribute_ram_code_ void trace_data(int id, u32 dat){
	trace_write(id,LOG_MASK_DAT,dat);
}
