
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


int main (void) {
    cpu_wakeup_init();

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

    while (1) {
        main_loop ();
    }
}



