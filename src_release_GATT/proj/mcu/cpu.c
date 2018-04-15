
#include "../tl_common.h"

void cpu_reboot(void){
	reg_pwdn_ctrl = FLD_PWDN_CTRL_REBOOT;
	volatile int i;
	for(i = 0; i < 32; ++i){}
}

