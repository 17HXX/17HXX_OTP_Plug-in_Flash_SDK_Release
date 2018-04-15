#include "tl_audio.h"
#include "../../proj_lib/blt_ll/trace.h"

#ifndef		TL_MIC_32K_FIR_16K
#define		TL_MIC_32K_FIR_16K		0
#endif

int md_long =0;
int md_short =0;
int md_im =0;
int md_noise = 0;
int md_gain = 256;

static const signed char idxtbl[] = { -1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8};
static const unsigned short steptbl[] = {
 7,  8,  9,  10,  11,  12,  13,  14,  16,  17,
 19,  21,  23,  25,  28,  31,  34,  37,  41,  45,
 50,  55,  60,  66,  73,  80,  88,  97,  107, 118,
 130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
 337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
 876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066,
 2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
 5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
    15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767   };

//////////////////////////////////////////////////////////
//	for 8266: input 128-word, output 80-byte
//////////////////////////////////////////////////////////
void pcm_to_adpcm (signed short *ps, int len, signed short *pd)
{
	int i, j;
	unsigned short code, code16;
	int predict_idx = 1;
	code = 0;

	for (i=0; i<8; i++) {
		*pd++ = ps[i];   //copy first 8 samples
	}
	int predict = ps[0];
	for (i=1; i<len; i++) {

		s16 di = ps[i];
		int step = steptbl[predict_idx];
		int diff = di - predict;

		if (diff >=0 ) {
			code = 0;
		}
		else {
			diff = -diff;
			code = 8;
		}

		int diffq = step >> 3;

		for (j=4; j>0; j=j>>1) {
			if( diff >= step) {
				diff = diff - step;
				diffq = diffq + step;
				code = code + j;
			}
			step = step >> 1;
		}

		code16 = (code16 >> 4) | (code << 12);
		if ( (i&3) == 3) {
			*pd++ = code16;
		}

		if(code >= 8) {
			predict = predict - diffq;
		}
		else {
			predict = predict + diffq;
		}

		if (predict > 32767) {
			predict = 32767;
		}
		else if (predict < -32767) {
			predict = -32767;
		}

		predict_idx = predict_idx + idxtbl[code];
		if(predict_idx < 0) {
			predict_idx = 0;
		}
		else if(predict_idx > 88) {
			predict_idx = 88;
		}
	}
}

#define				NUM_OF_ORIG_SAMPLE				2

void mic_to_adpcm (signed short *ps, int len, signed short *pd)
{
	int i, j;
	unsigned short code, code16;
	int predict_idx = 1;
	code = 0;

	for (i=0; i<NUM_OF_ORIG_SAMPLE; i++) {
		*pd++ = ps[i];   //copy first 5 samples
	}
	int predict = ps[0];
	for (i=1; i<len; i++) {

		s16 di = ps[i];
		int step = steptbl[predict_idx];
		int diff = di - predict;

		if (diff >=0 ) {
			code = 0;
		}
		else {
			diff = -diff;
			code = 8;
		}

		int diffq = step >> 3;

		for (j=4; j>0; j=j>>1) {
			if( diff >= step) {
				diff = diff - step;
				diffq = diffq + step;
				code = code + j;
			}
			step = step >> 1;
		}

		code16 = (code16 >> 4) | (code << 12);
		if ( (i&3) == 3) {
			*pd++ = code16;
		}

		if(code >= 8) {
			predict = predict - diffq;
		}
		else {
			predict = predict + diffq;
		}

		if (predict > 32767) {
			predict = 32767;
		}
		else if (predict < -32767) {
			predict = -32767;
		}

		predict_idx = predict_idx + idxtbl[code];
		if(predict_idx < 0) {
			predict_idx = 0;
		}
		else if(predict_idx > 88) {
			predict_idx = 88;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////
//	256-samples split into 2
/////////////////////////////////////////////////////////////////////////////////
void mic_to_adpcm_split (signed short *ps, int len, signed short *pds, int start)
{
	int i, j;
	unsigned short code, code16;
	static int predict_idx = 1;
	code = 0;
	static signed short *pd;
	static int predict;

	//byte2,byte1: predict;  byte3: predict_idx; byte4:adpcm data len
	if (start)
	{
		pd = pds;
		*pd++ = predict;
		* (((signed char *)pds) + 2)= predict_idx;
		* (((unsigned char *)pds) + 3)= (ADPCM_PACKET_LEN - 4);
		pd++;
	}

	//byte5- byte128: 124 byte(62 sample) adpcm data
	for (i=0; i<len; i++) {

		s16 di = ps[TL_MIC_32K_FIR_16K ? i * 2 : i];
		int step = steptbl[predict_idx];
		int diff = di - predict;

		if (diff >=0 ) {
			code = 0;
		}
		else {
			diff = -diff;
			code = 8;
		}

		int diffq = step >> 3;

		for (j=4; j>0; j=j>>1) {
			if( diff >= step) {
				diff = diff - step;
				diffq = diffq + step;
				code = code + j;
			}
			step = step >> 1;
		}

		code16 = (code16 >> 4) | (code << 12);
		if ( (i&3) == 3) {
			*pd++ = code16;
		}

		if(code >= 8) {
			predict = predict - diffq;
		}
		else {
			predict = predict + diffq;
		}

		if (predict > 32767) {
			predict = 32767;
		}
		else if (predict < -32767) {
			predict = -32767;
		}

		predict_idx = predict_idx + idxtbl[code];
		if(predict_idx < 0) {
			predict_idx = 0;
		}
		else if(predict_idx > 88) {
			predict_idx = 88;
		}
	}
}

////////////////////////////////////////////////////////////////////
/*  name ADPCM to pcm
    signed short *ps -> pointer to the adpcm source buffer
    signed short *pd -> pointer to the pcm destination buffer
    int len          -> decorded size
*/
void adpcm_to_pcm (signed short *ps, signed short *pd, int len){
	int i;

	//byte2,byte1: predict;  byte3: predict_idx; byte4:adpcm data len
	int predict = ps[0];
	int predict_idx = ps[1] & 0xff;
	int adpcm_len = (ps[1]>>8) & 0xff;

	unsigned char *pcode = (unsigned char *) (ps + NUM_OF_ORIG_SAMPLE);

	unsigned char code;
	code = *pcode ++;

	//byte5- byte128: 124 byte(62 sample) adpcm data
	for (i=0; i<len; i++) {

		if (1) {
			int step = steptbl[predict_idx];

			int diffq = step >> 3;

			if (code & 4) {
				diffq = diffq + step;
			}
			step = step >> 1;
			if (code & 2) {
				diffq = diffq + step;
			}
			step = step >> 1;
			if (code & 1) {
				diffq = diffq + step;
			}

			if (code & 8) {
				predict = predict - diffq;
			}
			else {
				predict = predict + diffq;
			}

			if (predict > 32767) {
				predict = 32767;
			}
			else if (predict < -32767) {
				predict = -32767;
			}

			predict_idx = predict_idx + idxtbl[code & 15];

			if(predict_idx < 0) {
				predict_idx = 0;
			}
			else if(predict_idx > 88) {
				predict_idx = 88;
			}

			if (i&1) {
				code = *pcode ++;
			}
			else {
				code = code >> 4;
			}
		}

		if (0 && i < NUM_OF_ORIG_SAMPLE) {
			*pd++ = ps[i];
		}
		else {
			*pd++ = predict;
		}
	}
}

#ifndef		ADPCM_PACKET_LEN
#define		ADPCM_PACKET_LEN					128
#endif

#if		TL_MIC_BUFFER_SIZE

#define	BUFFER_PACKET_SIZE		((ADPCM_PACKET_LEN >> 2) * TL_MIC_PACKET_BUFFER_NUM)

int		buffer_mic_enc[BUFFER_PACKET_SIZE];
u8		buffer_mic_pkt_wptr;
u8		buffer_mic_pkt_rptr;

u32		adb_t2;


#define TL_NOISE_SUPRESSION_ENABLE 0 // TODO : too much calculation can have packet drop

void	proc_mic_encoder (void)
{
	static u16	buffer_mic_rptr;
	u16 mic_wptr = reg_audio_wr_ptr;
	u16 l = ((mic_wptr<<1) >= buffer_mic_rptr) ? ((mic_wptr<<1) - buffer_mic_rptr) : 0xffff;

	if (l >=(TL_MIC_BUFFER_SIZE>>2)) {
		log_task_begin (TR_T_adpcm);
		s16 *ps = buffer_mic + buffer_mic_rptr;
#if 	TL_NOISE_SUPRESSION_ENABLE
        // for FIR adc sample data, only half part data are effective
		for (int i=0; i<TL_MIC_ADPCM_UNIT_SIZE*2; i++) {
			ps[i] = noise_supression (ps[i]);
        }
#endif

		mic_to_adpcm_split (	ps,	TL_MIC_ADPCM_UNIT_SIZE,
						(s16 *)(buffer_mic_enc + (ADPCM_PACKET_LEN>>2) *
						(buffer_mic_pkt_wptr & (TL_MIC_PACKET_BUFFER_NUM - 1))), 1);

		buffer_mic_rptr = buffer_mic_rptr ? 0 : (TL_MIC_BUFFER_SIZE>>2);
		buffer_mic_pkt_wptr++;
		int pkts = (buffer_mic_pkt_wptr - buffer_mic_pkt_rptr) & (TL_MIC_PACKET_BUFFER_NUM*2-1);
		if (pkts > TL_MIC_PACKET_BUFFER_NUM) {
			buffer_mic_pkt_rptr++;
			log_event (TR_T_adpcm_enc_overflow);
		}
		log_task_end (TR_T_adpcm);
	}
}

int		mic_encoder_data_ready (int *pd)
{
//	if ((buffer_mic_pkt_rptr & 0x7f) == (buffer_mic_pkt_wptr >> 1)) {
//		return 0;
//	}
//
//	int *ps = buffer_mic_enc + (ADPCM_PACKET_LEN>>2) *
//			(buffer_mic_pkt_rptr & (TL_MIC_PACKET_BUFFER_NUM - 1));
//	for (int i=0; i<(ADPCM_PACKET_LEN>>2); i++) {
//		*pd++ = *ps++;
//	}
//	buffer_mic_pkt_rptr++;
//	return ADPCM_PACKET_LEN;
}

int	*	mic_encoder_data_buffer ()
{
	if (buffer_mic_pkt_rptr == buffer_mic_pkt_wptr) {
			return 0;
	}

	int *ps = buffer_mic_enc + (ADPCM_PACKET_LEN>>2) *
			(buffer_mic_pkt_rptr & (TL_MIC_PACKET_BUFFER_NUM - 1));

	buffer_mic_pkt_rptr++;

	return ps;
}

#if 0
void	proc_mic_encoder (void)
{
	u32 t = clock_time ();
	static u16	buffer_mic_rptr;
	u16 mic_wptr = reg_audio_wr_ptr;
	u16 l = ((mic_wptr<<1) - buffer_mic_rptr) & ((TL_MIC_BUFFER_SIZE>>1) - 1);
	if (l >= 128) {
		log_task_begin (TR_T_adpcm);
		s16 *ps = buffer_mic + buffer_mic_rptr;

#if 	TL_NOISE_SUPRESSION_ENABLE
		for (int i=0; i<128; i++) {
			ps[i] = noise_supression (ps[i] >> 16) << 16;
		}
#endif
		mic_to_adpcm_split (	ps,	128,
						(s16 *)(buffer_mic_enc + (ADPCM_PACKET_LEN>>2) *
						((buffer_mic_pkt_wptr>>1) & (TL_MIC_PACKET_BUFFER_NUM - 1))), !(buffer_mic_pkt_wptr&1));

		buffer_mic_rptr = (buffer_mic_rptr + 128) & ((TL_MIC_BUFFER_SIZE>>1) - 1);
		buffer_mic_pkt_wptr++;
		int pkts = ((buffer_mic_pkt_wptr>>1) - buffer_mic_pkt_rptr) & (TL_MIC_PACKET_BUFFER_NUM*2-1);
		if (pkts > TL_MIC_PACKET_BUFFER_NUM) {
			buffer_mic_pkt_rptr++;
			log_event (TR_T_adpcm_enc_overflow);
		}
		adb_t2 = clock_time() - t;
		log_task_end (TR_T_adpcm);
	}
}

int		mic_encoder_data_ready (int *pd)
{
	if ((buffer_mic_pkt_rptr & 0x7f) == (buffer_mic_pkt_wptr >> 1)) {
		return 0;
	}

	int *ps = buffer_mic_enc + (ADPCM_PACKET_LEN>>2) *
			(buffer_mic_pkt_rptr & (TL_MIC_PACKET_BUFFER_NUM - 1));
	for (int i=0; i<(ADPCM_PACKET_LEN>>2); i++) {
		*pd++ = *ps++;
	}
	buffer_mic_pkt_rptr++;
	return ADPCM_PACKET_LEN;
}

int	*	mic_encoder_data_buffer ()
{
	if ((buffer_mic_pkt_rptr & 0x7f) == (buffer_mic_pkt_wptr >> 1)) {
			return 0;
	}

	int *ps = buffer_mic_enc + (ADPCM_PACKET_LEN>>2) *
			(buffer_mic_pkt_rptr & (TL_MIC_PACKET_BUFFER_NUM - 1));

	buffer_mic_pkt_rptr++;

	return ps;
}
#endif

#endif

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
//	hardware dependent
/////////////////////////////////////////////////////////////
#if TL_SDM_BUFFER_SIZE

int		buffer_sdm_wptr;
int		buffer_sdm_dec[ADPCM_PACKET_LEN];

void adpcm_to_sdm (signed short *ps, int len){
	int i;
	int predict_idx = 1;
	int predict;

	unsigned char *pcode = (unsigned char *) (ps + 12);
	unsigned char code;

	for (i=0; i<len; i++) {

		if (i) {
			int step = steptbl[predict_idx];

			int diffq = step >> 3;

			if (code & 4) {
				diffq = diffq + step;
			}
			step = step >> 1;
			if (code & 2) {
				diffq = diffq + step;
			}
			step = step >> 1;
			if (code & 1) {
				diffq = diffq + step;
			}

			if (code & 8) {
				predict = predict - diffq;
			}
			else {
				predict = predict + diffq;
			}

			if (predict > 32767) {
				predict = 32767;
			}
			else if (predict < -32767) {
				predict = -32767;
			}

			predict_idx = predict_idx + idxtbl[code & 15];

			if(predict_idx < 0) {
				predict_idx = 0;
			}
			else if(predict_idx > 88) {
				predict_idx = 88;
			}

			if (i&1) {
				code = *pcode ++;
			}
			else {
				code = code >> 4;
			}
		}
		else {
			code = *pcode++ >> 4;
			predict = ps[0];
		}

		int t2;
		if (i < 8) {
			t2 = ps[i];
		}
		else {
			t2 = predict;
		}
		//* ((s16 *) (buffer_sdm + buffer_sdm_wptr)) = t2;
		buffer_sdm[buffer_sdm_wptr] = (t2<<0);
		buffer_sdm_wptr = (buffer_sdm_wptr + 1) & ((TL_SDM_BUFFER_SIZE>>1) - 1);
	}
}

void pcm_to_sdm (signed short *ps, int len){
	for (int i=0; i<len; i++) {
		buffer_sdm[buffer_sdm_wptr] = ps[i];
		buffer_sdm_wptr = (buffer_sdm_wptr + 1) & ((TL_SDM_BUFFER_SIZE>>1) - 1);
	}
}

void silence_to_sdm (void){
	for (int i=0; i<TL_SDM_BUFFER_SIZE>>1; i++) {
		* ((s16 *) (buffer_sdm + i)) = 0;
	}
}

int  sdm_decode_ready (int nbyte_to_decode)
{
	u16 sdm_rptr = reg_aud_rptr; //get_sdm_rd_ptr ();
	u16 num = ((buffer_sdm_wptr>>1) - sdm_rptr) & ((TL_SDM_BUFFER_SIZE>>2) - 1);
	return ((nbyte_to_decode>>2) + num) < (TL_SDM_BUFFER_SIZE >> 2);
}

int   sdm_word_in_buffer ()
{
	u16 num = ((buffer_sdm_wptr>>1) - reg_aud_rptr) & ((TL_SDM_BUFFER_SIZE>>2) - 1);
}

void  sdm_decode_rate (int step, int adj)
{
	u16 sdm_rptr = reg_aud_rptr; //get_sdm_rd_ptr ();
	u16 num = ((buffer_sdm_wptr>>1) - sdm_rptr) & ((TL_SDM_BUFFER_SIZE>>2) - 1);

	if (num > (TL_SDM_BUFFER_SIZE*3>>5)) {
		reg_ascl_step = step + adj;
	}
	else if (num < (TL_SDM_BUFFER_SIZE>>4)) {
		reg_ascl_step = step - adj;
	}
}


void proc_sdm_decoder (void)
{

}

int  sdm_decode_data (int *ps, int nbyte)
{

}

#endif

