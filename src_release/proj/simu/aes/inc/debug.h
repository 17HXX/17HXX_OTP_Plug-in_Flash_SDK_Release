/**********************************************************
 * Copyright (C) 2008, HART Communication Foundation, Inc.
 **********************************************************/

#ifndef _DEBUG_H
#define _DEBUG_H


#if 0
#include <stdio.h>


/****************
 *  Definitions
 ****************/
/* Set values of the following to 1 to turn on debug 
 * printing for the desired code areas.
 */
#define DEBUG_APP     1     /* application debug */
#define DEBUG_CCM     0     /* ccm debug */


#if (DEBUG_APP)
#define dbgp_app(format, a...)     printf(format, ## a)
#else
#define dbgp_app(format, a...)  
#endif

#if (DEBUG_CCM)
#define dbgp_ccm(format, a...)     printf(format, ## a)
#else
#define dbgp_ccm(format, a...)  
#endif
#endif

#endif /* _DEBUG_H */

