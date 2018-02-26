/*
* This file contains all the necessary settings for the IQS263 and this file can
* be changed from the GUI or edited here
* File:   IQS263_init.h
* Author: Azoteq
*/

#ifndef IQS263_INIT_H
#define IQS263_INIT_H

#if 1
/* Used to switch Projected mode & set Global Filter Halt (0x01 Byte1) */
#define SYSTEM_FLAGS_VAL					0x00

/* Enable / Disable system events (0x01 Byte2)*/
#define SYSTEM_EVENTS_VAL					0x00

/* Change the Multipliers & Base value (0x07 in this order) */
#define MULTIPLIERS_CH0						0x08//0x19 - default
#define MULTIPLIERS_CH1						0x08//0x08 - default
#define MULTIPLIERS_CH2						0x08//0x08 - default
#define MULTIPLIERS_CH3						0x08//0x08 - default
#define BASE_VAL						    0x08//0x44 - default

/* Change the Compensation for each channel (0x08 in this order) */
#define COMPENSATION_CH0					0x51
#define COMPENSATION_CH1					0x49
#define COMPENSATION_CH2					0x4A
#define COMPENSATION_CH3					0x49

/* Change the Prox Settings or setup of the IQS263 (0x09 in this order) */
#define PROXSETTINGS0_VAL					0x10  //@@-- 0x00
#define PROXSETTINGS1_VAL					0x5c  //@@-- 0x58
#define PROXSETTINGS2_VAL					0x20  //@@-- 0x04
#define PROXSETTINGS3_VAL					0x00  //@@-- 0x00
#define EVENT_MASK_VAL						0x0f

/* Change the Thresholds for each channel (0x0A in this order) */
#define PROX_THRESHOLD						0x04  //@@-- 0x04   0f
#define TOUCH_THRESHOLD_CH1					0x04  //@@-- 0x0c
#define TOUCH_THRESHOLD_CH2					0x04  //@@-- 0x0c
#define TOUCH_THRESHOLD_CH3					0x04  //@@-- 0x0c
#define MOVEMENT_THRESHOLD					0x03
#define RESEED_BLOCK						0x00
#define HALT_TIME						    0xff
#define I2C_TIMEOUT						    0x08

/* Change the Timing settings (0x0B in this order) */
#define LOW_POWER						    0x04  //@@-- 0x10
#define ATI_TARGET_TOUCH			        0x64  //@@-- 0x40
#define ATI_TARGET_PROX				        0x80
#define TAP_TIMER						    0x05
#define FLICK_TIMER						    0x51
#define FLICK_THRESHOLD						0x33

/* Set Active Channels (0x0D) */
#define ACTIVE_CHS						    0x0F


#else

/* System Flags (Address 0x01 Byte1) */
#define SYSTEM_FLAGS_VAL					0x00 //Write Show Reset to 0

/* Set Active Channels (Address 0x0D) */
#define ACTIVE_CHS							0x0F //CH0,CH1,CH2,CH3

/* Change the Multipliers & Base values (0x07 in this order) */
#define MULTIPLIERS_CH0						0x00
#define MULTIPLIERS_CH1						0x00
#define MULTIPLIERS_CH2						0x00
#define MULTIPLIERS_CH3						0x00
#define BASE_VAL							0x01

/* Change the Thresholds for each channel (Address 0x0A) */
#define PROX_THRESHOLD						0x04 //Prox Threshold        //raw : 0x0A
#define TOUCH_THRESHOLD_CH1					0x09 //Touch Threshold CH1
#define TOUCH_THRESHOLD_CH2					0x09 //Touch Threshold CH2
#define TOUCH_THRESHOLD_CH3					0x09 //Touch Threshold CH3
#define MOVEMENT_THRESHOLD					0x03 //Movement Threshold (not used)
#define RESEED_BLOCK						0x00 //Halt timeout Reseed Block (not used)
#define HALT_TIME							0xFF //Always halt
#define I2C_TIMEOUT							0x08 //8*1.28ms=10.24ms

/* Change the Timing settings (Address 0x0B) */
#define LOW_POWER							0x08 //8*16ms=128ms
#define ATI_TARGET_TOUCH					0x64 //100*8=800 Target
#define ATI_TARGET_PROX						0x64 //100*8=800 Target

/* Change the Prox Settings or setup of the IQS263 (Address 0x09) */
#define PROXSETTINGS0_VAL					0x10 //Redo ATI
#define PROXSETTINGS1_VAL					0x5E //Event Mode, 3CH slider
#define PROXSETTINGS2_VAL					0x20 //Wake from LP for counts in both direction
#define PROXSETTINGS3_VAL					0x03
#define EVENT_MASK_VAL						0x0F //ATI, Slide, Touch, Prox



//add
#define COMPENSATION_CH0					0x51
#define COMPENSATION_CH1					0x49
#define COMPENSATION_CH2					0x4A
#define COMPENSATION_CH3					0x49

#define TAP_TIMER						    0x05
#define FLICK_TIMER						    0x51
#define FLICK_THRESHOLD						0x33

#endif


#endif	/* IQS263_INIT_H */
