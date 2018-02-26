

#include "../tl_common.h"
#include "../os/ev.h"
#include "../drivers/usbkeycode.h"
#include "../drivers/keyboard.h"
#include "../../vendor/common/keycode_custom.h"

u8 kb_simu_is_func_key;
u32 kb_simu_pressed_matrix[8];    // normally max 8 key rows
kb_data_t kb_simu_key_data;

int kb_simu_timer(void *data){
    static int key_cnt = 0;
    static u8 key_code = VK_1;
    
    kb_simu_key_data.cnt = 1;
    kb_simu_key_data.ctrl_key = 0;
    kb_simu_key_data.keycode[0] = key_code;
    ++key_code; 
    if(VK_0 < key_code){
        key_code = VK_1;
        kb_simu_key_data.cnt = 0;
        return (1000*1000);
    }
    return KEYBOARD_SCAN_INTERVAL;
}

void kb_simu_init(void){
    static ev_time_event_t kb_timer = {kb_simu_timer};
    ev_on_timer(&kb_timer, KEYBOARD_SCAN_INTERVAL);
}


