
#include "breakpoint.h"

volatile int bp_enable = 1;
volatile int bp_continue;
volatile int bp_counter;
volatile int bp_pos;

