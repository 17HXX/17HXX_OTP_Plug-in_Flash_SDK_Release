#pragma once

#include "../common/types.h"
#include "../common/static_assert.h"
#include "../common/bit.h"
#include "../usbstd/HIDReportData.h"
#include "../usbstd/HIDClassCommon.h"

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
	extern "C" {
#endif


#define MOUSE_REPORT_DATA_LEN     (sizeof(mouse_data_t))
#define MEDIA_REPORT_DATA_LEN		4
int usbmouse_hid_report(u8 report_id, u8 *data, int cnt);


/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
	}
#endif
