#pragma once


#ifdef WIN32
#include "../common/types.h"

typedef int (*handle_recv_data)(void *data, int len);

#define RECEIVE_MAX_LENGTH  128
#define SEND_MAX_LENGTH     128
#define SOCKET_HOST         "127.0.0.1"
#define SOCKET_PORT_SERVER         7001
#define SOCKET_PORT_CLIENT         7002

enum {
    SIMU_SOCKET = 0,
    TEST_SOCKET,
    WIRESHARK_SOCKET,
};


extern handle_recv_data handle_received_serial_data;
extern handle_recv_data handle_received_rf_data;

void socket_param_init(u8 type);

int node_send_to_rf(u8 *buf, u8 len);
int node_send_to_serial(u8 *buf, u8 len);
int node_send_to_wireshark(u8 *buf, u8 len);

int server_receive_from_rf(u8 *recvBuf, u8 bufLen);

#define SIMU_SOCK_UDP         0
#define SIMU_SOCK_TCP         1





void win32_param_init(void);
void simu_init(void);
int simu_recvFromRF(u8 *recvBuf, u8 bufLen);
int simu_recvFromTH(u8 *recvBuf, u8 bufLen);
int simu_sendToRF(u8 *buf, u8 len);
int simu_sendToWireshark(u8 *buf, u8 len);
int simu_sendToTH(u8* buf, u8 len);
void simu_setChannel(u8 ch);


void vs_sockEnvironmentInit(void);
void appSock_init(const char *ip, u32 port, u8 type);
int appSock_recv(u8 *recvBuf, u8 bufLen);

#endif
