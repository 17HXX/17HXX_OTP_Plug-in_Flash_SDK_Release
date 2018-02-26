#pragma once

#include "../common/types.h"
#include "../common/static_assert.h"
#include "../common/bit.h"
#include "../usbstd/CDCClassCommon.h"
#include "../usbstd/CDCClassDevice.h"

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
    extern "C" {
#endif


typedef void ( *cdc_handlerFn_t)( u8* pData);

typedef struct {
    u8 len;
    u8 data[1];
} usbcdc_txBuf_t;


typedef enum usbcdc_sts_e {
    // success = 0
    USB_BUSY = 1,
    USB_MULTIBLOCK,
} usbcdc_sts_t;


void CDC_Device_ProcessControlRequest(u8 bRequest, u16 wValue, u16 wIndex, u16 wLength);

usbcdc_sts_t usbcdc_sendData(u8* buf, u8 len);
u8   usbcdc_sendBulkData(void);

u8   usbcdc_isAvailable(void);
u8*  usbcdc_getData(void);
void usbcdc_init(void);
void usbcdc_setCB(cdc_handlerFn_t rxFunc, cdc_handlerFn_t txCb);
void usbcdc_setRxBuf(u8 *buf);




/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
    }
#endif
