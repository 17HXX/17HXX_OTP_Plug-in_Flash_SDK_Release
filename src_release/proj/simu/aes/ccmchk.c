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

#include "ccm.h"
#include "debug.h"
#include "ccmchk.h"
#include "utils.h"



void do_exit(t_errVal errVal)
{

    printf("\n");

    switch (errVal) {
        /* Keep these in alphabetical order */

    case CCMDECR_ERROR:
        printf("CCM Error while  message\n");
        break;
    case CCMENCR_ERROR:
        printf("CCM Error while encrypting message\n");
        break;
    case CCMKEY_ERROR:
        printf("CCM Error while encrypting key\n");
        break;
    case MALLOC_ERROR:
        printf("Could not allocate memory\n");
        break;
    case NO_CCM_ERROR:
        break;
    default:
        printf("Unknown error type!!!!\n");
        break;
    } /* switch */

    printf("\n");
}



void ccmCheck(ccm_info_t *pCCM)
{
    ccm_ctx     ctx[1];
    t_errVal    errVal = NO_CCM_ERROR;
    ret_type    retVal = RETURN_GOOD;


    dbgp_app("-------------------Enter CCM Check------------------\n\n");

    dbgp_app("Key Length: %d\n", pCCM->keyLen);
    /* First encrypt */
    if (pCCM->keyLen) {
        outputHexStr("Key:\n\r", pCCM->key, pCCM->keyLen);
    } else {
        printf("\n   no key to use ...\n");
        errVal = CCMKEY_ERROR;
        do_exit(errVal);
    }

    if (pCCM->nonceLen) {
        outputHexStr("Nonce:\n\r", pCCM->nonce,pCCM->nonceLen);
    } else {
        printf("\n   no nonce to use ...\n");
        errVal = CCMENCR_ERROR;
        do_exit(errVal);
    }

    dbgp_app("Assoc. Header Length: %d\n", pCCM->ahdrLen);
    /* First encrypt */
    if (pCCM->ahdrLen) {
        outputHexStr("Assoc. header:\n\r", pCCM->aHdr, pCCM->ahdrLen);
    } else {
        printf("\n   no header to be authenticated ...\n");
    }

    dbgp_app("Message Length: %d\n", pCCM->mstrLen);
    if (pCCM->mstrLen) {
        outputHexStr("Plain Text:\n\r", pCCM->mStr, pCCM->mstrLen);
    } else {
        printf("   no data to encrypt (only header authenticated)....\n");
    }


    retVal = ccm_init_and_key(pCCM->key, pCCM->keyLen, ctx);
    if (retVal != RETURN_GOOD) {
        errVal = CCMKEY_ERROR;
        do_exit(errVal);
    }

    if (pCCM->fEncryption) {
        printf("Encrypting...\n\r");
        retVal = ccm_encrypt_message(pCCM->nonce, pCCM->nonceLen, pCCM->aHdr, pCCM->ahdrLen,
                                     pCCM->mStr, pCCM->mstrLen, pCCM->micE, pCCM->micLen>2?pCCM->micLen:2, ctx);
        if (retVal != RETURN_GOOD) {
            errVal = CCMENCR_ERROR;
            do_exit(errVal);
        }

        if (pCCM->mstrLen) {
            outputHexStr("Cipher Text:\n\r", pCCM->mStr, pCCM->mstrLen);
        }
        if (pCCM->micLen) {
            outputHexStr("MIC on encrypt side:\n\r", pCCM->micE, pCCM->micLen>2?pCCM->micLen:0);
        }
    }
    
    /* Then decrypt */
    else {
    
        printf("Decrypting...\n\r");
        retVal = ccm_decrypt_message(pCCM->nonce, pCCM->nonceLen, pCCM->aHdr, pCCM->ahdrLen,
                                     pCCM->mStr, pCCM->mstrLen, pCCM->micE, pCCM->micLen>2?pCCM->micLen:2, pCCM->micD, ctx);
        if (pCCM->mstrLen) {
            outputHexStr("Plain Text:\n\r", pCCM->mStr, pCCM->mstrLen);
        } else {
            printf("   no data to decrypt (only header authenticated)....\n");
        }
        if (RETURN_GOOD == retVal) {
            printf ("MIC match\n\r");
        }
        else {
            outputHexStr("MIC on decrypt side:\n\r", pCCM->micD, pCCM->micLen>2?pCCM->micLen:0);
        }

    }

}

