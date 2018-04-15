
#include "register.h"

//  watchdog use timer 2
//STATIC_ASSERT((WATCHDOG_INIT_TIMEOUT * CLOCK_SYS_CLOCK_1MS >> WATCHDOG_TIMEOUT_COEFF) > 0);
static inline void wd_set_interval(int ms)	//  in ms
{
	SET_FLD_V(reg_tmr_ctrl, FLD_TMR_WD_CAPT, (ms * CLOCK_SYS_CLOCK_1MS >> WATCHDOG_TIMEOUT_COEFF), FLD_TMR2_MODE, 0);
	reg_tmr2_tick = 0;
}

static inline void wd_start(void){
#if(MODULE_WATCHDOG_ENABLE)		//  if watchdog not set,  start wd would cause problem
	SET_FLD(reg_tmr_ctrl, FLD_TMR_WD_EN);
#endif
}

static inline void wd_stop(void){
#if(MODULE_WATCHDOG_ENABLE)	
	CLR_FLD(reg_tmr_ctrl, FLD_TMR_WD_EN);
#endif
}

static inline void wd_clear(void){
	reg_tmr_sta = FLD_TMR_STA_WD;
}

