/*******************************************************************************
 *
 *		Azoteq IQS263_Example_Code
 *
 *              IQS263_Handler.h
 *
*******************************************************************************/

#ifndef IQS263_HANDLER_H
#define	IQS263_HANDLER_H

#if 0

void IQS263DeviceSettings(void);
void handleEvents(void);
void proxEvent(void);
void touchEvent(void);
void slideEvent(void);
void flickLeft(void);
void flickRight(void);
void tapEvent(void);
void movementEvent(void);


#define PROX_EVNET_MASK  			0x01
#define TOUCH_EVNET_MASK			0x02
#define SLIDE_EVNET_MASK			0x04


#define SMOOTH_COORDS_CHANGE		0x20
#define TOUCH_COORDS_THRES   		0x30

#define TOUCH_COORDS_EXCEED			0x40

#define SLIDE_COORDS_TRIG			0x38

#define SINGLE_TOUCH_TIME_THRES		250  //ms
#define DIFF_ACTION_INTERVAL_MIN	100  //ms


#define ACTION_IDLE 				0
#define SINGLE_TOUCH  				1
#define WHEEL_READY  				2
#define WHEEL_SLIDE  				3



#define DIR_NONE					0
#define DIR_INC						1
#define DIR_DEC						2

#define WHEEL_DIR_NUM_THRES			3


#define RAW_DATA_PRINT_MODE				1

#define USB_DBG_TOUCH					1


typedef struct{
	u8 event;
	u8 action_type;
	u8 coords_valid_flg;
	u8 begin_flg;

	u8 coords_current;
	u8 coords_last;
	u8 rsv1;
	u8 rsv2;


	u8 coords_valid_last;
	u8 coords_valid_max;
	u8 coords_valid_min;
	u8 coords_average;

	u8 coords_valid_cnt;
	u8 coords_inc_cnt;
	u8 coords_dec_cnt;
	u8 coords_equ_cnt;

	u8 coords_dir;  //1: inc   2:dec   0:none
	u8 err_dir_thres;
	u8 wheel_inc_num;
	u8 wheel_dec_num;

	u16 coords_tatal;
	u16 event_cnt;

	u32 cur_event_tick;
	u32 action_begin_tick;
	u32 action_end_tick;
	u32 detect_tick;
}touch_data_t;


extern touch_data_t touch_data;


#endif

#endif	/* IQS263_HANDLER_H */

