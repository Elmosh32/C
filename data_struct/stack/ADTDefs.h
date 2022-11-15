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
        ERR_STACK_BBBBB = 30,
        ERR_EMPTY_STACK
                          /* Vector Errors */
                          /* Stack  Errors */
                          /* LinkedList  Errors */
                          /* Bit Vector*/
} ADTErr;

void HandleErr(ADTErr errNum, char *msg);
