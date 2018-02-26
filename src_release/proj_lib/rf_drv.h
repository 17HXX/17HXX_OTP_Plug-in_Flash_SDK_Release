
#pragma once

#if(__TL_LIB_8266__ || MCU_CORE_TYPE == MCU_CORE_8266)
#include "rf_drv_8266.h"
#elif(__TL_LIB_8267__ || MCU_CORE_TYPE == MCU_CORE_8267)
#include "rf_drv_8267.h"
#elif(__TL_LIB_17H26__ || MCU_CORE_TYPE == MCU_CORE_17H26)
#include "rf_drv_17H26.h"
#endif

