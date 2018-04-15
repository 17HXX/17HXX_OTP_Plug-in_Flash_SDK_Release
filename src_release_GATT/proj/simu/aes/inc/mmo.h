
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

 This code implements the CCM combined encryption and authentication mode
 specified by Doug Whiting, Russ Housley and Niels Ferguson.  Relevant
 documents are:

    NIST Special Publication 800-38C: DRAFT Recommendation for Block Cipher
    Modes of Operation: The CCM Mode For AUthentication and Confidentiality.
    September 2003.

    IEEE Std 802.11i/D5.0, August 2003.   Draft Amendment to standard for
    Telecommunications and Information Exchange Between Systems - LAN/MAN
    Specific Requirements - Part 11: Wireless Medium Access Control (MAC)
    and physical layer (PHY) specifications:  Medium Access Control (MAC)
    Security Enhancements

 The length of the mesaage data must be less than 2^32 bytes unless the
 define LONG_MESSAGES is set.  NOTE that this implementation is not fully
 compliant with the CCM specification because, if an authentication error
 is detected when the last block is processed, blocks processed earlier will
 already have been returned to the caller. This violates the specification
 but is costly to avoid for large messages that cannot be memory resident as
 a single block. In this case the message would have to be processed twice
 so that the final authentication value can be checked before the output is
 provided on a second pass.

 My thanks go to Erik Andersen <andersen@codepoet.org> for finding a bug in
 an earlier relaease of this code. I am also grateful for the comments made
 by James Weatherall <jnw@realvnc.com> that led to several API changes.
*/

#ifndef _MMO_H
#define _MMO_H

#if 1
#  define LONG_MESSAGES
#endif

/*  This define sets the memory alignment that will be used for fast move
    and xor operations on buffers when the alignment matches this value.
*/
#if !defined( UNIT_BITS )
#  if 1
#    define UNIT_BITS 64
#  elif 0
#    define UNIT_BITS 32
#  else
#    define UNIT_BITS  8
#  endif
#endif

#if ( UNIT_BITS == 64 || defined( LONG_MESSAGES ) ) && !defined( NEED_UINT_64T )
#  define NEED_UINT_64T
#endif

#include "aes.h"

#if defined(__cplusplus)
extern "C"
{
#endif

/*  After encryption or decryption operations the return value of
    'compute tag' will be one of the values RETURN_GOOD, RETURN_WARN
    or RETURN_ERROR, the latter indicating an error. A return value
    RETURN_GOOD indicates that both encryption and authentication
    have taken place and resulted in the returned tag value. If
    the returned value is RETURN_WARN, the tag value is the result
    of authentication alone without encryption (CCM) or decryption
    (GCM and EAX).
*/
#ifndef RETURN_GOOD
# define RETURN_WARN      1
# define RETURN_GOOD      0
# define RETURN_ERROR    -1
#endif

#define MMO_BAD_KEY               -2
#define MMO_BAD_AUTH_FIELD_LENGTH -3
#define MMO_BAD_NONCE_LENGTH      -4
#define MMO_BAD_AUTH_CALL         -5
#define MMO_AUTH_LENGTH_ERROR     -6
#define MMO_MSG_LENGTH_ERROR      -7
#define MMO_MALLOC_ERROR          -8

//typedef int ret_type;
UNIT_TYPEDEF(mmo_unit_t, UNIT_BITS);
BUFR_TYPEDEF(mmo_buf_t, UNIT_BITS, AES_BLOCK_SIZE);

#define MMO_BLOCK_SIZE  AES_BLOCK_SIZE

/* The CCM context  */

/*
#if defined( LONG_MESSAGES )
  typedef uint_64t length_t;
#else
  typedef uint_32t length_t;
#endif
*/

typedef struct
{
    mmo_buf_t   hash_val;                       /* hash value                   */
    mmo_buf_t   mmo_buf;                        /* running CBC value            */
    mmo_buf_t   ipad;
    mmo_buf_t   opad;
    mmo_buf_t   key1;
    mmo_buf_t   key2;
    uint_8t     *mmo_tempBuf;
    length_t    mmo_tempBufLen;
    aes_encrypt_ctx aes[1];                     /* AES context                  */
    length_t    msg_len;                        /* message data length          */
    length_t    cnt;                            /* position counter             */
    length_t    txt_acnt;                       /* position counter             */
    uint_32t    iv_len;                         /* the nonce length             */
    u32    state;                          /* algorithm state/error value  */
} mmo_ctx;

/* The following calls handle mode initialisation, keying and completion        */

u32 mmo_init_and_key(                      /* initialise mode and set key  */
            const unsigned char key[],          /* the key value                */
            unsigned long key_len,              /* and its length in bytes      */
            mmo_ctx ctx[1]);                    /* the mode context             */

/* The following calls handle complete messages in memory in a single operation */


u32 mmo_encrypt_message(              /* encrypt an entire message */
            length_t msg_len,              /* and its length in bytes   */
            unsigned char msg[],           /* the message buffer        */
            mmo_ctx ctx[1],
            u8 result[]);               /* the mode context          */


                                    /* RETURN_GOOD is returned if the input tag */
                                    /* matches that for the decrypted message   */
u32 mmo_decrypt_message(              /* encrypt an entire message */
            length_t msg_len,              /* and its length in bytes   */
            unsigned char msg[],           /* the message buffer        */
            mmo_ctx ctx[1]);               /* the mode context          */




#if defined(__cplusplus)
}
#endif

#endif /* _MMO_H */
