#include "../../proj/tl_common.h"
#include "e2prom.h"

#define						EEPROM_I2C_ID				0xa0
#define						EEPROM_SIZE					256
void e2prom_init(){
	//i2c_sim_reset_e2prom();
	u8 eraseByte[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	for(u8 i=0;i<=EEPROM_SIZE/8;i++)
		e2prom_write(i*8,eraseByte,8);
}
void e2prom_write (int adr, u8 *p, int len)
{
	int i = 0;
	while (len > 0)
	{
		int l = len >= 8 ? 8 : len;				//page write: 8-byte
		len -= l;
		i2c_sim_burst_write (EEPROM_I2C_ID, adr + i, p + i, l);
		i += l;
		sleep_us (5000);
	}
}
void e2prom_read (int adr, u8 *p, int len)
{
	i2c_sim_burst_read (EEPROM_I2C_ID, adr, p, len);
}
