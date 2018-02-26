
#ifndef TRACE_H_
#define TRACE_H_


#define TR_T_ll_rx	            	0
#define TR_T_ll_brx	            	1
#define TR_T_ll_sync            	2
#define TR_T_ll_cmd_done           	3
#define TR_T_ll_first_timeout      	4
#define TR_T_ll_timeout            	5
#define TR_T_ll_miss            	6
#define TR_T_ll_adv	            	7
#define TR_T_ll_chn_map   	     	8
#define TR_T_ll_chn_timing      	9
#define TR_T_ll_push_tx         	10
#define TR_T_ll_push_tx_ok       	11

#define TR_T_user_task		        13
#define TR_T_adpcm		        	14
#define TR_T_adpcm_enc_overflow    	15
#define TR_T_adpcm2sdm    			16

#define TR_T_audio					17
#define TR_T_irq_rx					18
#define TR_T_irq_cmddone			19
#define TR_T_irq_rx_tmt				20
#define TR_T_irq_rx_fsttmt			21


#define TR_T_ota_version			22
#define TR_T_ota_start				23
#define TR_T_ota_end				24
#define TR_T_ota_err				25
#define TR_T_ota_data				26

#define TR_T_ble_time				27


#define TR_T_master_rx				28
#define TR_T_master_tx				29
#define TR_T_master_btx				30
#define TR_T_master_start			31
#define TR_T_master_update			32
#define TR_T_master_update_req		33


#define TR_24_ll_chn            	0
#define TR_24_brx_dbg            	1
#define TR_24_brx_clock            	2
#define TR_24_brx_timeout          	3
#define	TR_24_brx_conn_tick			4

#define	TR_24_fifo_pre				5
#define	TR_24_fifo_post				6

#define TR_24_ota_adr				7

#endif
