#ifndef _CBCCHK_H
#define _CBCCHK_H

#pragma pack(1)

/* ====== Typedefs ====== */


enum
{
  NO_CBC_ERROR = 0,

  /* keep the following in alphabetical order */
  CBCDECR_ERROR,
  CBCENCR_ERROR,
  CBCKEY_ERROR,
  CBCMALLOC_ERROR,
};


typedef struct cbc_info {
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
} cbc_info_t;

void cbcCheck(cbc_info_t *pCBC);


#endif /* _CBCCHK_H */
