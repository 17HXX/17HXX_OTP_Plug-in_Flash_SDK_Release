
#pragma once

#include "../common/types.h"

void otp_init(void);
void otp_write(u16 addr, u8 value);
void otp_stop_write(void);
u8 otp_read(u16 addr);

