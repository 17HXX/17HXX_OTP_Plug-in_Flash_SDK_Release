
#pragma once

#include "../common/types.h"

#define I2C_VENDOR_SEND_WAIT_MODE  1
#define I2C_VENDOR_SEND_DIRECT_MODE 2

void i2c_sim_init(void);
void i2c_sim_write(u8 id, u8 addr, u8 dat);
u8 i2c_sim_read(u8 id, u8 addr);
void i2c_sim_burst_read(u8 id, u8 addr, u8 *p, int n);
void i2c_sim_burst_write(u8 id, u8 addr,u8 *p,int n);

void i2c_init (void);
int i2c_burst_write(u8 id, u16 adr, u8 * buff, int len);
int i2c_burst_read(u8 id, u16 adr, u8 * buff, int len);
void i2c_write(u8 id, u16 adr, u8 dat);
u8 i2c_read(u8 id, u16 adr);

typedef void (*i2c_callback_func)(u8 *);
void i2c_slave_register(int pin, i2c_callback_func callback);
void i2c_send_response(u8*,int);

void i2c_vendor_slave_init(u32 rd_mem_addr, u32 wt_mem_addr);
void i2c_vendor_send_response(u8 *buf, int len);
void i2c_vendor_slave_register(u32 rd_mem_addr, u32 wt_mem_addr, u8 rd_buf_size, u8 wt_buf_size, int pin, i2c_callback_func callback);
void i2c_vendor_slave_deregister(void);
int i2c_vendor_rx_data_timerCb (void* arg);
void  i2c_vendor_reset_write_buf(void);







