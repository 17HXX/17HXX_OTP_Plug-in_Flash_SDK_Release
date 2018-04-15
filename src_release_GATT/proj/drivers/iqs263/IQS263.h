/*******************************************************************************
 *
 *		Azoteq IQS263_Example_Code
 *
 *              IQS263.h - Registers & Memory Map
 *
*******************************************************************************/

#ifndef IQS263_H
#define	IQS263_H

// I2C DEFAULT SLAVE ADDRESS
#define IQS263_ADDR             0x44

/*********************** IQS263 REGISTERS *************************************/

#define DEVICE_INFO             0x00
#define SYS_FLAGS               0x01
#define COORDINATES             0x02
#define TOUCH_BYTES             0x03
#define COUNTS                  0x04
#define LTA                     0x05
#define DELTAS                  0x06
#define MULTIPLIERS             0x07
#define COMPENSATION            0x08
#define PROX_SETTINGS           0x09
#define THRESHOLDS              0x0A
#define TIMINGS_AND_TARGETS     0x0B
#define GESTURE_TIMERS          0x0C
#define ACTIVE_CHANNELS         0x0D


struct a_s {
    unsigned char id;
    unsigned char len;
};

#endif	/* IQS263_H */

