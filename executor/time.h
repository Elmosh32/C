#ifndef __TIME_H__
#define __TIME_H__

typedef int clockid_t;

typedef struct timespec timespec;

#define MS_TO_NS(ms) ms * 1000000
#define NS_TO_MS(ns) ns / 1000000

#define S_TO_NS(ns) ns * 1000000000
#define NS_TO_S(ns) ns / 1000000000

#define S_TO_MS(s) s * 1000
#define MS_TO_S(ms) ms / 1000

/**
 * @brief
 * @params _periodTime:
 * @params _clockId: CLOCK_REALTIME
 * @return timespec
 */
timespec CalcNextTime(size_t _periodTime, clockid_t _clockId);

/**
 * @brief
 * @params _nextRunTime:
 * @params _clockId: CLOCK_REALTIME
 * @return X
 */
void sleepTime(timespec _nextRunTime, clockid_t _clockId);

/**
 * @brief
 * @details
 * @params _time1:
 * @params _time2:
 * @return long
 */
long CompareTime(timespec _time1, timespec _time2);

#endif /* __TIME_H__ */