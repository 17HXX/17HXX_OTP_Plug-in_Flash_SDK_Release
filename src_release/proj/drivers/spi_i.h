
#include "../config/user_config.h"
#include "../mcu/gpio.h"
#include "../mcu/register.h"

// use static inline, because, spi flash code must reside in memory..
// these code may be embedd in flash code
static _attribute_forceinline_ void mspi_wait(void){
	while(reg_master_spi_ctrl & FLD_MASTER_SPI_BUSY)
		;
}

static _attribute_forceinline_ void mspi_high(void){
	reg_master_spi_ctrl = FLD_MASTER_SPI_CS;
}

static _attribute_forceinline_ void mspi_low(void){
	reg_master_spi_ctrl = 0;
}

static _attribute_forceinline_ u8 mspi_get(void){
	return reg_master_spi_data;
}

static _attribute_forceinline_ void mspi_write(u8 c){
	reg_master_spi_data = c;
}

static _attribute_forceinline_ void mspi_ctrl_write(u8 c){
	reg_master_spi_ctrl = c;
}

static _attribute_forceinline_ u8 mspi_read(void){
	mspi_write(0);		// dummy, issue clock 
	mspi_wait();
	return mspi_get();
}

