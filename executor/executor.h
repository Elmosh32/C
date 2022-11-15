#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include <time.h>

typedef struct PeriodicExecutor PeriodicExecutor;

typedef enum
{
    ERR_OK = 1,
    ERR_NOT_INITIALIZED = -1,
    ERR_CREATE_TASK = -2,
    ERR_VECTOR_APPEND = -3,
    ERR_HEAP_BUILD = -4,
    ERR_EMPTY = -5
} ERRORS;

/**
 * @brief Creates a TasksExecutor
 * @params _name : The name of the TasksExecutor
 * @params _clk_id : CLOCK_REALTIME
 * @return if success returns pointer to TasksExecutor else retunrs null
 */
PeriodicExecutor *PeriodicExecutor_Create(const char *_name, clockid_t _clk_id);

/**
 * @brief Destroys the TasksExecutor.
 * @params _executor : A TasksExecutor to destroy
 * @return X
 */
void PeriodicExecutor_Destroy(PeriodicExecutor *_executor);

/**
 * @brief Adds a new task to a given TaskExecutor (_executor)
 * @params _executor : A TaskExecutor to add a task to execute
 * @params (*_taskFunction) : A task function to be executed, cannot be NULL
 * @params _context :  Context to pass to the task's function.
 * @params _period_ms :  A period time in miliseconds.
 * @return IF _executor == NULL || _taskFunction == NULL RETURNS ERR_NOT_INITIALIZED(-1)
 *         if CreateTask failed returns ERR_CREATE_TASK(-2)
 *         if VectorAppend falied returns ERR_VECTOR_APPEND(-3)
 *         if success ERR_OK(1)
 */
int PeriodicExecutor_Add(PeriodicExecutor *_executor, int (*_taskFunction)(void *), void *_context, size_t _period_ms);

/**
 * @brief Run the tasks, until they over or paused.
 * @params _executor : pointer to the periodic executor.
 * @return return the number of execution cycles performed, 0 if the _executor isn't exist.
 */
size_t PeriodicExecutor_Run(PeriodicExecutor *_executor);

/**
 * @brief Pause the running of all tasks.
 * @details The paused executor can be resumed later on by calling PeriodicExecutor_Run.
 * @params _executor : pointer to the periodic executor
 * @return return the number of tasks remaining inside the executor.
 */
size_t PeriodicExecutor_Pause(PeriodicExecutor *_executor);

#endif /* __EXECUTOR_H__ */
