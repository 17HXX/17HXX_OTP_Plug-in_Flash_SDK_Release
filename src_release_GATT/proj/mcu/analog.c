
#include "compiler.h"
#include "../common/bit.h"
#include "../common/utility.h"
#include "analog.h"
#include "irq_i.h"
#include "register.h"

#ifdef WIN32
extern u8 rega_simu_buffer[];
#endif

#if (MCU_CORE_TYPE != MCU_CORE_3520)

static inline void analog_wait(){
	while(reg_ana_ctrl & FLD_ANA_BUSY){}
}

_attribute_ram_code_ _attribute_no_inline_ u8 analog_read(u8 addr){
#if(ANALOG_OP_DISABLE_IRQ)
	u8 r = irq_disable();
#endif

	reg_ana_addr = addr;
	reg_ana_ctrl = (FLD_ANA_START);
//   Can't use one line setting "reg_ana_ctrl32 = ((FLD_ANA_START | FLD_ANA_RSV) << 16) | addr;"
//   This will fail because of time sequence and more over size is bigger
	analog_wait();
#ifndef WIN32
	u8 data = reg_ana_data;
#else
	u8 data = rega_simu_buffer[addr];
#endif	
	reg_ana_ctrl = 0;		// finish

#if(ANALOG_OP_DISABLE_IRQ)
	irq_restore(r);
#endif

	return data;
}

_attribute_ram_code_ _attribute_no_inline_ void analog_write(u8 addr, u8 v){
#if(ANALOG_OP_DISABLE_IRQ)
	u8 r = irq_disable();
#endif

	reg_ana_addr = addr;
	reg_ana_data = v;
	reg_ana_ctrl = (FLD_ANA_START | FLD_ANA_RW);
//	 Can't use one line setting "reg_ana_ctrl32 = ((FLD_ANA_START | FLD_ANA_RW) << 16) | (v << 8) | addr;"
//   This will fail because of time sequence and more over size is bigger
	analog_wait();
	reg_ana_ctrl = 0; 		// finish
#ifdef WIN32
	rega_simu_buffer[addr] = v;
#endif
	
#if(ANALOG_OP_DISABLE_IRQ)
	irq_restore(r);
#endif
}

/*No use for 17H26_remote*/
void analog_read_multi(u8 addr, u8 *v, int len){
#if(ANALOG_OP_DISABLE_IRQ)
	u8 r = irq_disable();
#endif

	reg_ana_ctrl = 0;		// issue clock
	reg_ana_addr = addr;
	while(len--){
		reg_ana_ctrl = FLD_ANA_CYC | FLD_ANA_START;
		analog_wait();
#ifndef WIN32
		*v++ = reg_ana_data;
#else
		*v++ = rega_simu_buffer[addr++];
#endif
	}
	reg_ana_ctrl = 0; 		// finish

#if(ANALOG_OP_DISABLE_IRQ)
	irq_restore(r);
#endif
}

/*No use for 17H26 remote*/
void analog_write_multi(u8 addr, u8 *v, int len){
#if(ANALOG_OP_DISABLE_IRQ)
	u8 r = irq_disable();
#endif

	reg_ana_addr = addr;
	while(len--){
		reg_ana_data = *v++;
#ifdef WIN32
		rega_simu_buffer[addr++] = *v++;
#endif
		reg_ana_ctrl = FLD_ANA_CYC | FLD_ANA_START | FLD_ANA_RW; 	// multi write
		analog_wait();
	}
	reg_ana_ctrl = 0; 		// finish
#if(ANALOG_OP_DISABLE_IRQ)
	irq_restore(r);
#endif
}

#endif
