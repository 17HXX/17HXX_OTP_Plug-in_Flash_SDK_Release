#pragma  once

u8 aes_ccm_encryption(u8 *key, u8 *iv, u8 *aStr,u8 *mic, u8 mStrLen, u8 *mStr, u8 *result);

u8 aes_ccm_decryption(u8 *key, u8 *iv, u8 *aStr, u8 *mic, u8 mStrLen, u8 *mStr, u8 *result);

u8 aes_ecb_encryption(u8 *key, u8 mStrLen, u8 *mStr, u8 *result);