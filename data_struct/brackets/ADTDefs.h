#ifndef __ADTDEFS_H__
#define __ADTDEFS_H__

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
        ERR_EMPTY_STACK
} ADTErr;

void HandleErr(ADTErr errNum, char *msg);

#endif /* __ADTDEFS_H__ */
