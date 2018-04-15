#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
    extern "C" {
#endif

void uartOpen(u32 baudrate);
void uartClose();
void uartWrite(u8 *addr);
int uartIsIdle();

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
    }
#endif


