#define _XOPEN_SOURCE 600
#define _POSIX_C_SOURCE 200112L

#include <time.h>
#include <unistd.h>

#include "time.h"
#include "task.h"

static timespec getTime(clockid_t _clockId);

timespec CalcNextTime(size_t _periodMS, clockid_t _clockId)
{
    timespec nextTime;

    nextTime = getTime(_clockId);
    nextTime.tv_sec += MS_TO_S(_periodMS);
    nextTime.tv_nsec += MS_TO_NS(_periodMS);

    return nextTime;
}

void sleepTime(timespec _nextRunTime, clockid_t _clockId)
{
    timespec time;
    long sleepTime;

    time = getTime(_clockId);
    if (CompareTime(_nextRunTime, time) <= 0)
    {
        return;
    }

    sleepTime = MS_TO_S(CompareTime(_nextRunTime, time));
    usleep(sleepTime);

    return;
}

long CompareTime(timespec _time1, timespec _time2)
{
    long nanoDif;

    nanoDif = _time1.tv_nsec - _time2.tv_nsec;

    return nanoDif;
}

static timespec getTime(clockid_t _clockId)
{
    timespec time;

    clock_gettime(_clockId, &time);

    return time;
}
