//--Development path should not be too long, and should be full English directory name, otherwise it may lead to compilation, however
//--Development path should not be too long, and should be full English directory name, otherwise it may lead to compilation, however
//--Development path should not be too long, and should be full English directory name, otherwise it may lead to compilation, however
//-------------------------------------------------------------
//-------------------------------------------------------------
版本号：	V0111
日期:		20180116
		1、chipID 起始位置由0x3FE9变更为0x3FEA

//-------------------------------------------------------------
版本号：	V0110
日期:		20171121
		2b8c4fe7f3246f8cbc672b6ea7159508fad5c447
		026556d81eaecbac5e8bcb75e7f1245987e8cba9
		1、修正连接超时后，广播功耗过高的问题
		2、RF初始化增加AGC

//-------------------------------------------------------------
版本号：	V0109
日期:		20170831
		02037243e3482bb2aa02e40a1888affa1b6c1fa4
		301d8528b19ccd4d29dabba809a260f1c57fdc30
		1、修正部分手机连接问题
		2、set_freq_offset_xx 函数可以从ui设置默认频偏

//-------------------------------------------------------------
版本号：	V0108
日期:		20170815
		1、修正高电压的时候(3.6V)32K偏差过大，造成重传、功耗过大的问题

//-------------------------------------------------------------
版本号：	V0107
日期:		20170803
		1、OTP以及FLASH中的配置信息重新整理，注意这些地址都已经编译到lib里面，所以在ui中更改这些地址是无效的（app_config.h）
			#define	CFG_TP_ORDER_ADDR_OTP		0x3FE6	// 2 bytes
			#define	CFG_TP_ORDER_ADDR_FLASH		0x76006	// 2 bytes	if  otp is not written, read flash instead
			#define	CFG_CHIP_ID_ADDR_OTP		0x3FE9	// 4bytes
			#define	CFG_CHIP_ID_ADDR_FLASH		0x76011	// 4bytes	if  otp is not written, read flash instead
			#define	CFG_ADR_MAC_ADDR_OTP   		0x3FE0	// 4bytes
			#define	CFG_ADR_MAC_ADDR_FLASH		0x76000	// 6 bytes
			#define	CFG_FREQUENCY_OFFSET_ADDR_OTP	0x3FE8	// 1byte	default 0xff,  if 0xfe or 0x00,turn off internal cap.
			#define	CFG_FREQUENCY_OFFSET_ADDR_FLASH 0x76010	// 1byte	default 0xff,  if 0xfe or 0x00,turn off internal cap.

		2、原main.c中rf_drv_1M_init()函数改为：OTP和FLASH各用一个函数 （main.c)
		3、ui.c中：user_init()函数里面多个初始化函数分成OTP和FLASH版本 (ui.c, pm_17H26.h, rf_drv_17H26.h)
		
//-------------------------------------------------------------
版本号：	V0106
日期:		20170707
更新内容：	1、修改OTP中存放配置信息的ROM地址，修改如下：
			#define	CFG_ADR_MAC_ADDR   		0x3FE0	// 4bytes  mac addres
			#define	CFG_TP_ORDER_ADDR		0x3FE6	// 2 bytes TP定制值
			#define	CFG_FREQUENCY_OFFSET_ADDR	0x3FE8	// 1byte  频偏设置或者禁止内部电容  default 0xff,  if 0xfe or 0x00,turn off internal cap.
			#define	CFG_CHIP_ID_ADDR		0x3FE9	// 4bytes chip ID

		   CFG_FREQUENCY_OFFSET_ADDR:该处值为0xfe或者0x00时，禁止内部电容,为0xff时使用内部默认频率设置，其它值是更新频率设置
		2、把pm_17H26.c收入lib
		3、freq_calibration代码，以及mac_address config代码收入lib


//-------------------------------------------------------------
版本号：	V0105 （临时使用版本）
日期:		20170623
更新内容：	1、修改wakeup- reset time
		2、修正APP连接时容易断开的问题

//-------------------------------------------------------------
版本号：	V0104
日期:		20170412
更新内容：	更新lib里面的版本号信息
		1、修正红米手机连接时中断的问题
		2、加密文件的删减代码默认优先时间，若需省空间则需要在库文件中修改选项
		3、sleep wakeup 增加PLL控制代码（jensen）


//-------------------------------------------------------------
版本号：	V0102
日期:		20170316
更新内容：	更新lib里面的版本号信息


//-------------------------------------------------------------
版本号：	V0101
日期:		20170315
更新内容：	更新对android7.0的支持，更新底层aes代码以节省ROM




