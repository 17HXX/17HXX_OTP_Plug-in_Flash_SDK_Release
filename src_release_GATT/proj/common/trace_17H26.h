/*
 * 17H26_trace.h
 *
 *  Created on: 2015-7-9
 *      Author: Administrator
 */

#ifndef TRACE_H_
#define TRACE_H_


#define		LOG_MASK_BEGIN		0x40
#define		LOG_MASK_END		0x00
#define		LOG_MASK_TGL		0xC0
#define		LOG_MASK_DAT		0x80


extern void trace_init(void);
extern void trace_log(u8 type_id,u32 data);


#endif /* 17H26_TRACE_H_ */
