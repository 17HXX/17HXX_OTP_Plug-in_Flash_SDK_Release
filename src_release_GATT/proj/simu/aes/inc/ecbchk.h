


#ifndef _ECBCHK_H
#define _ECBCHK_H

#pragma pack(1)

/* ====== Typedefs ====== */


enum
{
  NO_ECB_ERROR = 0,

  /* keep the following in alphabetical order */
  ECBDECR_ERROR,
  ECBENCR_ERROR,
  ECBKEY_ERROR,
  ECBMALLOC_ERROR,
};


typedef struct ecb_info {
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
} ecb_info_t;

void ecbCheck(ecb_info_t* pECB);


#endif /* _MMOCHK_H */