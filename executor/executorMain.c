
#define _XOPEN_SOURCE 600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "executor.h"

#define MS_TO_SEC(ms) ms / 1000
#define SEC_TO_MS(s) s * 1000

#define FIRST_EXEC_TIME_MS 10000
#define SECOND_EXEC_TIME_MS 13000
#define THIRD_EXEC_TIME_MS 5000

#define PAUSE_TIME 3
#define TASK_A_MAX_CYCLES 3
#define TASK_B_MAX_CYCLES 1
#define TASK_C_MAX_CYCLES 4

typedef struct TaskParameters TaskParameters;

struct TaskParameters
{
    int m_totalRun;
    long m_seconds;
    char m_name[20];
};

TaskParameters tasks[3] = {{0, FIRST_EXEC_TIME_MS, "task A"}, {0, SECOND_EXEC_TIME_MS, "task B"}, {0, THIRD_EXEC_TIME_MS, "task c"}};

typedef struct TaskAParam
{
    int totalRun;
    void *seconds;
} TaskAParam;

typedef struct TaskBParam
{
    int totalRun;
    void *seconds;
} TaskBParam;

typedef struct TaskCParam
{
    int totalRun;
    void *seconds;
} TaskCParam;

int counter = 0;
int TaskAFunc(void *_task)
{
    if ((*(TaskAParam *)_task).totalRun == TASK_A_MAX_CYCLES)
    {
        return 1;
    }

    counter += *(int *)(*(TaskAParam *)_task).seconds;
    (*(TaskAParam *)_task).totalRun++;
    /**
    printf("\nTime: %d ", counter);
    printf("execute task A\n");
    **/
    return 0;
}

int TaskBFunc(void *_task)
{
    if ((*(TaskBParam *)_task).totalRun == TASK_B_MAX_CYCLES)
    {
        return 1;
    }

    counter += *(int *)(*(TaskBParam *)_task).seconds;
    (*(TaskBParam *)_task).totalRun++;
    /**
    printf("\nTime: %d ", counter);
    printf("execute task B\n");
    **/
    return 0;
}

int TaskCFunc(void *_task)
{
    if ((*(TaskCParam *)_task).totalRun == TASK_C_MAX_CYCLES)
    {
        return 1;
    }
    counter += *(int *)(*(TaskCParam *)_task).seconds;
    (*(TaskCParam *)_task).totalRun++;

    /**
    printf("\nTime: %d ", counter);
    printf("execute task C\n");
    **/
    return 0;
}

int DumbFunc(void *_task)
{
    return 1;
}

int pauseE(void *_executor)
{
    /**
    printf("\nPause %d sec! \n", PAUSE_TIME);
    **/
    PeriodicExecutor_Pause((PeriodicExecutor *)_executor);
    sleep(PAUSE_TIME);

    return 1;
}

static void PeriodicCreateT1();
static void PeriodicCreateT2();
static void PeriodicCreateT3();

static void PeriodicDestroyT1();
static void PeriodicDestroyT2();
static void PeriodicDestroyT3();

static void PeriodicAddT1();
static void PeriodicAddT2();
static void PeriodicAddT3();
static void PeriodicAddT4();

static void PeriodicRunT1();
static void PeriodicRunT2();
static void PeriodicRunT3();

static void PeriodicPauseT1();
static void PeriodicPauseT2();
static void PeriodicPauseT3();

int main()
{
    PeriodicCreateT1();
    PeriodicCreateT2();
    PeriodicCreateT3();
    puts("\n");
    PeriodicDestroyT1();
    PeriodicDestroyT2();
    PeriodicDestroyT3();
    puts("\n");
    PeriodicAddT1();
    PeriodicAddT2();
    PeriodicAddT3();
    PeriodicAddT4();
    puts("\n");
    PeriodicRunT1();
    PeriodicRunT2();
    PeriodicRunT3();
    puts("\n");
    PeriodicPauseT1();
    PeriodicPauseT2();
    PeriodicPauseT3();

    return 0;
}

static void PeriodicCreateT1()
{
    if ((PeriodicExecutor_Create(NULL, CLOCK_REALTIME)) != NULL)
    {
        printf("1) PeriodicExecutor_Create\t=>\tFAIL\n");
        return;
    }

    printf("1) PeriodicExecutor_Create\t=>\tPASS\n");
}

static void PeriodicCreateT2()
{
    if ((PeriodicExecutor_Create(NULL, CLOCK_BOOTTIME)) != NULL)
    {
        printf("2) PeriodicExecutor_Create\t=>\tFAIL\n");
        return;
    }

    printf("2) PeriodicExecutor_Create\t=>\tPASS\n");
}

static void PeriodicCreateT3()
{
    if ((PeriodicExecutor_Create("task", CLOCK_REALTIME)) == NULL)
    {
        printf("3) PeriodicExecutor_Create\t=>\tFAIL\n");
        return;
    }

    printf("3) PeriodicExecutor_Create\t=>\tPASS\n");
}

static void PeriodicDestroyT1()
{
    PeriodicExecutor_Destroy(NULL);

    printf("1) PeriodicExecutor_Destroy\t=>\tPASS\n");
}

static void PeriodicDestroyT2()
{
    PeriodicExecutor *executor;
    executor = PeriodicExecutor_Create("task", CLOCK_REALTIME);
    PeriodicExecutor_Destroy(executor);

    printf("2) PeriodicExecutor_Destroy\t=>\tPASS\n");
}

static void PeriodicDestroyT3()
{
    PeriodicExecutor *executor;
    executor = PeriodicExecutor_Create("task", CLOCK_REALTIME);
    PeriodicExecutor_Destroy(executor);
    PeriodicExecutor_Destroy(executor);

    printf("3) PeriodicExecutor_Destroy\t=>\tPASS\n");
}

static void PeriodicAddT1()
{
    if ((PeriodicExecutor_Add(NULL, TaskAFunc, tasks, FIRST_EXEC_TIME_MS)) != ERR_NOT_INITIALIZED)
    {
        printf("1) PeriodicExecutor_Add\t=>\tFAIL\n");
        return;
    }

    printf("1) PeriodicExecutor_Add\t=>\tPASS\n");
}

static void PeriodicAddT2()
{
    PeriodicExecutor *executor;
    executor = PeriodicExecutor_Create("task", CLOCK_REALTIME);

    if ((PeriodicExecutor_Add(executor, NULL, tasks, FIRST_EXEC_TIME_MS)) != ERR_NOT_INITIALIZED)
    {
        printf("1) PeriodicExecutor_Add\t=>\tFAIL\n");
        return;
    }

    printf("1) PeriodicExecutor_Add\t=>\tPASS\n");
}

static void PeriodicAddT3()
{
    PeriodicExecutor *executor;
    executor = PeriodicExecutor_Create("task", CLOCK_REALTIME);

    if ((PeriodicExecutor_Add(executor, TaskAFunc, tasks, FIRST_EXEC_TIME_MS)) != ERR_OK)
    {
        printf("3) PeriodicExecutor_Add\t=>\tFAIL\n");
        return;
    }

    printf("3) PeriodicExecutor_Add\t=>\tPASS\n");
}

static void PeriodicAddT4()
{
    PeriodicExecutor *executor;
    executor = PeriodicExecutor_Create("task", CLOCK_REALTIME);

    PeriodicExecutor_Add(executor, TaskAFunc, NULL, FIRST_EXEC_TIME_MS);
    PeriodicExecutor_Add(executor, TaskAFunc, NULL, FIRST_EXEC_TIME_MS);
    if ((PeriodicExecutor_Add(executor, TaskAFunc, NULL, FIRST_EXEC_TIME_MS)) != ERR_OK)
    {
        printf("4) PeriodicExecutor_Add\t=>\tFAIL\n");
        return;
    }

    printf("4) PeriodicExecutor_Add\t=>\tPASS\n");
}

static void PeriodicRunT1()
{
    if ((PeriodicExecutor_Run(NULL)) != ERR_NOT_INITIALIZED)
    {
        printf("1) PeriodicExecutor_Run\t=>\tFAIL\n");
        return;
    }

    printf("1) PeriodicExecutor_Run\t=>\tPASS\n");
}

static void PeriodicRunT2()
{
    PeriodicExecutor *executor;
    executor = PeriodicExecutor_Create("task", CLOCK_REALTIME);

    if ((PeriodicExecutor_Run(executor)) != ERR_EMPTY)
    {
        printf("2) PeriodicExecutor_Run\t=>\tFAIL\n");
        return;
    }

    printf("2) PeriodicExecutor_Run\t=>\tPASS\n");
}

static void PeriodicRunT3()
{
    PeriodicExecutor *executor;
    executor = PeriodicExecutor_Create("task", CLOCK_REALTIME);

    PeriodicExecutor_Add(executor, DumbFunc, NULL, 100);
    PeriodicExecutor_Add(executor, DumbFunc, NULL, 100);

    if ((PeriodicExecutor_Run(executor)) != 2)
    {
        printf("3) PeriodicExecutor_Run\t=>\tFAIL\n");
        return;
    }

    printf("3) PeriodicExecutor_Run\t=>\tPASS\n");
}

static void PeriodicPauseT1()
{
    if ((PeriodicExecutor_Pause(NULL)) != ERR_NOT_INITIALIZED)
    {
        printf("1) PeriodicExecutor_Pause\t=>\tFAIL\n");
        return;
    }

    printf("1) PeriodicExecutor_Pause\t=>\tPASS\n");
}

static void PeriodicPauseT2()
{
    PeriodicExecutor *executor;
    TaskAParam *taskA;
    TaskBParam *taskB;
    TaskCParam *taskC;

    char name[] = "name";
    int *a[4];

    if ((taskA = ((TaskAParam *)malloc(sizeof(TaskAParam)))) == NULL)
    {
        return;
    }

    if ((taskB = ((TaskBParam *)malloc(sizeof(TaskBParam)))) == NULL)
    {
        return;
    }

    if ((taskC = ((TaskCParam *)malloc(sizeof(TaskCParam)))) == NULL)
    {
        return;
    }

    a[0] = malloc(sizeof(int));
    *a[0] = MS_TO_SEC(FIRST_EXEC_TIME_MS);

    a[1] = malloc(sizeof(int));
    *a[1] = MS_TO_SEC(SECOND_EXEC_TIME_MS);

    a[2] = malloc(sizeof(int));
    *a[2] = MS_TO_SEC(THIRD_EXEC_TIME_MS);

    taskA->totalRun = 0;
    taskB->totalRun = 0;
    taskC->totalRun = 0;

    taskA->seconds = a[0];
    taskB->seconds = a[1];
    taskC->seconds = a[2];

    executor = PeriodicExecutor_Create(name, CLOCK_REALTIME);

    PeriodicExecutor_Add(executor, pauseE, executor, 10);
    PeriodicExecutor_Add(executor, TaskAFunc, taskA, 200);
    PeriodicExecutor_Add(executor, TaskBFunc, taskB, 500);
    PeriodicExecutor_Add(executor, TaskCFunc, taskC, 300);

    /*PAUSE -> 1*/
    if ((PeriodicExecutor_Run(executor)) != 1)
    {
        printf("2) PeriodicExecutor_Pause\t=>\tFAIL\n");
        return;
    }
    printf("2) PeriodicExecutor_Pause\t=>\tPASS\n");

    PeriodicExecutor_Destroy(executor);
}

static void PeriodicPauseT3()
{
    PeriodicExecutor *executor;
    TaskAParam *taskA;
    TaskBParam *taskB;
    TaskCParam *taskC;

    char name[] = "name";
    int *a[4];

    if ((taskA = ((TaskAParam *)malloc(sizeof(TaskAParam)))) == NULL)
    {
        return;
    }

    if ((taskB = ((TaskBParam *)malloc(sizeof(TaskBParam)))) == NULL)
    {
        return;
    }

    if ((taskC = ((TaskCParam *)malloc(sizeof(TaskCParam)))) == NULL)
    {
        return;
    }

    a[0] = malloc(sizeof(int));
    *a[0] = MS_TO_SEC(FIRST_EXEC_TIME_MS);

    a[1] = malloc(sizeof(int));
    *a[1] = MS_TO_SEC(SECOND_EXEC_TIME_MS);

    a[2] = malloc(sizeof(int));
    *a[2] = MS_TO_SEC(THIRD_EXEC_TIME_MS);

    taskA->totalRun = 0;
    taskB->totalRun = 0;
    taskC->totalRun = 0;

    taskA->seconds = a[0];
    taskB->seconds = a[1];
    taskC->seconds = a[2];

    executor = PeriodicExecutor_Create(name, CLOCK_REALTIME);

    PeriodicExecutor_Add(executor, TaskAFunc, taskA, 400);
    PeriodicExecutor_Add(executor, TaskBFunc, taskB, 500);
    PeriodicExecutor_Add(executor, TaskCFunc, taskC, 600);
    PeriodicExecutor_Add(executor, pauseE, executor, 10);

    PeriodicExecutor_Run(executor);
    /* 5 TASK-A + 4 TASK-B + 2 TASKC + 1 PAUSE*/
    if ((PeriodicExecutor_Run(executor)) != 12)
    {
        printf("3) PeriodicExecutor_Pause\t=>\tFAIL\n");
        return;
    }
    printf("3) PeriodicExecutor_Pause\t=>\tPASS\n");

    PeriodicExecutor_Destroy(executor);
}

/**
int PrintE(void **_task)
{
long taskATime, taskBTime, taskCTime;
long size1 = (long *)(((TaskParameters *)_task)[0]).m_seconds;
long size2 = (long *)(((TaskParameters *)_task)[1]).m_seconds;
long size3 = (long *)(((TaskParameters *)_task)[2]).m_seconds;
if (counter < MS_TO_SEC(size1))
{
    taskATime = MS_TO_SEC(size1) - counter;
}
else
{
    taskATime = counter - MS_TO_SEC(size1);
}

if (counter < MS_TO_SEC(size2))
{
    taskBTime = MS_TO_SEC(size2) - counter;
}
else
{
    taskBTime = counter - MS_TO_SEC(size2);
}

if (counter < MS_TO_SEC(size3))
{
    taskCTime = MS_TO_SEC(size3) - counter;
}
else
{
    taskCTime = counter - MS_TO_SEC(size3);
}
printf("taskATime:%ld\n", taskATime);
printf("taskBTime:%ld\n", taskBTime);
printf("taskCTime:%ld\n", taskCTime);

if (counter == MS_TO_SEC(size1))
{
    if ((int *)(((TaskParameters *)_task)[0]).m_totalRun == 3)
    {
        return 1;
    }

    counter += 0.2;
    (int *)(((TaskParameters *)_task)[0]).m_totalRun++;
    printf("\nTime: %f ", counter);
    printf("execute task A\n");
    return 0;
}
else if (counter == MS_TO_SEC(size2))
{

    if ((int *)(((TaskParameters *)_task)[1]).m_totalRun == 1)
    {
        return 1;
    }

    counter += 0.2;
    (int *)(((TaskParameters *)_task)[1]).m_totalRun++;
    printf("\nTime: %f ", counter);
    printf("execute task B\n");
    return 0;
}
else if (counter == MS_TO_SEC(size3))
{
    if ((int *)(((TaskParameters *)_task)[2]).m_totalRun == 4)
    {
        return 1;
    }

    counter += 0.2;
    (int *)(((TaskParameters *)_task)[2]).m_totalRun++;
    printf("\nTime: %f ", counter);
    printf("execute task C\n");
    return 0;
}

if (taskATime < taskBTime && taskATime < taskCTime)
{

    if ((int *)(((TaskParameters *)_task)[0]).m_totalRun == 3)
    {
        return 1;
    }

    counter += (float)MS_TO_SEC(size1);
    (int *)(((TaskParameters *)_task)[0]).m_totalRun++;
    printf("\nTime: %f ", counter);
    printf("execute task A\n");
    return 0;
}
else if (taskBTime < taskCTime && taskBTime < taskATime)
{

    if ((int *)(((TaskParameters *)_task)[1]).m_totalRun == 1)
    {
        return 1;
    }

    counter += (float)MS_TO_SEC(size2);
    (int *)(((TaskParameters *)_task)[1]).m_totalRun++;
    printf("\nTime: %f ", counter);
    printf("execute task B\n");
    return 0;
}
else if (taskCTime < taskBTime && taskCTime < taskATime)
{

    if ((int *)(((TaskParameters *)_task)[2]).m_totalRun == 4)
    {
        return 1;
    }

    counter += (float)MS_TO_SEC(size3);
    (int *)(((TaskParameters *)_task)[2]).m_totalRun++;
    printf("\nTime: %f ", counter);
    printf("execute task C\n");
    return 0;
}

return 0;
}
**/