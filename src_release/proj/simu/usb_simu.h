
#pragma once

extern u8 usb_sim_ctrl_ep_buffer[128];
extern u8 usb_sim_eps_buffer[8][128];
extern u8 usb_sim_ctrl_ep_ptr;
extern u8 usb_sim_eps_ptr[8];
extern void usb_simu_init(void);

