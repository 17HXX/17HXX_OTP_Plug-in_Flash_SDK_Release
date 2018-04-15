#pragma once

#include "../app/usbcdc.h"
#include "uart.h"
#define DFLT_BAUD_RATE  9600



void usb_uart_open(u32 baudrate, uart_recvCb_t cb);
usbcdc_sts_t usb_uart_write(u8* buf, u8 len);
