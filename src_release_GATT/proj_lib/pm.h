
#pragma once

#if(__TL_LIB_8266__ || MCU_CORE_TYPE == MCU_CORE_8266)
#include "pm_8266.h"
#elif(__TL_LIB_8267__ || MCU_CORE_TYPE == MCU_CORE_8267)
#include "pm_8267.h"
#elif(__TL_LIB_8366__ || MCU_CORE_TYPE == MCU_CORE_8366)
#include "pm_8366.h"
#elif(__TL_LIB_17H26__ || MCU_CORE_TYPE == MCU_CORE_17H26)
#include "pm_17H26.h"
#endif

