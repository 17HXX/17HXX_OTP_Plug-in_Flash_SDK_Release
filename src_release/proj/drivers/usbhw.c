
#include "usbhw.h"
#include "../mcu/irq_i.h"
#include "../common/bit.h"
#include "../common/assert.h"
#include "../common/utility.h"
#include "usbhw_i.h"

// Endpont8 is the alias of endpoint0
void usbhw_disable_manual_interrupt(int m) {
	SET_FLD(reg_ctrl_ep_irq_mode, m);
}

void usbhw_enable_manual_interrupt(int m) {
	CLR_FLD(reg_ctrl_ep_irq_mode, m);
}

void usbhw_write_ep(u32 ep, u8 * data, int len) {
	assert(ep < 8);
	reg_usb_ep_ptr(ep) = 0;

	foreach(i,len){
		reg_usb_ep_dat(ep) = data[i];
	}
	reg_usb_ep_ctrl(ep) = FLD_EP_DAT_ACK;		// ACK
}

// handy help function
void usbhw_write_ctrl_ep_u16(u16 v){
	usbhw_write_ctrl_ep_data(v & 0xff);
	usbhw_write_ctrl_ep_data(v >> 8);
}

u16 usbhw_read_ctrl_ep_u16(void){
	u16 v = usbhw_read_ctrl_ep_data();
	return (usbhw_read_ctrl_ep_data() << 8) | v;
} 

