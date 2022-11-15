#define _XOPEN_SOURCE 600
#define _POSIX_C_SOURCE 200112L

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "executor.h"
#include "task.h"
#include "../advc/genHeap/genHeap.h"

#define EXECUTOR_MAGIC_NUMBER 6534445
#define VECTOR_CAPACITY 5
#define VECTOR_BLOCK_SIZE 10
#define NAME_LEN 20

struct PeriodicExecutor
{
    Heap *m_heap;
    Vector *m_tasks;
    clockid_t m_clk_id;
    char m_name[NAME_LEN];
    int m_pauseFlag;
    int m_magicNum;
    int m_numOfTask;
    int m_numOfCycles;
};

static void SetTasksNextTimeRun(Vector *_vector, clockid_t _clockId);

PeriodicExecutor *PeriodicExecutor_Create(const char *_name, clockid_t _clk_id)
{
    PeriodicExecutor *executor;

    if (!_name || _clk_id != CLOCK_REALTIME)
    {
        return NULL;
    }

    if ((executor = ((PeriodicExecutor *)malloc(sizeof(PeriodicExecutor)))) == NULL)
    {
        return NULL;
    }

    if ((executor->m_tasks = VectorCreate(VECTOR_CAPACITY, VECTOR_BLOCK_SIZE)) == NULL)
    {
        free(executor);
        return NULL;
    }

    executor->m_heap = NULL;
    executor->m_clk_id = _clk_id;
    executor->m_pauseFlag = 0;
    executor->m_numOfTask = 0;
    executor->m_numOfCycles = 0;
    strcpy(executor->m_name, _name);
    executor->m_magicNum = EXECUTOR_MAGIC_NUMBER;

    return executor;
}

void PeriodicExecutor_Destroy(PeriodicExecutor *_executor)
{
    if (_executor == NULL || _executor->m_magicNum != EXECUTOR_MAGIC_NUMBER)
    {
        return;
    }

    if (_executor->m_tasks)
    {
        VectorDestroy(&_executor->m_tasks, DestroyTask);
    }

    _executor->m_magicNum = 0;
    free(_executor);
}

int PeriodicExecutor_Add(PeriodicExecutor *_executor, int (*_taskFunction)(void *), void *_context, size_t _period_ms)
{
    Task *task;

    if (_executor == NULL || _taskFunction == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }

    if (_period_ms <= 0)
    {
        return ERR_CREATE_TASK;
    }

    if ((task = CreateTask(_taskFunction, _context, _period_ms)) == NULL)
    {
        DestroyTask(task);
        return ERR_CREATE_TASK;
    }

    if (VectorAppend(_executor->m_tasks, task) != VECTOR_SUCCESS)
    {
        return ERR_VECTOR_APPEND;
    }

    _executor->m_numOfTask++;
    return ERR_OK;
}

size_t PeriodicExecutor_Run(PeriodicExecutor *_executor)
{

    Task *task;
    int taskStatus;
    if (_executor == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }

    if (_executor->m_numOfTask == 0)
    {
        return ERR_EMPTY;
    }

    _executor->m_pauseFlag = 0;

    SetTasksNextTimeRun(_executor->m_tasks, _executor->m_clk_id);

    if ((_executor->m_heap = HeapBuild(_executor->m_tasks, CompareTasks)) == NULL)
    {
        return ERR_HEAP_BUILD;
    }

    while (1)
    {
        if (_executor->m_pauseFlag == 1)
        {
            break;
        }

        if ((task = HeapExtract(_executor->m_heap)) == NULL)
        {
            break;
        }

        taskStatus = RunTask(task, _executor->m_clk_id);
        if (taskStatus != 0)
        {
            DestroyTask(task);
            _executor->m_numOfTask--;
        }
        else
        {
            CalcNextRunTime(task, _executor->m_clk_id);
            HeapInsert(_executor->m_heap, task);
        }

        _executor->m_numOfCycles++;
    }

    HeapDestroy(&_executor->m_heap);

    return _executor->m_numOfCycles;
}

size_t PeriodicExecutor_Pause(PeriodicExecutor *_executor)
{
    if (_executor == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }

    _executor->m_pauseFlag = 1;

    return _executor->m_numOfTask;
}

static void SetTasksNextTimeRun(Vector *_vector, clockid_t _clockId)
{
    size_t vectorSize;
    Task *task;
    size_t i;

    vectorSize = VectorSize(_vector);
    for (i = 0; i < vectorSize; i++)
    {
        VectorGet(_vector, i, (void *)&task);
        CalcNextRunTime(task, _clockId);
    }
}
