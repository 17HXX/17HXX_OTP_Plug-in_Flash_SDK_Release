
#pragma once

#include "../config/user_config.h"
#include "usbkb.h"
#include "../drivers/usbhw.h"
#include "../drivers/usbhw_i.h"
/** HID class report descriptor. This is a special descriptor constructed with values from the
 *  USBIF HID class specification to describe the reports and capabilities of the HID device. This
 *  descriptor is parsed by the host and its contents used to determine what data (and in what encoding)
 *  the device will send, and what it may be sent back from the host. Refer to the HID specification for
 *  more details on HID report descriptors.
 */
static const USB_Descriptor_HIDReport_Datatype_t keyboard_report_desc[] = {
    HID_DESCRIPTOR_KEYBOARD(KEYBOARD_REPORT_KEY_MAX),
};

static inline u8* usbkb_get_report_desc(void) {
	return (u8*) (keyboard_report_desc);
}

static inline u16 usbkb_get_report_desc_size(void) {
	return sizeof(keyboard_report_desc);
}


