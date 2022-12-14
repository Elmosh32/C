#ifndef _ADTDEFS_H_
#define _ADTDEFS_H_

typedef enum
{
        /* General ADT Errors */
        ERR_OK                            =0,
        ERR_GENERAL,
        ERR_NOT_INITIALIZED,
        ERR_ALLOCATION_FAILED,
        ERR_REALLOCATION_FAILED,
        ERR_UNDERFLOW,
        ERR_OVERFLOW,
        ERR_WRONG_INDEX,
        ERR_INVALID_SIZE
} ADTErr;

#endif /*_ADTDEFS_H_*/
