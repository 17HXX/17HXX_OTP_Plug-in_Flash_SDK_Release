/*********************************************************************************************************************

        Azoteq IQS263_Example_Code

                i2c_high_level.c - i2c high level functions

********************************************************************************************************************/
#include "../../tl_common.h"
#include "../../../proj_lib/rf_drv.h"
#include "../../../proj_lib/pm.h"
#include "../../../proj/mcu/clock.h"
#include "../../../proj/mcu/clock_i.h"

#include "i2c_high_level.h"
#include "i2c_low_level.h"
#include "iqs263_init.h"
#include "IQS263.h"

void CommsIQS_Read(unsigned char i2c_addr, unsigned char read_addr, unsigned char *data, unsigned char NoOfBytes)
{
    unsigned char i;

    CommsIQS_send((i2c_addr << 1) + 0x00);      // device address + write
    CommsIQS_send(read_addr);                   // IQS address-command
    CommsIQS_repeat_start();
    CommsIQS_send((i2c_addr << 1) + 0x01);      // device address + read
    if (NoOfBytes > 1)
    {
        for (i = 0; i < NoOfBytes - 1; i++)
            data[i] = CommsIQS_read_ack();      // all bytes except las must be followed by ACK
    }
    data[NoOfBytes-1] = CommsIQS_read_nack();   // last byte read must be followed by a NACK
}

void CommsIQS_Write(unsigned char i2c_addr, unsigned char write_addr, unsigned char *data, unsigned char NoOfBytes)
{
    unsigned char i;

    CommsIQS_send((i2c_addr << 1) + 0x00);      // device address + write
    CommsIQS_send(write_addr);                  // IQS address-command
    for (i = 0; i < NoOfBytes; i++)
        CommsIQS_send(data[i]);
}


