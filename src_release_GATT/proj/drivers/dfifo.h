#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#include "../config/user_config.h"

void dfifo_init();
int dfifo0_low();
int dfifo0_high();
int dfifo1_high();
int dfifo2_high();

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif


