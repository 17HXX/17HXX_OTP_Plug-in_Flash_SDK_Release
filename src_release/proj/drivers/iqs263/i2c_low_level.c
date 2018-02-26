/*********************************************************************************************************************

		Azoteq IQS263_Example_Code

                i2c_low_level.c - i2c low level functions

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


void i2c_delay_us(unsigned int lp)
{
	for(int i=0;i<lp;i++)
	{
		CLOCK_DLY_8_CYC;
	}
}

#define IIC_SHORT_DELAY		i2c_delay_us(10)  //10
#define IIC_MIDDLE_DELAY	i2c_delay_us(20)  //20
#define IIC_LONG_DELAY		i2c_delay_us(40)  //30


void iqs263_i2c_init()
{
	gpio_set_func(PIN_I2C_SCL,AS_GPIO);
	gpio_set_func(PIN_I2C_SDA,AS_GPIO);
}



unsigned char Comms_IsRdy(void)
{
    if (RDY_IN) {
        return 0;
    }
    else {
        return 1;
    }
}

static void  i2c_start(void)
{
	SDA_HIGH;
	IIC_SHORT_DELAY;
	SCL_HIGH;
	IIC_MIDDLE_DELAY;
	SDA_LOW;
	IIC_MIDDLE_DELAY;
	SCL_LOW;
}

static void  i2c_stop(void)
{
	SDA_LOW;
	IIC_SHORT_DELAY;
	SCL_HIGH;
	IIC_MIDDLE_DELAY;
	SDA_HIGH;
	//IIC_SHORT_DELAY;
}

/***************************************************************************************************
						----    CommsIQS_send()    ----
	Description:	Transmits the data byte given as parameter via the I2C of the PIC18F4550
				Note that the I2C communication channel must already be active before calling this function,
				as no start bits are included in this function

	Parameters:		send_data - data byte to be transmitted via the I2C
****************************************************************************************************/
unsigned char CommsIQS_send(unsigned char dat)
{
	SCL_LOW;
	u8 temp = 0x80;
	while(temp)
	{
			if(dat & temp)
			{
				SDA_HIGH;
			}
			else
			{
				SDA_LOW;
			}

			IIC_SHORT_DELAY;
			SCL_HIGH;
			IIC_LONG_DELAY;
			SCL_LOW;
			temp>>= 1;
	}

	SDA_INPUT;    //slave  ACK, SDA input, release data line
	i2c_delay_us(40);
	SCL_HIGH;

	//LED_O_ON;
	IIC_MIDDLE_DELAY;
	//LED_O_OFF;

	SCL_LOW;
	i2c_delay_us(10);
}

/*  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						----    CommsIQS_read_ack()    ----
	Description:	Enables the Master Receive Mode of the I2C module on the PIC18F4550. The data received is
				returned and an (ACK) acknowledge is sent to the IQS to indicate that more byte read's will
				still take place.

	Return:		The data received via the I2C
*/
unsigned char CommsIQS_read_ack(void)
{
	SDA_INPUT;

	u8 dat = 0;
	SCL_LOW;
	foreach(i, 8)
	{
		IIC_SHORT_DELAY;
		SCL_HIGH;
		IIC_LONG_DELAY;
		if(gpio_read(PIN_I2C_SDA))
		{
			dat = (dat << 1) | 0x01;
		}
		else
		{
			dat = dat << 1;
		}
		SCL_LOW;
	}

	SDA_LOW;  //ack

	IIC_SHORT_DELAY;
	SCL_HIGH;
	IIC_LONG_DELAY;
	SCL_LOW;

	return dat;
}

/*  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						----    CommsIQS_read_nack()    ----
	Description:	Enables the Master Receive Mode of the I2C module on the PIC18F4550. The data received is
				returned and a NACK acknowledge is sent to the IQS to indicate that this was the final read
				of the current continuous read block.

	Return:		The data received via the I2C
*/
unsigned char CommsIQS_read_nack(void)
{
	SDA_INPUT;

	u8 dat = 0;
	SCL_LOW;
	foreach(i, 8)
	{
		IIC_SHORT_DELAY;
		SCL_HIGH;
		IIC_LONG_DELAY;
		if(gpio_read(PIN_I2C_SDA))
		{
			dat = (dat << 1) | 0x01;
		}
		else
		{
			dat = dat << 1;
		}
		SCL_LOW;
	}

	SDA_HIGH;  //nack

	IIC_SHORT_DELAY;
	SCL_HIGH;
	IIC_LONG_DELAY;
	SCL_LOW;

	return dat;
}

/*  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						----    CommsIQS_start()    ----
				A i2c START condition is generated
*/
void CommsIQS_start(void)
{
    // IQ263 starts in full streaming mode
    while (RDY_IN != 0)       //wait for IQS device to become ready
    {}

    i2c_start();
}

/*  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						----    CommsIQS_repeat_start()    ----
	Description:	An i2c START condition is generated.
*/
void CommsIQS_repeat_start(void)
{
    i2c_start();
}

/*  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						----    CommsIQS_stop()    ----
	Description:	An i2c STOP condition is generated.
*/
void CommsIQS_stop(void)
{
    i2c_stop();

    //wait for the IQS device to become ready
    while (RDY_IN != 0)       //wait for IQS device to become ready
    {}
    while (RDY_IN == 0)       //wait for IQS device to become ready
    {}
    //wait for IQS device to become ready
}


