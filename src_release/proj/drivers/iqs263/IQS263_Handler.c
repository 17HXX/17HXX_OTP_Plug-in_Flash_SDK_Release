/*******************************************************************************
 *
 *		Azoteq IQS263_Example_Code
 *
 *              IQS263_Handler - IQS263 device settings and events
 *
*******************************************************************************/

//#include "Includes.h"
#include "../../tl_common.h"
#include "../../../proj_lib/rf_drv.h"
#include "../../../proj_lib/pm.h"
#include "../../../proj/mcu/clock.h"
#include "../../../proj/mcu/clock_i.h"

#include "i2c_high_level.h"
#include "i2c_low_level.h"
#include "iqs263_init.h"
#include "IQS263.h"
#include "IQS263_Handler.h"
/***************************** GLOBAL VARIABLES *******************************/

#if 0

unsigned char touch0 = 0;                       // variable identified with a Touch event
unsigned char prox = 0;                         // variable identified with a Prox event
unsigned char sliderCoords;                     // variable identified with a Slide event
unsigned char movement;                         // variable identified with a Movement event
unsigned char tap = 0;                          // variable identified with a Tap event
unsigned char leftFlick;                        // variable identified with a Flick event(left)
unsigned char rightFlick;                       // variable identified with a Flick event(right)
unsigned char events = 0;                       // variable identified with all events

// Data buffer for communication with the IQS263, set to an array size of 30 elememnts,
// which can fit all the IQS263 settings.
unsigned char data_buffer[8];
unsigned char product_num[4];


int print_flg = 0;

#if(!RAW_DATA_PRINT_MODE)
touch_data_t touch_data;


void pre_data_proc(void)
{
	print_flg = 0;
	touch_data.detect_tick = clock_time();


	while (RDY_IN != 0)       //wait for IQS device to become ready
	{
#if(USB_DBG_TOUCH)
		if(!print_flg && clock_time_exceed(touch_data.detect_tick ,100000)){

			print_flg = 1;

			u32 action_t = (u32)((touch_data.action_end_tick - touch_data.action_begin_tick)>>14);

			if(touch_data.action_type == SINGLE_TOUCH){  //touch
				printf("----------------%04d------------touch  %02x---\n",action_t,\
					   touch_data.coords_average);
			}
			else if(touch_data.wheel_inc_num){
				printf("----------------%04d------------slide inc %02x---\n",action_t,\
						touch_data.wheel_inc_num);
			}
			else if(touch_data.wheel_dec_num){
				printf("----------------%04d------------slide dec %02x---\n",action_t,\
						touch_data.wheel_dec_num);
			}
			else{
				printf("----------------%04d------------------------------\n",action_t);
			}
		}
#endif
	}

	if(print_flg){
		memset(&touch_data,0,sizeof(touch_data));
	}


	touch_data.cur_event_tick = clock_time();
}

void touch_data_update(u8 dir)
{
	//touch_data.coords_valid_last = touch_data.coords_last = \
			touch_data.coords_valid_max = touch_data.coords_valid_min =  touch_data.coords_current;


	touch_data.coords_valid_last = touch_data.coords_last = touch_data.coords_current;
	if(dir == DIR_INC){
		touch_data.coords_valid_min += SLIDE_COORDS_TRIG;
		touch_data.coords_valid_max = touch_data.coords_current;
	}
	else if(dir == DIR_DEC){
		touch_data.coords_valid_max -= SLIDE_COORDS_TRIG;
		touch_data.coords_valid_min = touch_data.coords_current;
	}

	touch_data.coords_tatal = touch_data.coords_current;
	touch_data.coords_valid_cnt = 1;
	touch_data.coords_dir = DIR_NONE;
	touch_data.coords_inc_cnt = touch_data.coords_dec_cnt = touch_data.coords_equ_cnt = 0;
}

void  touch_data_process(void)
{
	touch_data.coords_valid_flg = 0;
	touch_data.event_cnt++;


	if( touch_data.action_type != WHEEL_READY && touch_data.begin_flg && \
			clock_time_exceed(touch_data.action_begin_tick,SINGLE_TOUCH_TIME_THRES*1000)){
		touch_data.action_type = WHEEL_READY;
	}

	if(touch_data.event & 0x01){  //01,03,07:PROX : close or leave
		if(!touch_data.begin_flg){  //close
			//continuous close,
			if(!clock_time_exceed(touch_data.action_end_tick,DIFF_ACTION_INTERVAL_MIN*100)){
			}
			else{  //new close:start
				touch_data.action_begin_tick = touch_data.cur_event_tick;
			}
		}
		else{  //leave
			touch_data.action_end_tick = touch_data.cur_event_tick;

			//timing short, coords change low -> single touch
			if( ((u32)(touch_data.action_end_tick-touch_data.action_begin_tick)) < SINGLE_TOUCH_TIME_THRES*CLOCK_SYS_CLOCK_1MS  \
				   && (touch_data.coords_valid_max - touch_data.coords_valid_min) < TOUCH_COORDS_THRES){
				if(touch_data.action_type == ACTION_IDLE && touch_data.coords_valid_cnt > 0){
					touch_data.action_type = SINGLE_TOUCH;
					touch_data.coords_average = touch_data.coords_tatal/touch_data.coords_valid_cnt;
				}
			}
		}

		touch_data.begin_flg = !touch_data.begin_flg;
	}


	if(touch_data.event & 0x06 ){  //07,04,06,02:  coords data valid

		if(!touch_data.coords_valid_cnt){

			//first coords, default set valid,max,min
			touch_data.coords_valid_last = touch_data.coords_last = \
			   touch_data.coords_valid_max = touch_data.coords_valid_min =  touch_data.coords_current;
		}


		if(abs(touch_data.coords_current - touch_data.coords_last) < SMOOTH_COORDS_CHANGE){
			touch_data.coords_valid_flg = 1; //valid data
		}
		else{  //data sharp change. special proc

		}


		touch_data.coords_last = touch_data.coords_current;

	}



	///////////////////////////// data valid ///////////////////////////////////
	if(touch_data.coords_valid_flg){
		touch_data.coords_tatal += touch_data.coords_current;
		touch_data.coords_valid_cnt++;

		//current data diretion
		if(touch_data.coords_current > touch_data.coords_valid_last){
			touch_data.coords_inc_cnt++;
		}
		else if(touch_data.coords_current < touch_data.coords_valid_last){
			touch_data.coords_dec_cnt++;
		}
		else{
			touch_data.coords_equ_cnt ++;
		}

		//in idle mode,big data change, no touch anymore,  ready for wheel
		if(touch_data.action_type == ACTION_IDLE && \
			( touch_data.coords_current - touch_data.coords_valid_min > TOUCH_COORDS_EXCEED || \
		      touch_data.coords_valid_max - touch_data.coords_current > TOUCH_COORDS_EXCEED  ) ){
			touch_data.action_type = WHEEL_READY;
		}


		//get whole data stream direction
		int judge_dir_flg = 0;
		if(touch_data.coords_dir == DIR_NONE && touch_data.action_type == WHEEL_READY && touch_data.coords_valid_cnt > WHEEL_DIR_NUM_THRES){
			judge_dir_flg = 1;
		}
		else if(touch_data.coords_dir==DIR_INC && touch_data.coords_current < touch_data.coords_valid_last){  //inc dir with a dec data
			judge_dir_flg = 1;
		}
		else if(touch_data.coords_dir==DIR_DEC && touch_data.coords_current > touch_data.coords_valid_last){ //dec dir with a inc data
			judge_dir_flg = 1;
		}
		if(judge_dir_flg){
			touch_data.err_dir_thres = touch_data.coords_valid_cnt/4;
			if(touch_data.coords_inc_cnt > max2(touch_data.coords_dec_cnt,1) && touch_data.coords_dec_cnt <= touch_data.err_dir_thres){
				touch_data.coords_dir  = DIR_INC;
			}
			else if(touch_data.coords_dec_cnt > max2(touch_data.coords_inc_cnt,1) && touch_data.coords_inc_cnt <= touch_data.err_dir_thres){
				touch_data.coords_dir  = DIR_DEC;
			}
		}
		///////////////////////////////////////


		if(touch_data.coords_current - touch_data.coords_valid_min > SLIDE_COORDS_TRIG && touch_data.coords_dir == DIR_INC){
			touch_data_update(DIR_INC);
			touch_data.wheel_inc_num ++;
		}
		else if(touch_data.coords_valid_max - touch_data.coords_current > SLIDE_COORDS_TRIG && touch_data.coords_dir == DIR_DEC){
			touch_data.wheel_dec_num ++;
			touch_data_update(DIR_DEC);
		}


		//update max min
		if(touch_data.coords_valid_max < touch_data.coords_current){
			touch_data.coords_valid_max = touch_data.coords_current;
		}
		if(touch_data.coords_valid_min > touch_data.coords_current){
			touch_data.coords_valid_min = touch_data.coords_current;


		}


		touch_data.coords_valid_last = touch_data.coords_current; //update valid_last
	}
	///////////////////////////// data valid end///////////////////////////////////

#if(USB_DBG_TOUCH)
    printf("%02x,%02x,%02x,%02x,%04d  %01d,%02x  %02x,%02x,%02x,%02x  %02x,%02x  %02x\n",\
    		data_buffer[1], data_buffer[2], data_buffer[3],data_buffer[4],\
    		(touch_data.cur_event_tick>>14)%10000,\
    		touch_data.coords_valid_flg,touch_data.coords_valid_cnt,\
    		touch_data.coords_dir,touch_data.coords_inc_cnt,touch_data.coords_equ_cnt,touch_data.coords_dec_cnt,\
    		touch_data.coords_valid_max,touch_data.coords_valid_min, \
    		touch_data.wheel_inc_num<<4 | touch_data.wheel_dec_num);
#endif

}

#endif

/*************************** IQS263 DEVICE SETTINGS ***************************/

void IQS263DeviceSettings(void)
{
    // Switch on all lights to show whether the Program
    // has entered the DeviceSettings function.
    leds_all_on();

    // Read the product number
    CommsIQS_start();
    CommsIQS_Read(IQS263_ADDR, DEVICE_INFO, &product_num[0], 2);
    CommsIQS_stop();

    
    // Switch the IQS263 into projection mode - if necessary
    data_buffer[0] = SYSTEM_FLAGS_VAL;
    CommsIQS_start();
    CommsIQS_Write(IQS263_ADDR, SYS_FLAGS, &data_buffer[0], 1);
    CommsIQS_stop();
        
    // Set active channels
    data_buffer[0] = ACTIVE_CHS;
    CommsIQS_start();
    CommsIQS_Write(IQS263_ADDR, ACTIVE_CHANNELS, &data_buffer[0], 1);
    CommsIQS_stop();
        
    // Setup touch and prox thresholds for each channel
    data_buffer[0] = PROX_THRESHOLD;
    data_buffer[1] = TOUCH_THRESHOLD_CH1;
    data_buffer[2] = TOUCH_THRESHOLD_CH2;
    data_buffer[3] = TOUCH_THRESHOLD_CH3;
    data_buffer[4] = MOVEMENT_THRESHOLD;
    data_buffer[5] = RESEED_BLOCK;
    data_buffer[6] = HALT_TIME;
    data_buffer[7] = I2C_TIMEOUT;
    CommsIQS_start();
    CommsIQS_Write(IQS263_ADDR, THRESHOLDS, &data_buffer[0], 8);
    CommsIQS_stop();
        
    // Set the ATI Targets (Target Counts)
    data_buffer[0] = ATI_TARGET_TOUCH;
    data_buffer[1] = ATI_TARGET_PROX;
    CommsIQS_start();
    CommsIQS_Write(IQS263_ADDR, TIMINGS_AND_TARGETS, &data_buffer[0], 2);
    CommsIQS_stop();
        
    // Set the BASE value for each channel
    data_buffer[0] = MULTIPLIERS_CH0;
    data_buffer[1] = MULTIPLIERS_CH1;
    data_buffer[2] = MULTIPLIERS_CH2;
    data_buffer[3] = MULTIPLIERS_CH3;
    CommsIQS_start();
    CommsIQS_Write(IQS263_ADDR, MULTIPLIERS, &data_buffer[0], 4);
    CommsIQS_stop();

    // Setup prox settings
    data_buffer[0] = PROXSETTINGS0_VAL;
    data_buffer[1] = PROXSETTINGS1_VAL;
    data_buffer[2] = PROXSETTINGS2_VAL;
    data_buffer[3] = PROXSETTINGS3_VAL;
    data_buffer[4] = EVENT_MASK_VAL;
    CommsIQS_start();
    CommsIQS_Write(IQS263_ADDR, PROX_SETTINGS, &data_buffer[0], 5);
    CommsIQS_stop();

    // Setup Compensation (PCC)
    data_buffer[0] = COMPENSATION_CH0;
    data_buffer[1] = COMPENSATION_CH1;
    data_buffer[2] = COMPENSATION_CH2;
    data_buffer[3] = COMPENSATION_CH3;
    CommsIQS_start();
    CommsIQS_Write(IQS263_ADDR, COMPENSATION, &data_buffer[0], 4);
    CommsIQS_stop();


    write_reg8(0x8000,0x77);
        
    // Set timings on the IQS263
    data_buffer[0] = LOW_POWER;
    CommsIQS_start();
    CommsIQS_Write(IQS263_ADDR, TIMINGS_AND_TARGETS, &data_buffer[0], 1);

    write_reg8(0x8000,0x88);

    CommsIQS_stop();
    
    write_reg8(0x8000,0x99);

    // Set gesture timers on IQS263
    data_buffer[0] = TAP_TIMER;
    data_buffer[1] = FLICK_TIMER;
    data_buffer[2] = FLICK_THRESHOLD;
    CommsIQS_start();

    write_reg8(0x8000,0xaa);

    CommsIQS_Write(IQS263_ADDR, GESTURE_TIMERS, &data_buffer[0], 3);
    CommsIQS_stop();
    
    write_reg8(0x8000,0xbb);


    // Redo ati
    data_buffer[0] = 0x10;
    CommsIQS_start();
    CommsIQS_Write(IQS263_ADDR, PROX_SETTINGS, &data_buffer[0], 1);
    CommsIQS_stop();
    
    // Wait untill the ATI algorithm is done
    do
    {
        WaitMs(10);
        CommsIQS_start();
        CommsIQS_Read(IQS263_ADDR, SYS_FLAGS, &data_buffer[0], 1);
        CommsIQS_stop();
    }
    while ((data_buffer[0] & 0b00000100) == 0b00000100);

    // read the error bit to determine if ATI error occured
    CommsIQS_start();
    CommsIQS_Read(IQS263_ADDR, PROX_SETTINGS, &data_buffer[0], 2);
    CommsIQS_stop();

#if 0
    // If an ATI occured flash the LEDS
    if (data_buffer[1] & 0x02 == 0x02)
    {
        int i = 0;
        for (i = 0; i < 10; i++) {
            leds_all_on();
            WaitMs(50);
            leds_all_off();
        }
    }
    
    // Switch all the LEDS off to indicate that ATI was successful
    leds_all_off();
#endif

}


/*******************************************************************************
 *             This function will display the different event
 *             features of the IQS263 IC. This will be done by
 *             toggeling of four different LEDS, to create
 *             patterns identified with each event.
 ******************************************************************************/
void handleEvents(void)
{

#if RAW_DATA_PRINT_MODE

	print_flg = 0;
	touch_data.detect_tick = clock_time();

	while (RDY_IN != 0)       //wait for IQS device to become ready
	{

#if(USB_DBG_TOUCH)
		if(!print_flg && clock_time_exceed(touch_data.detect_tick ,100000)){
			print_flg = 1;
			printf("------------------------------\n");
		}
#endif
	}
	touch_data.cur_event_tick = clock_time();

	CommsIQS_start();
	// Start the communication session
	CommsIQS_Read(IQS263_ADDR, SYS_FLAGS, &data_buffer[0], 2);                  // Read the system flags register to enable all events
	CommsIQS_repeat_start();                                                    // Create another start condition
	//CommsIQS_Read(IQS263_ADDR, TOUCH_BYTES, &data_buffer[2], 1);                // Read from the touch bytes register to enable touch events
	//CommsIQS_repeat_start();                                                    // Create another start condition
	CommsIQS_Read(IQS263_ADDR, COORDINATES, &data_buffer[3], 1);                // Read the coordinates register to get slider coordinates
	CommsIQS_stop();                                                            // Stop the communication session


#if(USB_DBG_TOUCH)
    printf("%02x,%02x,%02x,%02x,%02x,%06d\n",data_buffer[1], data_buffer[2], data_buffer[3],data_buffer[4],data_buffer[5],\
    		touch_data.cur_event_tick>>14);
#endif


    events = data_buffer[1];
    /******************************** SLIDE ***********************************/
    if (((events & 0x04) == 0x04) && (events != 0))
        slideEvent();

#else

	pre_data_proc();


    CommsIQS_start();
    // Start the communication session
    CommsIQS_Read(IQS263_ADDR, SYS_FLAGS, &data_buffer[0], 2);                  // Read the system flags register to enable all events
    CommsIQS_repeat_start();                                                    // Create another start condition
    CommsIQS_Read(IQS263_ADDR, TOUCH_BYTES, &data_buffer[2], 1);                // Read from the touch bytes register to enable touch events
    CommsIQS_repeat_start();                                                    // Create another start condition
    CommsIQS_Read(IQS263_ADDR, COORDINATES, &data_buffer[3], 3);                // Read the coordinates register to get slider coordinates
    CommsIQS_stop();                                                            // Stop the communication session


    touch_data.event = data_buffer[1];
    touch_data.coords_current = data_buffer[3];

    touch_data_process();

#endif

    events = data_buffer[1];
    /******************************** SLIDE ***********************************/
    if (((events & 0x04) == 0x04) && (events != 0))
        slideEvent();

#if 0

    /******************************* PROXIMITY ********************************/
    if ((events & 0x01) == 0x01)
        proxEvent();

    /******************************** TOUCH ***********************************/
    if ((events & 0x02) == 0x02)
        touchEvent();

    /******************************* MOVEMENT *********************************/

    if ((events & 0x10) == 0x10)
        movementEvent();
    else
        led3_off();

    /********************************* TAP ************************************/

    if((events & 0x20) == 0x20)
        tapEvent();

    /******************************* FLICK (LEFT) *****************************/

    if((events & 0x40) == 0x40)
        flickLeft();

    /******************************* FLICK (RIGHT) ****************************/

    if((events & 0x80) == 0x80)
        flickRight();
#endif
}

/*******************************************************************************
 *      This function handles touch events. If a touch event occurs
 *      an LED will be switched on marking the current channel that the
 *      touch event occured in.
 ******************************************************************************/
void touchEvent(void)
{
    touch0 = data_buffer[2];

    if (touch0 != 0)
    {
        /* CHANNEL 1*/
        if ((touch0 & 0x02) == 0x02)                    // If a touch event occurs on Channel 1
        {
            led1_on();                         // Toggle LED 1 ON
        }
        else
        {
            led1_off();                         // Toggle LED 1 OFF
        }

        /* CHANNEL 2 */
        if ((touch0 & 0x04) == 0x04)                    // If a touch event occurs on Channel 2
        {
            led2_on();                         // Toggle LED 2 ON
        }
        else
        {
            led2_off();                         // Toggle LED 2 OFF
        }

        /* CHANNEL 3 */
        if ((touch0 & 0x08) == 0x08)                    // If a touch event occurs on Channel 3
        {
            led1_on();                         // Toggle LED 1 ON
            led2_on();                         // Toggle LED 2 ON
        }
        else
        {
            led1_off();                         // Toggle LED 1 OFF
            led2_off();                         // Toggle LED 2 OFF
        }
    }
}
/*******************************************************************************
 *      This function handles a slide event, if a slide event is triggered
 *      an LED will switch on marking the position that the finger of the
 *      user is currently on including the coordinate value thereof.
 ******************************************************************************/

u8 a_coordinate;
void slideEvent(void)
{
    sliderCoords = data_buffer[3];
    touch0 = data_buffer[2];

    a_coordinate = touch0;

    if (touch0 != 0)
    {
        if ((sliderCoords > 0 && sliderCoords < 85)&& ((touch0 & 0x02) == 0x02))
        {
            led1_on();             // Toggle LED 1 ON
            led2_off();             // Toggle LED 2 OFF
            led3_off();             // Toggle LED 3 OFF
            led4_off();             // Toggle LED 4 OFF
        }
        else if ((sliderCoords > 84 && sliderCoords < 170)&& ((touch0 & 0x04) == 0x04))
        {
            led1_off();             // Toggle LED 1 OFF
            led2_on();             // Toggle LED 2 ON
            led3_off();             // Toggle LED 3 OFF
            led4_off();             // Toggle LED 4 OFF
        }
        else if ((sliderCoords > 170 && sliderCoords < 255)&& ((touch0 & 0x08) == 0x08))
        {
#if 0
            led1_on();             // Toggle LED 1 ON
            led2_on();             // Toggle LED 2 ON
            led3_off();             // Toggle LED 3 OFF
            led4_off();             // Toggle LED 4 OFF
#else
            led1_off();
            led2_off();
            led3_on();
            led4_off();
#endif
        }
        else
        {
            leds_all_off();               // Toggle All LEDS OFF
        }
    }
}

/*******************************************************************************
 *      This function handles a prox event, if proximity is being detected
 *      LED 4 will be switched ON, and switched OFF if no proximity is being
 *      detected.
 ******************************************************************************/
void proxEvent(void)
{
    prox = data_buffer[2];

    if ((prox & 0x01) == 0x01)              // If a prox event occures
    {
        led4_on();                 // Toggle LED 4 ON
    }
    else
    {
        led4_off();                 // Toggle LED 4 OFF
    }
}

/*******************************************************************************
 *      This function handles a movement event, each time movement is
 *      sensed, LED 3 will be switched ON, and switched OFF if no movement
 *      is sensed.
 ******************************************************************************/
void movementEvent(void)
{
    movement = data_buffer[1];

    if ((movement & 0x10) == 0x10)          // If a movement event occurs
    {
        led3_on();                 // Toggle LED 3 ON
    }
    else
    {
        led3_off();                 // Toggle LED 3 OFF
    }
}

/*******************************************************************************
 *      This function handles a tap event, each time this event is
 *      triggered ALL LEDS will flash 3 times.
 ******************************************************************************/
void tapEvent(void)
{
    u8 i;
    tap = data_buffer[1];

    if ((tap & 0x20) == 0x20)               // If a tap event occurs
    {
        for (i = 0; i < 3; i++)
        {
            led1_on();
            led2_on();            /* Toggle ALL LEDS ON */
            led3_on();
            led4_on();
            WaitMs(50);                  /* Wait for 50ms */
            led1_off();
            led2_off();
            led3_off();            /* Toggle ALL LEDS OFF */
            led4_off();
            WaitMs(50);                  /* Wait for 50ms */
        }
    }
}

/*******************************************************************************
 *     This function handles a right flick event, each time this event is
 *     is triggered, LED 1 will flicker 5 times.
 ******************************************************************************/
void flickRight(void)
{
    u8 i;
    rightFlick = data_buffer[1];

    if ((rightFlick & 0x80) == 0x80)       // If a right flick event occurs
    {
        for (i = 0; i < 5; i++)
        {
            tap = 0x00;                     // avoid tap event coliding with flicker event
            led1_on();             // Toggle LED 1 ON
            WaitMs(300);                  // Wait 300ms
            led1_off();             // Toggle LED 1 OFF
            WaitMs(300);                  // Wait 300ms
        }
    }
    else
    {
        led1_off();                 // Toggle LED 1 OFF
    }
}

/*******************************************************************************
 *     This function handles a left flick event, each time this event is
 *     is triggered, LED 2 will flicker 5 times.
 ******************************************************************************/
void flickLeft(void)
{
    u8 i;
    leftFlick = data_buffer[1];

    if ((leftFlick & 0x40) == 0x40)        // If a left click event occurs
    {
        for (i = 0; i < 5; i++)
        {
            tap = 0x00;                     // avoid tap event coliding with flicker event
            led2_on();             // Toggle LED 2 ON
            WaitMs(300);                  // Wait 300ms
            led2_off();             // Toggle LED 2 OFF
            WaitMs(300);                  // Wait 300ms
        }
    }
    else
    {
        led2_off();                 // Toggle LED 2 OFF
    }
}



void iqs263_init(void)
{
    leds_init();

    iqs263_i2c_init();

    IQS263DeviceSettings();
}



#endif








