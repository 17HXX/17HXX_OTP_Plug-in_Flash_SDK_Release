
#pragma once


enum{
	GPIO_DIR_IN 	= 0,
	GPIO_DIR_OUT	= 1
};

// do not use enum,  because we use this in preprocessor diretive,  #if
#define AS_GPIO		0
#define AS_MSPI		1
#define AS_SWIRE	2
#define AS_UART		3
#define AS_PWM		4
#define AS_I2C		5
#define AS_SPI		6
#define AS_ETH_MAC	7
#define AS_I2S		8
#define AS_SDM		9
#define AS_DMIC		10
#define AS_USB		11
#define AS_SWS		12
#define AS_SWM		13
#define AS_TEST		14
#define AS_ADC		15

#include "../common/static_assert.h"

#if(__TL_LIB_8266__ || MCU_CORE_TYPE == MCU_CORE_8266)
#include "../mcu_spec/gpio_default_8266.h"
#include "../mcu_spec/gpio_8266.h"
#elif(__TL_LIB_8267__ || MCU_CORE_TYPE == MCU_CORE_8267)
#include "../mcu_spec/gpio_default_8267.h"
#include "../mcu_spec/gpio_8267.h"
#elif(__TL_LIB_8366__ || MCU_CORE_TYPE == MCU_CORE_8366)
#include "../mcu_spec/gpio_default_8366.h"
#include "../mcu_spec/gpio_8366.h"
#elif(__TL_LIB_17H26__ || MCU_CORE_TYPE == MCU_CORE_17H26)
#include "../mcu_spec/gpio_default_17H26.h"
#include "../mcu_spec/gpio_17H26.h"
#endif

