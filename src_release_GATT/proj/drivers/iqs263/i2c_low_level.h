/*******************************************************************************
 *
 *		Azoteq IQS263_Example_Code
 *
 *              i2c_low_level.h
 *
*******************************************************************************/

#ifndef I2C_LOW_LEVEL_H
#define	I2C_LOW_LEVEL_H

#ifndef PIN_I2C_SCL
#define PIN_I2C_SCL				0
#endif

#ifndef PIN_I2C_SDA
#define PIN_I2C_SDA				0
#endif

#ifndef PIN_I2C_RDY
#define PIN_I2C_RDY				0
#endif


#define SCL_INPUT	   gpio_set_output_en(PIN_I2C_SCL,0)
#define SCL_HIGH       gpio_set_output_en(PIN_I2C_SCL,0)
#define SCL_LOW        gpio_set_output_en(PIN_I2C_SCL,1)

#define SDA_INPUT	   gpio_set_output_en(PIN_I2C_SDA,0)
#define SDA_HIGH	   gpio_set_output_en(PIN_I2C_SDA,0)
#define SDA_LOW        gpio_set_output_en(PIN_I2C_SDA,1)

#define RDY_IN		   gpio_read(PIN_I2C_RDY)

unsigned char Comms_IsRdy(void);
unsigned char CommsIQS_send(unsigned char send_data);
unsigned char CommsIQS_read_ack(void);
unsigned char CommsIQS_read_nack(void);
void CommsIQS_start(void);
void CommsIQS_repeat_start(void);
void CommsIQS_stop(void);
unsigned char Comms_send(unsigned char send_data);

#endif	/* I2C_LOW_LEVEL_H */

