/*
 * mouse_type.h
 *
 *  Created on: Feb 10, 2014
 *      Author: xuzhen
 */

#ifndef MOUSE_TYPE_H_
#define MOUSE_TYPE_H_
#include "..\..\proj\common\types.h"

#define MOUSE_FRAME_DATA_NUM   4

typedef struct {
	//u8 buff_id;
	u8 btn;
	s8 x;
	s8 y;
	s8 wheel;
	//s8 tl_wheel;
	//u8 hotkey;
}mouse_data_t;




#endif /* MOUSE_TYPE_H_ */
