#ifndef __STATUS_H__
#define __STATUS_H__

#include <stddef.h>

typedef enum
{
        OK = 0,
        OVERFLOW,
        REALLOC_FAIL,
        EMPTY_AD,
        APPOINTMENT_ALREADY_EXIST,
        TIME_ERROR,
        APPOINTMENT_DAIRY_IS_NOT_INITIALIZED,
        APPOINTMENT_NOT_FOUND,
        STRUCT_ALREADY_DESTROYED,
        FILE_OPEN_FAILED,
        OVERLAPPING,
        STOP_APP
} status;


#endif /*__STATUS_H__*/
