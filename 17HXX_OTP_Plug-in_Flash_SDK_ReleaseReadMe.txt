//--Development path should not be too long, and should be full English directory name, otherwise it may lead to compilation, however
//--Development path should not be too long, and should be full English directory name, otherwise it may lead to compilation, however
//--Development path should not be too long, and should be full English directory name, otherwise it may lead to compilation, however
//-------------------------------------------------------------
//-------------------------------------------------------------
�汾�ţ�	V0111
����:		20180116
		1��chipID ��ʼλ����0x3FE9���Ϊ0x3FEA

//-------------------------------------------------------------
�汾�ţ�	V0110
����:		20171121
		2b8c4fe7f3246f8cbc672b6ea7159508fad5c447
		026556d81eaecbac5e8bcb75e7f1245987e8cba9
		1���������ӳ�ʱ�󣬹㲥���Ĺ��ߵ�����
		2��RF��ʼ������AGC

//-------------------------------------------------------------
�汾�ţ�	V0109
����:		20170831
		02037243e3482bb2aa02e40a1888affa1b6c1fa4
		301d8528b19ccd4d29dabba809a260f1c57fdc30
		1�����������ֻ���������
		2��set_freq_offset_xx �������Դ�ui����Ĭ��Ƶƫ

//-------------------------------------------------------------
�汾�ţ�	V0108
����:		20170815
		1�������ߵ�ѹ��ʱ��(3.6V)32Kƫ���������ش������Ĺ��������

//-------------------------------------------------------------
�汾�ţ�	V0107
����:		20170803
		1��OTP�Լ�FLASH�е�������Ϣ��������ע����Щ��ַ���Ѿ����뵽lib���棬������ui�и�����Щ��ַ����Ч�ģ�app_config.h��
			#define	CFG_TP_ORDER_ADDR_OTP		0x3FE6	// 2 bytes
			#define	CFG_TP_ORDER_ADDR_FLASH		0x76006	// 2 bytes	if  otp is not written, read flash instead
			#define	CFG_CHIP_ID_ADDR_OTP		0x3FE9	// 4bytes
			#define	CFG_CHIP_ID_ADDR_FLASH		0x76011	// 4bytes	if  otp is not written, read flash instead
			#define	CFG_ADR_MAC_ADDR_OTP   		0x3FE0	// 4bytes
			#define	CFG_ADR_MAC_ADDR_FLASH		0x76000	// 6 bytes
			#define	CFG_FREQUENCY_OFFSET_ADDR_OTP	0x3FE8	// 1byte	default 0xff,  if 0xfe or 0x00,turn off internal cap.
			#define	CFG_FREQUENCY_OFFSET_ADDR_FLASH 0x76010	// 1byte	default 0xff,  if 0xfe or 0x00,turn off internal cap.

		2��ԭmain.c��rf_drv_1M_init()������Ϊ��OTP��FLASH����һ������ ��main.c)
		3��ui.c�У�user_init()������������ʼ�������ֳ�OTP��FLASH�汾 (ui.c, pm_17H26.h, rf_drv_17H26.h)
		
//-------------------------------------------------------------
�汾�ţ�	V0106
����:		20170707
�������ݣ�	1���޸�OTP�д��������Ϣ��ROM��ַ���޸����£�
			#define	CFG_ADR_MAC_ADDR   		0x3FE0	// 4bytes  mac addres
			#define	CFG_TP_ORDER_ADDR		0x3FE6	// 2 bytes TP����ֵ
			#define	CFG_FREQUENCY_OFFSET_ADDR	0x3FE8	// 1byte  Ƶƫ���û��߽�ֹ�ڲ�����  default 0xff,  if 0xfe or 0x00,turn off internal cap.
			#define	CFG_CHIP_ID_ADDR		0x3FE9	// 4bytes chip ID

		   CFG_FREQUENCY_OFFSET_ADDR:�ô�ֵΪ0xfe����0x00ʱ����ֹ�ڲ�����,Ϊ0xffʱʹ���ڲ�Ĭ��Ƶ�����ã�����ֵ�Ǹ���Ƶ������
		2����pm_17H26.c����lib
		3��freq_calibration���룬�Լ�mac_address config��������lib


//-------------------------------------------------------------
�汾�ţ�	V0105 ����ʱʹ�ð汾��
����:		20170623
�������ݣ�	1���޸�wakeup- reset time
		2������APP����ʱ���׶Ͽ�������

//-------------------------------------------------------------
�汾�ţ�	V0104
����:		20170412
�������ݣ�	����lib����İ汾����Ϣ
		1�����������ֻ�����ʱ�жϵ�����
		2�������ļ���ɾ������Ĭ������ʱ�䣬����ʡ�ռ�����Ҫ�ڿ��ļ����޸�ѡ��
		3��sleep wakeup ����PLL���ƴ��루jensen��


//-------------------------------------------------------------
�汾�ţ�	V0102
����:		20170316
�������ݣ�	����lib����İ汾����Ϣ


//-------------------------------------------------------------
�汾�ţ�	V0101
����:		20170315
�������ݣ�	���¶�android7.0��֧�֣����µײ�aes�����Խ�ʡROM




