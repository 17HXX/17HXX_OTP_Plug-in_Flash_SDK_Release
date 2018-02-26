
#pragma once

#include "../common/bit.h"

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

/*Write 0x53 to enable writing to 0x7f,0x7e,0x7d and 0x7c*/
#define ID_WRITE_ENABLE_MAGIC   0x53

void id_set_product_id(u8 function_id, u8 version_id, u16 production_id);

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

