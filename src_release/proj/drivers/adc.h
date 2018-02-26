/*
 * adc.h
 *
 *  Created on: 2015-12-10
 *      Author: 
 */

#ifndef ADC_H_
#define ADC_H_

#if(__TL_LIB_8266__ || MCU_CORE_TYPE == MCU_CORE_8266)
#include "../mcu_spec/adc_8266.h"
#elif(__TL_LIB_8267__ || MCU_CORE_TYPE == MCU_CORE_8267)
#include "../mcu_spec/adc_8267.h"
#elif(__TL_LIB_17H26__ || MCU_CORE_TYPE == MCU_CORE_17H26)
#include "../mcu_spec/adc_17H26.h"
#endif



#endif /* ADC_H_ */
