#pragma  once

#define AES_BLOCK_SIZE     16



enum {
    AES_SUCC = SUCCESS,
    AES_NO_BUF,               
    AES_FAIL,
};


struct CCM_FLAGS_TAG {
    union {
        struct {
            u8 L : 3;
            u8 M : 3;
            u8 aData :1;
            u8 reserved :1;            
        } bf;
        u8 val;
    };
};

typedef struct CCM_FLAGS_TAG ccm_flags_t;

enum AES_OPT {
    AES_ENCRYPTION = 0,
    AES_DECRYPTION,
};

typedef struct {
    union {
        u8 A[AES_BLOCK_SIZE];
        u8 B[AES_BLOCK_SIZE];
    } bf;
    
    u8 tmpResult[AES_BLOCK_SIZE];
    u8 newAstr[AES_BLOCK_SIZE];
} aes_enc_t;

u8 aes_ccmAuthTran(u8 *iv, u8 *mStr, u16 mStrLen, u8 aStr, u8 *result);
u8 aes_initKey(u8 *key);
u8 aes_encrypt(u8 *key, u8 *data, u8 *result);
u8 aes_ll_encryption(u8 *key, u8 *plaintext, u8 *result);
void aes_ll_c1(u8 * key, u8 * r, u8 *p1, u8 *p2, u8 * result);
void aes_ll_s1(u8 * key, u8 * r1, u8 * r2, u8 * result);
void aes_ll_ccm_encryption_init (u8 *ltk, u8 *skdm, u8 *skds, u8 *ivm, u8 *ivs);
void aes_ll_ccm_encryption(u8 *pkt, int master);
int aes_ll_ccm_decryption(u8 *pkt, int master);


