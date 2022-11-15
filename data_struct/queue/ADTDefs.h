#ifndef __ADTDEFS_H__
#define __ADTDEFS_H__
typedef enum
{
        /* General ADT Errors */
        OK                            =0,
        NOT_INITIALIZED,
        EMPTY_QUEUE,
        FULL_QUEUE
} ADTErr;

void HandleErr(ADTErr errNum, char *msg);
#endif /* __ADTDEFS_H__ */
