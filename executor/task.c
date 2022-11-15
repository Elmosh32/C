#define _XOPEN_SOURCE 600
#define _POSIX_C_SOURCE 200112L
#include <time.h>

#include <stdlib.h>
#include "task.h"
#include "time.h"

#define TASK_MAGIC_NUMBER 132902
#define ERR_OK 1
#define ERR_NULL_TASK -1

struct Task
{
    taskFunction m_taskFunc;
    timespec m_nextRunTime;
    size_t m_periodTime;
    void *m_context;
    int m_magicNum;
};

Task *CreateTask(int (*_taskFunction)(void *), void *_context, size_t _periodTime)
{
    Task *task;

    if (_taskFunction == NULL)
    {
        return NULL;
    }

    if ((task = ((Task *)malloc(sizeof(Task)))) == NULL)
    {
        return NULL;
    }

    task->m_taskFunc = _taskFunction;
    task->m_periodTime = _periodTime;
    task->m_context = _context;
    task->m_magicNum = TASK_MAGIC_NUMBER;

    return task;
}

void DestroyTask(void *_task)
{
    if (_task == NULL || ((Task *)_task)->m_magicNum != TASK_MAGIC_NUMBER)
    {
        return;
    }

    free(_task);
}

int RunTask(Task *_task, clockid_t _clockId)
{
    if (_task == NULL)
    {
        return ERR_NULL_TASK;
    }

    sleepTime(_task->m_nextRunTime, _clockId);

    return _task->m_taskFunc(_task->m_context);
}

int CalcNextRunTime(Task *_task, clockid_t _clockId)
{
    if (_task == NULL)
    {
        return ERR_NULL_TASK;
    }

    _task->m_nextRunTime = CalcNextTime(_task->m_periodTime, _clockId);

    return ERR_OK;
}

int CompareTasks(const void *_task1, const void *_task2)
{
    timespec nextTime1;
    timespec nextTime2;

    nextTime1 = ((Task *)_task1)->m_nextRunTime;
    nextTime2 = ((Task *)_task2)->m_nextRunTime;

    if (CompareTime(nextTime1, nextTime2) < 0)
    {
        return 1;
    }

    return 0;
}
