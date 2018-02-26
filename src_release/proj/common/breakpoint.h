
#pragma once
#include "../tl_common.h"

//  breakpoint simulation
#define MODULE_BREAKPOINT_ENABLE	0

#if(MODULE_BREAKPOINT_ENABLE)
extern volatile int bp_continue;		// 
extern volatile int bp_counter;			// use for breakpoint on counter
extern volatile int bp_pos;				// to indicate where the breakpoint is, may be useful in BP_ON_COND
extern volatile int bp_enable;			// enable breakpoint,  default to 1

#define BP_RST_COUNTER		do{bp_counter = 0;}while(0)

// no idea why gcc optimize off the multline version,  so use the oneline version instead
#if 1
#define BP_ALWAYS(p)		if(bp_enable){bp_pos = p;bp_continue = 0;reg_system_tick_ctrl=FLD_SYSTEM_TICK_STOP;do{}while(bp_enable && 0 == bp_continue);reg_system_tick_ctrl=FLD_SYSTEM_TICK_START;}
#define BP_ON_COUNTER(p,c)	if(bp_enable){bp_pos = p;++bp_counter;reg_system_tick_ctrl=FLD_SYSTEM_TICK_STOP;do{}while(bp_enable && (bp_counter == c));reg_system_tick_ctrl=FLD_SYSTEM_TICK_START;}
#define BP_ON_COND(p,c)		if(bp_enable){bp_pos = p;bp_continue = 0;reg_system_tick_ctrl=FLD_SYSTEM_TICK_STOP;do{}while(bp_enable && (0 == bp_continue) && (c));reg_system_tick_ctrl=FLD_SYSTEM_TICK_START;}
#else
#define BP_ALWAYS(p)		if(bp_enable)										\
							{													\
								bp_pos = p;										\
								bp_continue = 0; 								\
								CLR_FLD(reg_tmr_ctrl,FLD_TMR0_EN); 				\
								do{												\
								}while(bp_enable && 0 == bp_continue);			\
								SET_FLD(reg_tmr_ctrl,FLD_TMR0_EN);				\
							}
#define BP_ON_COUNTER(p,c)	if(bp_enable)										\
							{													\
								bp_pos = p; 									\
								++bp_counter; 									\
								CLR_FLD(reg_tmr_ctrl,FLD_TMR0_EN); 				\
								do{												\
								}while(bp_enable && bp_counter == c);			\
								SET_FLD(reg_tmr_ctrl,FLD_TMR0_EN);				\
							}

#define BP_ON_COND(p,c)		if(bp_enable)										\
							{													\
								bp_pos = p; 									\
								bp_continue = 0; 								\
								CLR_FLD(reg_tmr_ctrl,FLD_TMR0_EN); 				\
								do{												\
								}while(bp_enable && (0 == bp_continue) && (c));	\
								SET_FLD(reg_tmr_ctrl,FLD_TMR0_EN);				\
							}

#endif

#else

#define BP_RST_COUNTER

#define BP_ALWAYS
#define BP_ON_COUNTER(p, c)
#define BP_ON_COND(p, c)

#endif

