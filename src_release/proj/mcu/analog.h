
#pragma once

#include "../common/types.h"
#include "compiler.h"

u8 analog_read(u8 addr);
//_attribute_ram_code_
void analog_write(u8 addr, u8 v);
void analog_read_multi(u8 addr, u8 *v, int len);
void analog_write_multi(u8 addr, u8 *v, int len);
void analog_set_freq_offset(int off);

// the analog version of SET_FLD_V
#define ANALOG_SET_FLD_V(addr, ...)				\
	do{											\
		u8 v = analog_read(addr);		\
		SET_FLD_V(v, __VA_ARGS__);				\
		analog_write(addr, v);			\
	}while(0)

