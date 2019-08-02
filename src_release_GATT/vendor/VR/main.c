
#include "../../proj/tl_common.h"


#include "../../proj/mcu/watchdog_i.h"
#include "../../vendor/common/user_config.h"
#include "../../proj_lib/rf_drv.h"
#include "../../proj_lib/pm.h"

extern void user_init();
extern  void main_loop();

_attribute_ram_code_ void irq_handler(void)
{
#if 0
    u32 src = reg_irq_src;
    if(src & FLD_IRQ_TMR1_EN){
        irq_host_timer1();
        reg_tmr_sta = FLD_TMR_STA_TMR1;
    }
#endif

}

void watch_dog_en()
{
	reg_tmr_ctrl = MASK_VAL(FLD_TMR0_EN, 0, FLD_TMR_WD_CAPT, ((CLOCK_SYS_CLOCK_1S*3) >> WATCHDOG_TIMEOUT_COEFF), FLD_TMR_WD_EN, 1);
}

void clr_watch_dog()
{
	reg_tmr_sta = FLD_TMR_STA_WD;	// watchdog clear
}

int main (void) {
    cpu_wakeup_init();

#if(DEBUG_FROM_FLASH)
	set_freq_offset_flash(0x58);
#else
	set_freq_offset_OTP(0x58);
#endif
    //clock_init
    write_reg8(0x66, 0x26); // 32M pll

    gpio_init();

   // reg_irq_mask = FLD_IRQ_ZB_RT_EN;
//    rf_drv_init(CRYSTAL_TYPE);
#if(DEBUG_FROM_FLASH)
	rf_drv_1M_init_flash();
#else
	rf_drv_1M_init_OTP();
#endif
    

#if(MODULE_ADC_ENABLE)
    	adc_init();
#endif
	user_init ();

	watch_dog_en();
    while (1) {
        main_loop ();
        clr_watch_dog();
    }
}



