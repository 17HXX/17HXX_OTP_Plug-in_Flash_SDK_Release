
#pragma once

#include "../../proj/tl_common.h"
#include "../../proj/os/ev.h"
#include "../../proj/os/et.h"

// if pattern changed,  the led will change accordingly within LED_MIN_RESP_TIME in ms
#define LED_MIN_RESP_TIME	50

typedef struct {
	u32 gpio;
	int *pattern_time;
	et_t et;
	int duration;
	u8  pattern;
}led_ctrl_t;

typedef void (*led_count_init_function)(void);
extern led_count_init_function led_count_init_cb;

int led_handler(int led);
void led_set_pattern(int led, int pat);
void led_set_next_pattern(int led);
void led_init(void);


