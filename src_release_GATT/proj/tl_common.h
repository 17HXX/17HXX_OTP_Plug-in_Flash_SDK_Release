
#pragma once


#include "common/types.h"
#include "common/bit.h"
#include "common/utility.h"
#include "common/static_assert.h"
#include "common/assert.h"
#include "mcu/analog.h"
#include "common/compatibility.h"
#include "../vendor/common/user_config.h"
#include "mcu/config.h"
#include "mcu/compiler.h"
#include "mcu/register.h"
#include "mcu/gpio.h"
#include "mcu/pwm.h"

#include "mcu/cpu.h"
#include "mcu/dma.h"
#include "mcu/irq_i.h"
#include "mcu/clock.h"
#include "mcu/clock_i.h"
#include "mcu/random.h"
#include "common/breakpoint.h"
#include "common/log.h"

#ifdef WIN32
#include <stdio.h>
#include <string.h>
#else
#include "common/printf.h"
#include "common/string.h"
#endif

#define DEBUG_STOP()	{reg_tmr_ctrl = 0; reg_gpio_pb_ie = 0xff; while(1);}	// disable watchdog;  DP/DM en
#define DEBUG_SWS_EN()	{reg_tmr_ctrl = 0; reg_gpio_pb_ie = 0xff;}	// disable watchdog;  DP/DM en

