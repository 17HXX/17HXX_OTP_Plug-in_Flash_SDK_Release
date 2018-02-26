
#include "../mcu/register.h"
#include "../common/assert.h"
#include "id.h"

static void id_set_magic_enable(){
	reg_id_wr_en = ID_WRITE_ENABLE_MAGIC;
}

void id_set_product_id(u8 function_id, u8 version_id, u16 production_id){
	id_set_magic_enable();
	reg_product_id = (production_id << 16 | version_id << 8 | function_id);
}

