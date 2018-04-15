#pragma once

#include "../common/types.h"
#include "../common/static_assert.h"
#include "../common/bit.h"
#include "uart.h"
//#include "../usbstd/CDCClassCommon.h"
//#include "../usbstd/CDCClassDevice.h"

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
    extern "C" {
#endif

typedef struct {
	u8 *rxBuf;
	u8 *txBuf;

	/* Following variables are used in the RX more than DMA_MAX_SIZE */
	u16 lenToSend;
	u16 lastSendIndex;
	
} DmaUart_ctrl_t;

uart_sts_t DmaUart_sendData(u8* buf, u32 len);
uart_sts_t DmaUart_sendBulkData(void);
u8   DmaUart_isAvailable(void);

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
    }
#endif

