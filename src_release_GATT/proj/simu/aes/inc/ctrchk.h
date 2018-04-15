
#ifndef _CTRCHK_H
#define _CTRCHK_H

#pragma pack(1)

#include "types.h"

/* ====== Typedefs ====== */


enum
{
  NO_CTR_ERROR = 0,

  /* keep the following in alphabetical order */
  CTRDECR_ERROR,
  CTRENCR_ERROR,
  CTRKEY_ERROR,
  CTRMALLOC_ERROR,
};


typedef struct ctr_info {
    uint8_t  fEncryption;
    uint8_t  micLen;
    uint8_t  keyLen;
    uint8_t  nonceLen;
    uint32_t ahdrLen;
    uint32_t mstrLen;
    uint8_t  *key;
    uint8_t  *nonce;
    uint8_t  *aHdr;
    uint8_t  *mStr;
    uint8_t  *micE;
    uint8_t  *micD;
    uint8_t  counterMod;  /* used in CTR mode */
    uint32_t initCounter; /* used in CTR mode */
} ctr_info_t;

void ctrCheck(ctr_info_t* pCTR);


#endif /* _CTRCHK_H */
