
#pragma once

#include "../common/types.h"

void spi_write(u8 d);
u8 spi_read();

typedef void (*spi_callback_func)(u8 *);


