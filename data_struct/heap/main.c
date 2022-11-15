#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "heap.h"
#include "ADTDefs.h"

void heapBuildT1()
{
        if (HeapBuild(NULL) != NULL)
        {
                printf("HeapBuild negative test\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapBuild negative test\t=>\tPASS\n");
        }
}

void heapBuildT2()
{
        Heap *heap;
        Vector *vec;
        vec = VectorCreate(4, 4);

        VectorAdd(vec, 1);
        VectorAdd(vec, 55);
        VectorAdd(vec, 31);
        VectorAdd(vec, 55);
        VectorAdd(vec, 31);

        if ((heap = HeapBuild(vec)) == NULL)
        {
                printf("HeapBuild positive test\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapBuild positive test\t=>\tPASS\n");
        }

        HeapDestroy(heap);
        VectorDestroy(vec);
}

void heapBuildT3()
{
        Heap *heap;
        Vector *vec;
        int max;

        vec = VectorCreate(4, 4);

        VectorAdd(vec, 1000);
        VectorAdd(vec, 222);
        VectorAdd(vec, 300);
        VectorAdd(vec, 400);
        VectorAdd(vec, 1001);
        VectorAdd(vec, 500);
        VectorAdd(vec, 600);
        VectorAdd(vec, 700);

        heap = HeapBuild(vec);
        HeapMax(heap, &max);

        if (max != 1001)
        {
                printf("HeapBuild positive test\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapBuild positive test\t=>\tPASS\n");
        }
        HeapDestroy(heap);
        VectorDestroy(vec);
}

void heapBuildT4()
{
        Heap *heap;
        Vector *vec;

        vec = VectorCreate(4, 4);
        heap = HeapBuild(vec);

        if (heap == NULL)
        {
                printf("HeapBuild positive test\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapBuild positive test\t=>\tPASS\n");
        }

        HeapDestroy(heap);
        VectorDestroy(vec);
}

void HeapDestroyT1()
{
        HeapDestroy(NULL);
        printf("HeapDestroy(NULL)\t=>\tPASS\n");
}

void HeapDestroyT2()
{
        Heap *heap;
        Vector *vec;

        vec = VectorCreate(4, 4);
        VectorAdd(vec, 1000);
        heap = HeapBuild(vec);
        HeapDestroy(heap);
        HeapDestroy(heap);
        printf("HeapDestroy twice\t=>\tPASS\n");
}

void HeapInsertT1()
{
        if (HeapInsert(NULL, 2) != ERR_NOT_INITIALIZED)
        {
                printf("HeapInsert(NULL)\t\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapInsert(NULL)\t\t=>\tPASS\n");
        }
}

void HeapInsertT2()
{
        Heap *heap;
        Vector *vec;

        vec = VectorCreate(4, 4);
        VectorAdd(vec, 1000);
        heap = HeapBuild(vec);
        HeapDestroy(heap);
        if (HeapInsert(NULL, 2) != ERR_NOT_INITIALIZED)
        {
                printf("HeapInsert after destroy\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapInsert after destroy\t=>\tPASS\n");
        }
}

void HeapInsertT3()
{
        Heap *heap;
        Vector *vec;
        int max;

        vec = VectorCreate(4, 4);
        VectorAdd(vec, 211);
        VectorAdd(vec, 32);
        VectorAdd(vec, 1000);
        VectorAdd(vec, 544);

        heap = HeapBuild(vec);
        if (HeapInsert(heap, 1001) != ERR_OK)
        {
                printf("HeapInsert positive test\t=>\tFAIL\n");
        }

        HeapMax(heap, &max);

        if (max != 1001)
        {
                printf("HeapInsert positive test\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapInsert positive test\t=>\tPASS\n");
        }
}

void HeapInsertT4()
{
        Heap *heap;
        Vector *vec;
        int max;

        vec = VectorCreate(4, 4);
        VectorAdd(vec, 211);
        VectorAdd(vec, 1021);
        VectorAdd(vec, 1);
        VectorAdd(vec, 544);

        heap = HeapBuild(vec);

        if (HeapInsert(heap, 1001) != ERR_OK)
        {
                printf("HeapInsert positive test\t=>\tFAIL\n");
        }

        HeapMax(heap, &max);

        if (max != 1021)
        {
                printf("HeapInsert positive test\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapInsert positive test\t=>\tPASS\n");
        }
}

void HeapInsertT5()
{
        Heap *heap;
        Vector *vec;
        int max;

        vec = VectorCreate(4, 4);
        heap = HeapBuild(vec);

        if (HeapInsert(heap, 1001) != ERR_OK)
        {
                printf("HeapInsert positive test\t=>\tFAIL\n");
        }

        HeapMax(heap, &max);

        if (max != 1001)
        {
                printf("HeapInsert positive test\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapInsert positive test\t=>\tPASS\n");
        }
}

void HeapMaxT1()
{
        Heap *heap;
        Vector *vec;

        vec = VectorCreate(4, 4);
        heap = HeapBuild(vec);

        HeapInsert(heap, 1001);

        if (HeapMax(heap, NULL) != ERR_NOT_INITIALIZED)
        {
                printf("HeapMax(HEAP,NULL)\t\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapMax(HEAP,NULL)\t\t=>\tPASS\n");
        }
}

void HeapMaxT2()
{
        int max;
        if (HeapMax(NULL, &max) != ERR_NOT_INITIALIZED)
        {
                printf("HeapMax(NULL,&int)\t\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapMax(NULL,&int)\t\t=>\tPASS\n");
        }
}

void HeapMaxT3()
{
        Heap *heap;
        Vector *vec;
        int max;

        vec = VectorCreate(4, 4);
        heap = HeapBuild(vec);

        HeapInsert(heap, 1001);
        HeapDestroy(heap);
        if (HeapMax(heap, &max) != ERR_NOT_INITIALIZED)
        {
                printf("HeapMax after heap destroy\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapMax after heap destroy\t=>\tPASS\n");
        }
}

void HeapMaxT4()
{
        Heap *heap;
        Vector *vec;
        int max;

        vec = VectorCreate(4, 4);
        heap = HeapBuild(vec);
        if (HeapMax(heap, &max) != ERR_UNDERFLOW)
        {
                printf("HeapMax(HEAP,NULL)\t\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapMax(HEAP,NULL)\t\t=>\tPASS\n");
        }
}

void HeapExtractMaxT1()
{
        Heap *heap;
        Vector *vec;

        vec = VectorCreate(4, 4);
        heap = HeapBuild(vec);

        HeapInsert(heap, 1001);

        if (HeapExtractMax(heap, NULL) != ERR_NOT_INITIALIZED)
        {
                printf("HeapExtractMax(HEAP,NULL)\t\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapExtractMax(HEAP,NULL)\t\t=>\tPASS\n");
        }
}

void HeapExtractMaxT2()
{
        int max;
        if (HeapExtractMax(NULL, &max) != ERR_NOT_INITIALIZED)
        {
                printf("HeapExtractMax(NULL,&int)\t\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapExtractMax(NULL,&int)\t\t=>\tPASS\n");
        }
}

void HeapExtractMaxT3()
{
        Heap *heap;
        Vector *vec;
        int max;

        vec = VectorCreate(4, 4);
        heap = HeapBuild(vec);
        if (HeapExtractMax(heap, &max) != ERR_UNDERFLOW)
        {
                printf("HeapExtractMax(HEAP,NULL)\t\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapExtractMax(HEAP,NULL)\t\t=>\tPASS\n");
        }
}

void HeapExtractMaxT4()
{
        Heap *heap;
        Vector *vec;
        int max;

        vec = VectorCreate(4, 4);
        heap = HeapBuild(vec);

        HeapInsert(heap, 1001);
        HeapDestroy(heap);
        if (HeapExtractMax(heap, &max) != ERR_NOT_INITIALIZED)
        {
                printf("HeapExtractMax after heap destroy\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapExtractMax after heap destroy\t=>\tPASS\n");
        }

        HeapDestroy(heap);
        VectorDestroy(vec);
}

void HeapExtractMaxT5()
{
        Heap *heap;
        Vector *vec;
        int max;

        vec = VectorCreate(4, 4);
        heap = HeapBuild(vec);
        HeapInsert(heap, 1001);
        if (HeapExtractMax(heap, &max) != ERR_OK)
        {
                printf("HeapExtractMax VALID TEST 5\t\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapExtractMax VALID TEST 5\t\t=>\tPASS\n");
        }

        HeapDestroy(heap);
        VectorDestroy(vec);
}

void HeapExtractMaxT6()
{
        Heap *heap;
        Vector *vec;
        int ExtractMax, max;

        vec = VectorCreate(4, 4);
        heap = HeapBuild(vec);
        HeapInsert(heap, 1001);
        HeapInsert(heap, 21);
        HeapInsert(heap, 3451);
        HeapInsert(heap, 245);

        if (HeapExtractMax(heap, &ExtractMax) != ERR_OK)
        {
                printf("HeapExtractMax VALID TEST 6\t\t=>\tFAIL\n");
        }
        HeapMax(heap, &max);

        if (max != 1001)
        {
                printf("HeapExtractMax VALID TEST 6\t\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapExtractMax VALID TEST 6\t\t=>\tPASS\n");
        }
}

void HeapItemsNumT1()
{
        if (HeapItemsNum(NULL) != ERR_NOT_INITIALIZED)
        {
                printf("HeapItemsNum(NULL)\t\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapItemsNum(NULL)\t\t=>\tPASS\n");
        }
}

void HeapItemsNumT2()
{
        Heap *heap;
        Vector *vec;

        vec = VectorCreate(4, 4);
        heap = HeapBuild(vec);
        HeapInsert(heap, 1001);
        HeapDestroy(heap);
        if (HeapItemsNum(heap) != ERR_NOT_INITIALIZED)
        {
                printf("HeapItemsNum after heap destroy\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapItemsNum after heap destroy\t=>\tPASS\n");
        }
}

void HeapItemsNumT3()
{
        Heap *heap;
        Vector *vec;

        vec = VectorCreate(4, 4);
        heap = HeapBuild(vec);
        if (HeapItemsNum(heap) != 0)
        {
                printf("HeapItemsNum to empty heap\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapItemsNum to empty heap\t=>\tPASS\n");
        }
}

void HeapItemsNumT4()
{
        Heap *heap;
        Vector *vec;

        vec = VectorCreate(4, 4);
        heap = HeapBuild(vec);
        HeapInsert(heap, 12);
        HeapInsert(heap, 121);
        if (HeapItemsNum(heap) != 2)
        {
                printf("HeapItemsNum valid test\t\t=>\tFAIL\n");
        }
        else
        {
                printf("HeapItemsNum valid test\t\t=>\tPASS\n");
        }
}
static void HeapBuildTestNormal()
{
        Heap *heap;
        Vector *vec;
        int ExtractMax, max;
        vec = VectorCreate(4, 4);
        heap = HeapBuild(vec);
        HeapInsert(heap, 5);
        HeapInsert(heap, 39);
        HeapInsert(heap, 77);
        HeapInsert(heap, 21);
        HeapInsert(heap, 100);

        HeapPrint(heap);
}
int main()
{
        printf("\n*************************************************************\n"
               "                     heapBuild tests\n"
               "*************************************************************\n");
        heapBuildT1();
        heapBuildT2();
        heapBuildT3();
        heapBuildT4();

        printf("\n*************************************************************\n"
               "                     HeapDestroy tests\n"
               "*************************************************************\n");
        HeapDestroyT1();
        HeapDestroyT2();

        printf("\n*************************************************************\n"
               "                     HeapInsert tests\n"
               "*************************************************************\n");
        HeapInsertT1();
        HeapInsertT2();
        HeapInsertT3();
        HeapInsertT4();
        HeapInsertT5();

        printf("\n*************************************************************\n"
               "                      HeapMax tests\n"
               "*************************************************************\n");
        HeapMaxT1();
        HeapMaxT2();
        HeapMaxT3();
        HeapMaxT4();

        printf("\n*************************************************************\n"
               "                   HeapExtractMax tests\n"
               "*************************************************************\n");
        HeapExtractMaxT1();
        HeapExtractMaxT2();
        HeapExtractMaxT3();
        HeapExtractMaxT4();
        HeapExtractMaxT5();
        HeapExtractMaxT6();

        printf("\n*************************************************************\n"
               "                     HeapItemsNum tests\n"
               "*************************************************************\n");
        HeapItemsNumT1();
        HeapItemsNumT2();
        HeapItemsNumT3();
        HeapItemsNumT4();
        HeapBuildTestNormal();
}
