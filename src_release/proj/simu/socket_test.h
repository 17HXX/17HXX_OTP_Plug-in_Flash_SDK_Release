#pragma once


#ifdef WIN32

#include<stdio.h>
#include<winsock2.h>

#include "../common/types.h"
#include "../common/assert.h"

#define RECEIVE_MAX_LENGTH  128
#define SEND_MAX_LENGTH     128
#define SOCKET_HOST         "127.0.0.1"
#define SOCKET_PORT_SERVER         7001
#define SOCKET_PORT_CLIENT         7002

#endif

