
/* ************************************************************
 * This simple test application encrypts a message and then
 * decrypts it right back, and prints the calculated MIC.
 * The Key, Nonce, Header etc. used are whatever is assigned
 * to the variables "Key", "Nnc", "Hdr" etc. via conditional
 * compilation.
 *
 * Usage: getmic
 *
 * ***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <memory.h>

#include "ecb.h"
#include "debug.h"
#include "ecbchk.h"


void ecbCheck(ecb_info_t  *pECB)
{
    ecb_ctx     ctx[1];
    uint8_t     errVal = NO_ECB_ERROR;
    ret_type    retVal = RETURN_GOOD;


    dbgp_app("-------------------Enter ECB Check------------------\n\n");

    dbgp_app("Key Length: %d\n", pECB->keyLen);

    if (pECB->keyLen) {
        outputHexStr("Key:\n\r", pECB->key, pECB->keyLen);
    } else {
        printf("\n   no key to use ...\n");
    }

    /* First encrypt */
    if (pECB->fEncryption) {
        dbgp_app("Message Length: %d\n", pECB->mstrLen);
        if (pECB->mstrLen) {
            outputHexStr("Plain Text:\n\r", pECB->mStr, pECB->mstrLen);
        } else {
            printf("   no data to encrypt (only header authenticated)....\n");
        }

        retVal = ecb_init_and_enkey(pECB->key, pECB->keyLen, ctx);
        if (retVal != RETURN_GOOD) {
            errVal = ECBKEY_ERROR;
            return;
        }

        printf("\nEncrypting...\n\r");
        retVal = ecb_encrypt_message(pECB->mstrLen, pECB->mStr, ctx);
        if (retVal != RETURN_GOOD) {
            errVal = ECBENCR_ERROR;
            //do_exit(errVal);
        }

        if (pECB->mstrLen) {
            outputHexStr("Cipher Text:\n\r", pECB->mStr, pECB->mstrLen);
        }
    }
    

    /* Then decrypt */
    else {
        dbgp_app("Message Length: %d\n", pECB->mstrLen);
        if (pECB->mstrLen) {
            outputHexStr("Plain Text:\n\r", pECB->mStr, pECB->mstrLen);
        } else {
            printf("   no data to encrypt (only header authenticated)....\n");
        }
        
        retVal = ecb_init_and_dekey(pECB->key, pECB->keyLen, ctx);
        printf("Decrypting...\n\r");
        retVal = ecb_decrypt_message(pECB->mstrLen, pECB->mStr, ctx);
        if (pECB->mstrLen) {
            outputHexStr("Plain Text:\n\r", pECB->mStr, pECB->mstrLen);
        } else {
            printf("   no data to decrypt (only header authenticated)....\n");
        }

    
    }



}
