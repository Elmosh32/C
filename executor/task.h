#ifndef __TASK_H__
#define __TASK_H__

typedef struct Task Task;

typedef int (*taskFunction)(void *);

/**
 * @brief Creates a new task.
 * @params (*_taskFunction): task function action, cannot be NULL
 * @params _context: the task context
 * @params periodTime: A period time in miliseconds.
 * @return if success returns pointer to Task else retunrs null
 */
Task *CreateTask(int (*_taskFunction)(void *), void *_context, size_t periodTime);

/**
 * @brief Destroy _task.
 * @params _task: Task to destroy
 * @return X
 */
void DestroyTask(void *_task);

/**
 * @brief Run the task, until the tasl over or paused.
 * @params _task: pointer to the task
 * @params _clockId: CLOCK_REALTIME
 * @return if task == null returns ERR_NULL_TASK(-1)
 *          else returns _task->m_functionPointer => (0 if m_functionPointer stop the task else 1)
 */
int RunTask(Task *_task, clockid_t _clockId);

/**
 * @brief Calculates the next run time of the task.
 * @params _task: pointer to the task
 * @params _clockId: CLOCK_REALTIME
 * @return if task == null returns ERR_NULL_TASK(-1)
 *         if success returns ERR_OK(1)
 */
int CalcNextRunTime(Task *_task, clockid_t _clockId);

/**
 * @brief Compare two tasks
 * @params _task1: pointer to the first task
 * @params _task2: pointer to the second task
 * @return If task-1 time < task-2 time returns 1.
 *         else return 0;
 */
int CompareTasks(const void *_task1, const void *_task2);

#endif /* __TASK_H__ */