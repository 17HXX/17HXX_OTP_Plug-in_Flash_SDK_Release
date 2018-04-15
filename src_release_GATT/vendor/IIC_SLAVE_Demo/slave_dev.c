
#include "ui.h"
#include "../../proj/tl_common.h"
#include "../../proj_lib/blt_ll/blt_ll.h"
#include "../../proj/mcu_spec/gpio_17H26.h"
#include "./app_config.h"
#include "slave_dev.h"

__attribute__ ((aligned (128))) u8 host_rb[128] = {0};
u8 temp_buff_send_app[20] = {0};
u8 temp_buff_from_app[20] = {0};
u8 all_zero[23] = {0};
u8 run_where = 0;
u8 app_send_flag = 0;
u8 length_read = 0;
u8 data_length = 0;
u8 can_Deal = 0;
u8 put_len = 0;
u8 read_ask = 0;
u8 after_master_write = 0;
u8 can_suspend_flag = 0;
u8 ask_mode_flag = 0;
u8 from_app_step = 0;
u8 allow_read = 0;

void slave_dev_init(void)
{
	//从机  I2C初始化
	REG_ADDR16(0x3e) = (u16)(u32)host_rb;		//the space use to save the IIC write or read
	gpio_set_func (GPIO_GP22, !AS_GPIO);		//SCL
	gpio_set_func (GPIO_GP23, !AS_GPIO);		//SDA
	gpio_set_func(GPIO_GP5, AS_GPIO);			// GP22 GP23 as IIC, GP5 must as GPIO
	//write_reg8 (0x01, 0x5C);
	write_reg8(0x596,read_reg8(0x596) & 0x7f);		//GP23 NO as GPIO
	write_reg8(0x591,read_reg8(0x591) | 0xc0);		//must! GP23 input enable
	//write_reg8(0x593,read_reg8(0x593) & 0x80);
	analog_write (0x09, 0x28);					//	10K pull-up(上拉) 	gp22 gp23
	REG_ADDR8(0x03) |= BIT(2);					//	enable host address
	REG_ADDR8(0x22) = BIT(2);					//write 1 clear host_pkt_irq, read host_pkt_irq status
	//REG_ADDR8(0x20) = BIT(7);

	/*******************PAD or Suspend wakeup set****************/
	blt_set_wakeup_source(PM_WAKEUP_CORE);
	write_reg8(0x594,0x00);				//高电平有效
	write_reg8(0x597,0x04);
	analog_write (0x16, 0x02);			//PAD_wakeup_enabel ---> p_gpio[18] set enable
	analog_write (0x14, analog_read (0x14) & 0xef );// set polarity	 	P18 | 0x10   & 0xef
	can_suspend_flag = 1;
	//从机信号脚初始化
	gpio_set_func(GPIO_GP18, AS_GPIO);			//GP18 is signal pin
	gpio_set_output_en(GPIO_GP18,0);
	gpio_set_input_en(GPIO_GP18,1);

	gpio_set_func(GPIO_GP7, AS_GPIO);		//work led (工作指示灯)
	gpio_set_output_en(GPIO_GP7,1);
	gpio_set_input_en(GPIO_GP7,0);
	analog_write (0x08,analog_read(0x08) | 0x0c);

}


void deal_rev_data_from_app(void)
{
	run_where = 4;
	static u8 check_time = 0;
	static u32 sec_time_tick = 0;
	if(ask_mode_flag == 1 && app_send_flag == 1)
	{
		run_where = 5;
		if(from_app_step == 0)
		{
			run_where = 6;
			from_app_step = 1;
//			gpio_write(GPIO_GP10,1);
			memset(host_rb+64, 0x00, 23);
			host_rb[64] = 0xff;
			memcpy (host_rb+65, temp_buff_from_app, length_read -3);
			memcpy (temp_buff_send_app, temp_buff_from_app, length_read -3);
			memset(temp_buff_from_app, 0x00, 20);
			host_rb[65+length_read -3] = 0x21;
			host_rb[66+length_read -3] = 0x56;
			put_len = length_read -3;
			run_where = 7;
		}
		if(from_app_step == 1)
		{
			if(sec_time_tick == 0)
			{
				sec_time_tick = clock_time();
			}
			if(sec_time_tick != 0 && clock_time_exceed(sec_time_tick, 100*1000))
			{
				sec_time_tick = 0;
				put_len = length_read -3;

				memcpy(all_zero,host_rb+1,23);
//				memset(host_rb+1, 0x00, 23);
				blt_push_notify_data(17, temp_buff_send_app , put_len);
				from_app_step = 0;
				ask_mode_flag = 0;
				check_time = 0;
				can_suspend_flag = 1;
			}
		}
	}

}

void deal_send_data_to_app(void)
{
	run_where = 8;
	if(from_app_step != 1)
	{
		if(host_rb[1] == 0xff)
		{
			while(!(host_rb[data_length+2] == 0x21 && host_rb[data_length+3] == 0x56))
			{
				data_length++;
				can_Deal = 1;
				allow_read = 0;
				if(data_length >= 21)
				{
					can_Deal = 0;
					data_length = 0;
					return;
				}
			}
		}
		if((data_length != 0) && can_Deal == 1)//memcmp(host_rb+1,all_zero,20))  (memcmp(host_rb+1,all_zero,data_length+3)
		{
			sleep_us(3000);
			can_Deal = 0;
			put_len = data_length;
			memset(temp_buff_send_app, 0x00, 20);
			memset(host_rb+64, 0x00, 23);
			memcpy (temp_buff_send_app, (host_rb+2), data_length);
			memcpy (all_zero, host_rb+1, 23 );
			after_master_write = 1;
			data_length = 0;
			memset(host_rb+1, 0x00, 23);
		}
	}
}









