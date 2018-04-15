
#pragma once

#include "../common/types.h"
#include "register.h"
#include "clock_i.h"

static inline u16 rand(void){
	return (u16)((clock_time() & 0xffff) ^ reg_rnd_number);
}

