
/*
 ---------------------------------------------------------------------------
 Copyright (c) 1998-2006, Brian Gladman, Worcester, UK. All rights reserved.

 LICENSE TERMS

 The free distribution and use of this software in both source and binary
 form is allowed (with or without changes) provided that:

   1. distributions of this source code include the above copyright
      notice, this list of conditions and the following disclaimer;

   2. distributions in binary form include the above copyright
      notice, this list of conditions and the following disclaimer
      in the documentation and/or other associated materials;

   3. the copyright holder's name is not used to endorse products
      built using this software without specific written permission.

 DISCLAIMER

 This software is provided 'as is' with no explicit or implied warranties
 in respect of its properties, including, but not limited to, correctness
 and/or fitness for purpose.
 ---------------------------------------------------------------------------
 Issue Date: 20/12/2007

 My thanks to Colin Sinclair for finding an error and suggesting a number
 of improvements to this code
*/

#include <stdio.h>
#include "../../common/types.h"
#include "inc/ecb.h"
#include "inc/mode_hdr.h"
#include "inc/debug.h"

#if defined(__cplusplus)
extern "C"
{
#endif

#define BLOCK_SIZE      AES_BLOCK_SIZE      /* block length                */
#define BLK_ADR_MASK    (BLOCK_SIZE - 1)    /* mask for 'in block' address */
#define INIT_STATE      10
#define AUTH_STATE      11
#define MSG_STATE       12

#define MAX_NONCE_LEN   12

#define ctr_len(x)      (((*(u8*)(x)) & 0x07) + 1)

#define clr_ctr(x,l)    memset((u8*)(x) + BLOCK_SIZE - (l), 0, (l))

#define set_ctr(x,v)                                \
  {                                                 \
    u8 *_p = (u8*)(x) + BLOCK_SIZE;       \
    length_t _t = (v), _l = ctr_len(x);             \
    do                                              \
    {                                               \
      *--_p = (u8)_t; _t >>= 8;                \
    } while (--_l);                                 \
  }


#define inc_ctr(x)                                  \
  {                                                 \
    u8 *_p = (u8*)(x) + BLOCK_SIZE;       \
    length_t _l = ctr_len(x);                       \
    while (_l-- && ++(*--_p) == 0) ;                \
  }


#ifdef LONG_MESSAGES

#  define mlen_len(x)                     \
    (((x) & 0xff00000000000000ll) ? 7 :     \
     ((x) & 0xffff000000000000ll) ? 6 :     \
     ((x) & 0xffffff0000000000ll) ? 5 :     \
     ((x) & 0xffffffff00000000ll) ? 4 :     \
     ((x) & 0xffffffffff000000ll) ? 3 :     \
     ((x) & 0xffffffffffff0000ll) ? 2 : 1)

#else
#  define mlen_len(x) (((x) & 0xff000000) ? 3 : ((x) & 0xffff0000) ? 2 : 1)
#endif
extern int j;



/*****************************************************************************/

ret_type ecb_init_and_enkey(                 /* initialise mode and set key */
            const unsigned char key[],     /* the key value               */
            unsigned long key_len,         /* and its length in bytes     */
            ecb_ctx ctx[1])                /* the mode context            */
{
    ctx->state = RETURN_GOOD;
    if ((key_len != 16) && (key_len != 24) && (key_len != 32))
    {
        ctx->state = ECB_BAD_KEY;
    }
    aes_encrypt_key(key, (int)key_len, ctx->aes);
    return RETURN_GOOD;
}

ret_type ecb_init_and_dekey(                 /* initialise mode and set key */
            const unsigned char key[],     /* the key value               */
            unsigned long key_len,         /* and its length in bytes     */
            ecb_ctx ctx[1])                /* the mode context            */
{
    ctx->state = RETURN_GOOD;
    if ((key_len != 16) && (key_len != 24) && (key_len != 32))
    {
        ctx->state = ECB_BAD_KEY;
    }
    aes_decrypt_key(key, (int)key_len, (aes_decrypt_ctx*)&ctx->aes);
    return RETURN_GOOD;
}


/*****************************************************************************/

ret_type ecb_crypt_message(              /* encrypt an entire message */
            length_t msg_len,              /* and its length in bytes   */
            unsigned char msg[],           /* the message buffer        */
            ecb_ctx ctx[1])                /* the mode context          */
{
    ret_type retVal = RETURN_GOOD;
    u32 cnt = 0;
    u32 count = 0;


    ctx->cnt = 0;
    ctx->txt_acnt = 0;
    ctx->msg_len = msg_len;

    while (cnt + BLOCK_SIZE <= msg_len) {

        memcpy(UI8_PTR(ctx->ecb_buf), msg+cnt, BLOCK_SIZE);

        /* encrypt the ecb block    */
        aes_encrypt(UI8_PTR(ctx->ecb_buf), msg+cnt, ctx->aes);

        printf("Block %d:\n", count++);
        for (j=0;j<16;j++) {
            printf("%x ", UI8_PTR(ctx->ecb_buf)[j]);
        }
        printf("\n");

        cnt += BLOCK_SIZE;
    }

    if (cnt < msg_len) {
        memset(UI8_PTR(ctx->ecb_buf), 0, BLOCK_SIZE);
        memcpy(UI8_PTR(ctx->ecb_buf), msg+cnt, msg_len - cnt);
        aes_encrypt(UI8_PTR(ctx->ecb_buf), msg+cnt, ctx->aes);

        printf("Block %d:\n", count);
        for (j=0;j<16;j++) {
            printf("%x ", UI8_PTR(ctx->ecb_buf)[j]);
        }
        printf("\n");
    }


    return retVal;
}

/*****************************************************************************/

ret_type ecb_uncrypt_message(              /* encrypt an entire message */
            length_t msg_len,              /* and its length in bytes   */
            unsigned char msg[],           /* the message buffer        */
            ecb_ctx ctx[1])                /* the mode context          */
{
    ret_type retVal = RETURN_GOOD;
    u32 cnt = 0;
    u32 count = 0;


    ctx->cnt = 0;
    ctx->txt_acnt = 0;
    ctx->msg_len = msg_len;

    while (cnt + BLOCK_SIZE <= msg_len) {

        memcpy(UI8_PTR(ctx->ecb_buf), msg+cnt, BLOCK_SIZE);

        /* decrypt the ecb block    */
        aes_decrypt(UI8_PTR(ctx->ecb_buf), msg+cnt, (aes_decrypt_ctx*)&ctx->aes);

        printf("Block %d:\n", count++);
        for (j=0;j<16;j++) {
            printf("%x ", UI8_PTR(ctx->ecb_buf)[j]);
        }
        printf("\n");

        cnt += BLOCK_SIZE;
    }

    if (cnt < msg_len) {
        memset(UI8_PTR(ctx->ecb_buf), 0, BLOCK_SIZE);
        memcpy(UI8_PTR(ctx->ecb_buf), msg+cnt, msg_len - cnt);
        aes_decrypt(UI8_PTR(ctx->ecb_buf), msg+cnt, (aes_decrypt_ctx*)&ctx->aes);

        printf("Block %d:\n", count);
        for (j=0;j<16;j++) {
            printf("%x ", UI8_PTR(ctx->ecb_buf)[j]);
        }
        printf("\n");
    }


    return retVal;
}

/*****************************************************************************/

ret_type ecb_encrypt_message(              /* encrypt an entire message */
            length_t msg_len,              /* and its length in bytes   */
            unsigned char msg[],           /* the message buffer        */
            ecb_ctx ctx[1])                /* the mode context          */
{
    ret_type retVal = RETURN_GOOD;

    do {
        if (msg_len == 0) {
            retVal = ECB_MSG_LENGTH_ERROR;
            break;
        }

        retVal = ecb_crypt_message(msg_len, msg, ctx);

    } while(0);

    return retVal;
}

/*****************************************************************************/

ret_type ecb_decrypt_message(              /* encrypt an entire message */
            length_t msg_len,              /* and its length in bytes   */
            unsigned char msg[],           /* the message buffer        */
            ecb_ctx ctx[1])                /* the mode context          */
{
    ret_type retVal = RETURN_GOOD;

    do {
        if (msg_len == 0) {
            retVal = ECB_MSG_LENGTH_ERROR;
            break;
        }

        retVal = ecb_uncrypt_message(msg_len, msg, ctx);

    } while(0);

    return retVal;
}

#if defined(__cplusplus)
}
#endif
