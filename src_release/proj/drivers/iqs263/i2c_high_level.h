/*******************************************************************************
 *
 *		Azoteq IQS263_Example_Code
 *
 *              i2c_high_level.h
 *
*******************************************************************************/

#ifndef I2C_HIGH_LEVEL_H
#define	I2C_HIGH_LEVEL_H

void CommsIQS_Read(unsigned char i2c_addr, unsigned char read_addr, unsigned char *data, unsigned char NoOfBytes);
void CommsIQS_Write(unsigned char i2c_addr, unsigned char write_addr, unsigned char *data, unsigned char NoOfBytes);

#endif	/* I2C_HIGH_LEVEL_H */

