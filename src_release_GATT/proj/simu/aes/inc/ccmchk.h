#ifndef _CCMCHK_H
#define _CCMCHK_H

#pragma pack(1)

/* ====== Typedefs ====== */

typedef enum
{
  NO_CCM_ERROR = 0,

  /* keep the following in alphabetical order */
  CCMDECR_ERROR,
  CCMENCR_ERROR,
  CCMKEY_ERROR,
  MALLOC_ERROR,
} t_errVal;


typedef struct ccm_info {
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
} ccm_info_t;

void ccmCheck(ccm_info_t* pCCM);


#endif /* _GETMIC_H */

