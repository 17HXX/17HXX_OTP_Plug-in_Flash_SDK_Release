#pragma once

#include "../common/types.h"
#include "../common/static_assert.h"
#include "../usbstd/HIDReportData.h"
#include "../usbstd/HIDClassCommon.h"
#include "../mcu/clock_i.h"

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#define KEYBOARD_REPORT_KEY_MAX     6
typedef struct {
    u8 Modifier; /**< Keyboard modifier byte, indicating pressed modifier keys (a combination of
                       *   \c HID_KEYBOARD_MODIFER_* masks).
                       */
    u8 Reserved; /**< Reserved for OEM use, always set to 0. */
    u8 KeyCode[KEYBOARD_REPORT_KEY_MAX]; /**< Key codes of the currently pressed keys. */
} usbkb_hid_report_t;

int usbkb_hid_report_normal(u8 ctrl_key, u8 *keycode);


/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

