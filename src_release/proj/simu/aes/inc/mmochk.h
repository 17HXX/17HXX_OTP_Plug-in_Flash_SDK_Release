

#ifndef _MMOCHK_H
#define _MMOCHK_H

#pragma pack(1)

/* ====== Typedefs ====== */


enum
{
  NO_MMO_ERROR = 0,

  /* keep the following in alphabetical order */
  MMODECR_ERROR,
  MMOENCR_ERROR,
  MMOKEY_ERROR,
  MMOMALLOC_ERROR,
};


typedef struct mmo_info {
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
    uint8_t  result[16];
} mmo_info_t;

void mmoCheck(mmo_info_t* pMMO);


#endif /* _MMOCHK_H */
