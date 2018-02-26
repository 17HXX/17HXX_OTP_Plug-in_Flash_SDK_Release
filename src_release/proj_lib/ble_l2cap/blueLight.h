
#pragma once

/////////////////////////////  PARING HEAD /////////////////////////////////////////////
#define			BLE_GATT_OP_PAIR_REQ			1
#define			BLE_GATT_OP_PAIR_RSP			2
#define			BLE_GATT_OP_PAIR_REJECT			3
#define			BLE_GATT_OP_PAIR_NETWORK_NAME	4
#define			BLE_GATT_OP_PAIR_NETWORK_PASS	5
#define			BLE_GATT_OP_PAIR_NETWORK_LTK	6
#define			BLE_GATT_OP_PAIR_CONFIRM		7
#define			BLE_GATT_OP_PAIR_LTK_REQ		8
#define			BLE_GATT_OP_PAIR_LTK_RSP		9
#define			BLE_GATT_OP_PAIR_DELETE			10
#define			BLE_GATT_OP_PAIR_DEL_RSP		11
#define			BLE_GATT_OP_ENC_REQ				12
#define			BLE_GATT_OP_ENC_RSP				13
#define			BLE_GATT_OP_ENC_FAIL			14
#define			BLE_GATT_OP_ENC_READY			15

///////////////////////////// SMP ///////////////////////////////////
#define			SMP_OP_PAIRING_REQ					1
#define			SMP_OP_PAIRING_RSP					2
#define			SMP_OP_PAIRING_CONFIRM				3
#define			SMP_OP_PAIRING_RANDOM				4
#define			SMP_OP_PAIRING_FAIL					5
#define			SMP_OP_ENC_INFO						6
#define			SMP_OP_ENC_IDX						7
#define			SMP_OP_ENC_IINFO					8
#define			SMP_OP_ENC_IADR						9
#define			SMP_OP_ENC_SIGN						0x0a
#define			SMP_OP_SEC_REQ						0x0b
#define			SMP_OP_WAIT							0x0f

enum{
	EVENT_PKT_CUA = 0,			// connected undirected advertising event
	EVENT_PKT_ADV = EVENT_PKT_CUA,
	EVENT_PKT_CDA = 1,			// connected directed advertising event
	EVENT_PKT_NUA = 2,			// non-connected undirected advertising
	EVENT_PKT_SCAN_REQ = 3,
	EVENT_PKT_SCAN_RSP = 4,
	EVENT_PKT_CONNECT = 5,
	EVENT_PKT_DISCV = 6,		// connected discovery advertising event 
	
	EVENT_SYS_TIMER,
	EVENT_PKT_PAIR,		// PKT 的类型，同时作为 event 类型
	EVENT_PKT_RELAY,	// PKT 的类型，同时作为 event 类型
	EVENT_PKT_DATA,
	EVENT_PKT_DATA_RESP,
	EVENT_PKT = 0xfe,
	EVENT_NONE = 0xff,
};

typedef struct {
    u8 llid   :2;
    u8 nesn   :1;
    u8 sn     :1;
    u8 md     :1;
    u8 rfu1   :3;
}rf_data_head_t;

#define PKT_DMAOFF			4
#define PKT_RFOFF			(PKT_DMAOFF + 2)
#define PKT_L2OFF			(PKT_RFOFF + 4)

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)
}rf_packet_head_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)
}rf_packet_auto_reply_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)

	u8	advA[6];			//address
	u8	data[30];			//0-31 byte
}rf_packet_adv_t;


typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)

	u8	scanA[6];			//
	u8	advA[6];			//
}rf_packet_scan_req_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)

	u8	advA[6];			//address
	u8	data[30];			//0-31 byte
}rf_packet_scan_rsp_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4): connect request PDU
	u8  rf_len;				//LEN(6)_RFU(2)
	u8	scanA[6];			//
	u8	advA[6];			//
	u8	accessCode[4];		// access code
	u8	crcinit[3];
	u8	winSize;
	u16	winOffset;
	u16 interval;
	u16 latency;
	u16 timeout;
	u8	chm[5];
	u8	hop;				//sca(3)_hop(5)
}rf_packet_connect_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4): connect request PDU
	u8  rf_len;				//LEN(6)_RFU(2)
	u8	scanA[6];			//
	u8	advA[6];			//
	u8	aa[4];				// access code
	u8	crcinit[3];
	u8	wsize;
	u16	woffset;
	u16 interval;
	u16 latency;
	u16 timeout;
	u8	chm[5];
	u8	hop;				//sca(3)_hop(5)
}rf_packet_ll_init_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4): connect request PDU
	u8  rf_len;				//LEN(6)_RFU(2)

	u8	scanA[6];			//
	u8	advA[6];			//
	u8	aa[4];				// access code
	u8	crcinit[3];
	u8	wsize;
	u16	woffset;
	u16 interval;
	u16 latency;
	u16 timeout;
	u8	chm[5];
	u8	hop;				//sca(3)_hop(5)
}rf_packet_relay_t;

/*
LLID(2) - NESN(1) - SN(1) - MD(1) - RFU(3) - Length(5) - RFU(3)
*/


typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)
	u16	l2capLen;
	u16	chanId;
}rf_packet_l2cap_head_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 data[1];
}rf_packet_l2cap_req_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u8	data;
}rf_packet_l2cap_cust_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 	errOpcode;
	u16 errHandle;
	u8  errReason;
}rf_packet_att_errRsp_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)

	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8	startingHandle;
	u8	startingHandle1;
	u8	endingHandle;
	u8	endingHandle1;
	u8	attType[2];				//
}rf_packet_att_readByType_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u16 startingHandle;
	u16 endingHandle;
	u8 att_type[2];
}rf_packet_att_common_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)

	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8	startingHandle;
	u8	startingHandle1;
	u8	endingHandle;
	u8	endingHandle1;
	u8	attType[2];
	u8  attValue[2];
}rf_packet_att_findByTypeReq_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8	startingHandle;
	u8	startingHandle1;
	u8	endingHandle;
	u8	endingHandle1;
}rf_packet_att_findInfoReq_t;


typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)

	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 	data[1];
}rf_packet_att_findByTypeRsp_t;


typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 handle;
	u8 handle1;
}rf_packet_att_read_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 handle;
	u8 handle1;
	u8 offset;
	u8 offset1;
}rf_packet_att_readBlob_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 	value[22];
}rf_packet_att_readRsp_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8  datalen;
	u8  data[1];			// character_handle / property / value_handle / value
}rf_packet_att_readByTypeRsp_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8  datalen;
	u8  data[1];
}rf_packet_att_readByGroupTypeRsp_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8  format;
	u8  data[1];			// character_handle / property / value_handle / value
}rf_packet_att_findInfoRsp_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 handle;
	u8 handle1;
	u8 value;
}rf_packet_att_write_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8 handle[2];
	u8 data;
}rf_packet_att_notification_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number

	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)

	u16	l2cap;				//0x17
	u16	chanid;				//0x04,

	u8	att;				//0x12 for master; 0x1b for slave
	u8	hl;					// assigned by master
	u8	hh;					//
	u8	sno;

	u8	ctype;
	u8	cmd[18];				//byte
}rf_packet_ll_write_data_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u16 mtu;
}rf_packet_att_mtu_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
}rf_packet_att_writeRsp_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)
	u8 	opcode;
	u8	data[8];
}rf_packet_feature_rsp_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)
	u8 	opcode;
	u8  mainVer;
	u16 vendor;
	u16 subVer;
}rf_packet_version_ind_t;

typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8 	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)
	u8 	opcode;
	u8 	winSize;
	u16 winOffset;
	u16 interval;
	u16 latency;
	u16 timeout;
	u16 instant;
}rf_packet_connect_upd_req_t;

typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8 	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)
	u8 	opcode;
	u8 	chm[5];
	u16 instant;
} rf_packet_chm_upd_req_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)
	u8 	opcode;
	u8	data[1];
}rf_packet_ctrl_unknown_t;


typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RA(1)_TA(1)_RFU(2)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)
	u16	l2capLen;
	u16	chanId;
	u8  opcode;
	u8  id;
	u16 siglen;		
    u16 min_interval;
    u16 max_interval;
    u16 latency;
    u16 timeout;
}rf_packet_connParUpReq_t;

typedef struct {
	u8  valid;
	u8 	winSize;
	u16 winOffset;
	u16 interval;
	u16 latency;
	u16 timeout;
	u16 instant;
}connect_upd_data_t;

typedef struct {
	u8  valid;
	u8 	chm[5];
	u16 instant;
}connect_chm_upd_data_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number

	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)

	u8	opcode;				//
	u8	dat[1];				//
}rf_packet_ll_control_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number

	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)
	u16	flag;

	u32	src_id;

	u8	att;				//0x12 for master; 0x1b for slave
	u8	hl;					// assigned by master
	u8	hh;					//
	u8	sno;

	u16	nid;				// network ID
	u16	group;

	u32	dst_id;

	u8	cmd[11];			//byte
							// 10 xx xx xx xx xx xx		=> light on
							// 11 xx xx xx xx xx xx		=> light off
							// 12 rr gg bb ww uu vv		=> set

	//u32	mic[4];			//optional
}rf_packet_ll_rc_data_t;

typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number

	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(5)_RFU(3)

	u16	l2capLen;			// can be src_id
	u16	chanId;

	u8	att;				//0x12 for master; 0x1b for slave
	u8	hl;					// assigned by master
	u8	hh;					//
	u8	sno;

	u16	mic;				// network ID
	u16	group;

	u8	dst_id[4];

	u8	cmd[11];			//byte
							// 10 xx xx xx xx xx xx		=> light on
							// 11 xx xx xx xx xx xx		=> light off
							// 12 rr gg bb ww uu vv		=> set

	//u32	mic[4];			//optional
}rf_packet_mesh_data_phone_t;

typedef struct{
    u8 sno[3];
    u8 src[2];
    u8 dst[2];
    u8 op_para[13];
 //   u8 ttl;
 //   u8 hop;
}rf_packet_mesh_nwk_t;


typedef struct{
	u32 dma_len;            //29

	u8	rf_len;				//28
	u8  type;				//LEN(5)_RFU(3)

	u8	src_id[4];			// src_id

	u8	ttl;				// time to live
	u8	hl;					// assigned by master
	u8	hh;					//
	u8	sno;

	u16	mic;				// network ID
	u16	group;

	u8	dst_id[4];

	u8	cmd[11];			//byte
							// 10 xx xx xx xx xx xx		=> light on
							// 11 xx xx xx xx xx xx		=> light off
							// 12 rr gg bb ww uu vv		=> set

	//u32	mic[4];			//optional
}rf_packet_mesh_data_t1;

typedef struct{
	u32 dma_len;            //29

	u8	rf_len;				//28
	u8  type;				//LEN(5)_RFU(3)

	u16	l2cap;				// l2cap length
	u16	chan;				// channel ID

	u8	ttl;				// time to live
	u8	hl;					// assigned by master
	u8	hh;					//
	rf_packet_mesh_nwk_t	c;

}rf_packet_mesh_phone_t;

typedef struct{
	u32 dma_len;            //29

	u8	rf_len;				//28
	u8  type;				//LEN(5)_RFU(3)

	u16	l2cap;				// l2cap length
	u16	chan;				// channel ID

	u8	ttl;				// time to live
	u8	hl;					// assigned by master
	u8	hh;					//
	rf_packet_mesh_nwk_t	c;
	u8 rsv[6];

}rf_packet_mesh_data_t;

typedef struct{
	u32 dma_len;            //39

	u8	rf_len;				//38
	u8  type;				//LEN(5)_RFU(3)

	u16	l2cap;				// l2cap length
	u16	chan;				// channel ID

	u8	ttl;				// time to live
	u8	hl;					// assigned by master
	u8	hh;					//
	u8	dat[30];

}rf_packet_mesh_status_t;


#define BLE_ADDR_LEN                     6

//Definition for BLE Common Address Type
 /* Device Address Type */
 #define BLE_ADDR_PUBLIC                  0
 #define BLE_ADDR_RANDOM                  1
 #define BLE_ADDR_INVALID                 0xff

typedef struct {
	u8 type;
	u8 address[BLE_ADDR_LEN];
} addr_t;


//Definition for White List Table
#define  MAX_WHITE_LIST_SIZE    4
typedef struct {
	u8 curNum;
	addr_t wl_devices[MAX_WHITE_LIST_SIZE];
} ll_whiteListTbl_t;

// define smp paring request
typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(6)_RFU(2)
	u16	l2capLen;
	u16	chanId;
    u8 code;
    u8 ioCapability;
    u8 obbDataFlag;
    u8 authReq;
    u8 maxEncKeySize;
    u8 initiatorKeyDist;
    u8 responderKeyDist;
} smp_pairingReq_t;

typedef struct {
    u8 code;
    u8 ioCapability;
    u8 obbDataFlag;
    u8 authReq;
    u8 maxEncKeySize;
    u8 initiatorKeyDist;
    u8 responderKeyDist;
} smp_pairingReqData_t;

// define smp paring response
typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(6)_RFU(2)
	u16	l2capLen;
	u16	chanId;
    u8 code;
    u8 ioCapability;
    u8 obbDataFlag;
    u8 authReq;
    u8 maxEncKeySize;
    u8 initiatorKeyDist;
    u8 responderKeyDist;
} smp_pairingResp_t;

// define smp paring confirm
typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(6)_RFU(2)
	u16	l2capLen;
	u16	chanId;
    u8 code;
    u8 cnfVal[16];
} smp_pairingCnf_t;

// define smp paring random
typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(6)_RFU(2)
	u16	l2capLen;
	u16	chanId;
    u8 code;
    u8 randVal[16];
} smp_pairingRand_t;

// define smp paring random
typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(6)_RFU(2)
	u16	l2capLen;
	u16	chanId;
    u8 code;
    u8 reason;
} smp_pairingFailed_t;

typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(6)_RFU(2)
	u16	l2capLen;
	u16	chanId;
    u8 code;
    u8 ltk[16];
} smp_encInfo_t;

typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(6)_RFU(2)
	u8	opcode;
	u8	rand[8];
	u8	ediv[2];
	u8	sdk[8];
    u8 iv[4];
} smp_encryptReq_t;

typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(6)_RFU(2)
	u8	opcode;
	u8	sdk[8];
    u8 iv[4];
} smp_encryptRsp_t;

typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(6)_RFU(2)
	u8	opcode;
} smp_startEncrypt_t;

typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(6)_RFU(2)
	u8	opcode;
} smp_pauseEncryptRsp_t;

// define master identification
typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(6)_RFU(2)
	u16	l2capLen;
	u16	chanId;
    u8 code;
    u8 ediv[2];
    u8 rand[8];
} smp_masterId_t;


// define identity information
typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(6)_RFU(2)
	u16	l2capLen;
	u16	chanId;
    u8 code;
    u8 irk[16];
} smp_idInfo_t;

// define identity address information
typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(6)_RFU(2)
	u16	l2capLen;
	u16	chanId;
    u8 code;
	u8 addrType;
	u8 advA[6];
} smp_idAddrInfo_t;


// define signing information
typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(6)_RFU(2)
	u16	l2capLen;
	u16	chanId;
    u8 code;
    u8 sigKey[16];
} smp_sigInfo_t;


// define signing information
typedef struct {
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	u8	type;				//RFU(3)_MD(1)_SN(1)_NESN(1)-LLID(2)
	u8  rf_len;				//LEN(6)_RFU(2)
	u16	l2capLen;
	u16	chanId;
    u8 code;
    u8 authReq;
} smp_secReq_t;

typedef struct {
    u8 pairRand[16];
    u8 pairCnf[16];
} smp_pairingInfo_t;

typedef struct {
    /* data */
    u8 ltk[16];
    u16 ediv;
    u16 div;
    u8 rand[8];
    u8 keySize;
} smp_secKey_t;

typedef struct {
    /* data */
    u8 csrk[16];
    u32 signCounter;
} smp_secSigInfo_t;

typedef enum {
    SMP_CODE_PAIRING_REQUEST                      = 0x01,
    SMP_CODE_PAIRING_RESPONSE                     = 0x02,       
    SMP_CODE_PAIRING_CONFIRM                      = 0x03,
    SMP_CODE_PAIRING_RANDOM                       = 0x04,
    SMP_CODE_PAIRING_FAILED                       = 0x05,
    SMP_CODE_ENCRYPTION_INFORMATION               = 0x06,
    SMP_CODE_MASTER_IDENTIFICATION             	  = 0x07,
    SMP_CODE_IDENTITY_INFORMATION                 = 0x08,
    SMP_CODE_IDENTITY_ADDRESS_INFORMATION         = 0x09,
    SMP_CODE_SIGNING_INFORMATION                  = 0x0a,
    SMP_CODE_SECURITY_REQUEST                     = 0x0b,
} smp_cmd_t;


////////////////////////////////////////////////////////////////////////////
typedef int (*smp_brx_handler_t)(u8 * p, int crcok);
typedef void (*smp_init_handler_t)(u8 *p);
typedef void (*smp_enc_handler_t)(u8 *p);

typedef void (*pair_init_handler_t)(u8 *p);
typedef void (*pair_handler_t)();
typedef u8 *  (*pair_proc_t) ();
typedef void (*user_task_handler_t)(void);

int 	blt_fifo_empty ();
u8 *	push_pkt_smp (int type);
u8 * 	smp_send_info ();
void	blt_smp_func_init ();
u8 *	smp_get_adv_pkt ();
// type 0:  just works.   1:  passkey
// passkey:   0 ~ 999999.  valid iff  type==passkey
void blt_smp_set_pairing_type(u8 type, u32 passkey);

u16 blt_get_sdk_version();


//slave paried with master OK, return 1; otherwise return 0
int is_slave_bonded(void);

//return 1 for OK, 0 for ERR(no bond master addr)
int blt_get_bonded_address(addr_t * adr);

//return 1 for OK, 0 for ERR(no paired key)
//rand: 8 byte   ediv: 2 byte ltk: 16 byte
int blt_get_smp_key(u8* rand,u8 *ediv, u8 *ltk);


//erase all bond info(master addr/key)
void erase_bond_info(void);

#if (MCU_CORE_TYPE == MCU_CORE_17H26)
void	blt_brx_sleep (u32 app_wakeup_tick);
#else
void	blt_brx_sleep ();
#endif

