/**********************************************************************************
                                includes
**********************************************************************************/
#include <stdio.h>
#include "../genHeap/genHeap.h"

/**********************************************************************************
                                print Functions
**********************************************************************************/
int PrintVector(void *_element, size_t _index, void *_context)
{
        printf("%d ", *((int *)_element));
        return 1;
}

int PrintInt(const void *_elem, void *_context)
{
        printf("%d\t", *(int *)_elem);
        return 1;
}

/**********************************************************************************
                             different heap types
**********************************************************************************/
int MaxIntHeap(const void *_left, const void *_right)
{
        return *(int *)_left > *(int *)_right;
}

int MinIntHeap(const void *_left, const void *_right)
{
        return *(int *)_left < *(int *)_right;
}

/**********************************************************************************
                     Declaration of static test functions
**********************************************************************************/
static void HeapBuildTests();
static void NullHeapBuild();
static void EmptyVecHeapBuild();
static void ValidHeapBuild();
static void MinHeapBuild();
static void MaxHeapBuild();

static void HeapDestroyTests();
static void NullHeapDestroy();
static void DoubleHeapDestroy();

static void HeapSizeTests();
static void NullHeapSize();
static void EmptyHeapSize();
static void ValidHeapSize();
static void HeapSizeAfterInsert();
static void HeapSizeAfterExtract();

static void HeapInsertTests();
static void ValidHeapInsert();
static void NullHeapInsert();
static void HeapInsertToEmpty();

static void HeapPeekTests();
static void NullHeapPeek();
static void EmptyHeapPeek();

static void HeapExtractTests();
static void ValidHeapExtract();
static void NullHeapExtract();
static void EmptyHeapExtract();

int HeapTest()
{

        HeapBuildTests();

        HeapDestroyTests();

        HeapSizeTests();

        HeapInsertTests();

        HeapPeekTests();

        HeapExtractTests();

        return 0;
}

/**********************************************************************************
                             test functions
**********************************************************************************/
static void HeapBuildTests()
{
        printf("\n*********************************************************************\n"
               "**************************Heap Build Tests***************************\n"
               "*********************************************************************\n");
        NullHeapBuild();
        EmptyVecHeapBuild();
        ValidHeapBuild();
        MinHeapBuild();
        MaxHeapBuild();
}

static void NullHeapBuild()
{
        if (HeapBuild(NULL, MaxIntHeap) == NULL)
        {
                printf("HeapBuild for NULL\t=>\tpass\n");
        }
        else
        {
                printf("HeapBuild for NULL\t=>\tfail\n");
        }
}

static void EmptyVecHeapBuild()
{
        Vector *vec;
        Heap *heap;

        vec = VectorCreate(2, 2);

        if ((heap = HeapBuild(vec, MaxIntHeap)) != NULL)
        {
                printf("HeapBuild for empty vector\t=>\tpass\n");
        }
        else
        {
                printf("HeapBuild for empty vector\t=>\tfail\n");
        }

        VectorDestroy(&vec, NULL);
        HeapDestroy(&heap);
}

static void ValidHeapBuild()
{
        Vector *vec;
        Heap *heap;

        int data1 = 100;
        int data2 = 39;
        int data3 = 77;

        vec = VectorCreate(2, 3);
        VectorAppend(vec, &data1);
        VectorAppend(vec, &data2);
        VectorAppend(vec, &data3);

        heap = HeapBuild(vec, MaxIntHeap);

        if (heap != NULL)
        {
                printf("valid HeapBuild\t=>\tpass\n");
        }
        else
        {
                printf("valid HeapBuild\t=>\tfail\n");
        }

        VectorDestroy(&vec, NULL);
        HeapDestroy(&heap);
}

static void MinHeapBuild()
{
        Vector *vec = NULL;
        Heap *heap = NULL;
        void *min;
        int data1 = 100;
        int data2 = 39;
        int data3 = 77;
        int data4 = 5;
        int data5 = 21;
        int data6 = 40;
        int data7 = 41;

        vec = VectorCreate(2, 3);
        VectorAppend(vec, &data4);
        VectorAppend(vec, &data2);
        VectorAppend(vec, &data3);
        VectorAppend(vec, &data5);
        VectorAppend(vec, &data1);
        VectorAppend(vec, &data6);
        VectorAppend(vec, &data7);

        heap = HeapBuild(vec, MinIntHeap);

        min = HeapExtract(heap);
        if (*(int *)min == 5)
        {
                printf("HeapBuild min heap\t=>\tpass\n");
        }
        else
        {
                printf("HeapBuild min heap\t=>\tfail\n");
        }

        VectorDestroy(&vec, NULL);
        HeapDestroy(&heap);
}

static void MaxHeapBuild()
{
        Vector *vec = NULL;
        Heap *heap = NULL;
        void *max;
        int data1 = 100;
        int data2 = 39;
        int data3 = 77;
        int data4 = 5;
        int data5 = 21;
        int data6 = 40;
        int data7 = 41;

        vec = VectorCreate(2, 3);
        VectorAppend(vec, &data4);
        VectorAppend(vec, &data2);
        VectorAppend(vec, &data3);
        VectorAppend(vec, &data5);
        VectorAppend(vec, &data1);
        VectorAppend(vec, &data6);
        VectorAppend(vec, &data7);

        heap = HeapBuild(vec, MaxIntHeap);

        max = HeapExtract(heap);
        if (*(int *)max == 100)
        {
                printf("HeapBuild maxx heap\t=>\tpass\n");
        }
        else
        {
                printf("HeapBuild max heap\t=>\tfail\n");
        }

        VectorDestroy(&vec, NULL);
        HeapDestroy(&heap);
}

static void HeapDestroyTests()
{
        printf("\n*********************************************************************\n"
               "**************************Heap Destroy Tests*************************\n"
               "*********************************************************************\n");
        NullHeapDestroy();
        DoubleHeapDestroy();
}

static void NullHeapDestroy()
{
        Vector *vec = NULL;
        vec = HeapDestroy(NULL);

        if (vec == NULL)
        {
                printf("Null HeapDestroy\t=>\tpass\n");
        }
        else
        {
                printf("Null HeapDestroy\t=>\tfail\n");
        }
}

static void DoubleHeapDestroy()
{
        Vector *vec = NULL;
        Vector *destroyVec = NULL;
        Heap *heap = NULL;
        int data1 = 100;
        int data2 = 39;
        int data3 = 77;
        int data4 = 5;

        vec = VectorCreate(2, 3);
        VectorAppend(vec, &data4);
        VectorAppend(vec, &data2);
        VectorAppend(vec, &data3);
        VectorAppend(vec, &data1);

        heap = HeapBuild(vec, MaxIntHeap);

        VectorDestroy(&vec, NULL);
        destroyVec = HeapDestroy(&heap);
        destroyVec = HeapDestroy(&heap);

        if (destroyVec == NULL)
        {
                printf("Null HeapDestroy\t=>\tpass\n");
        }
        else
        {
                printf("Null HeapDestroy\t=>\tfail\n");
        }
        printf("double HeapDestroy\t=>\tpass\n");
}

static void HeapSizeTests()
{
        printf("\n*********************************************************************\n"
               "****************************Heap Size Tests**************************\n"
               "*********************************************************************\n");
        NullHeapDestroy();
        NullHeapSize();
        EmptyHeapSize();
        ValidHeapSize();
        HeapSizeAfterInsert();
        HeapSizeAfterExtract();
}

static void NullHeapSize()
{
        if (HeapSize(NULL) == 0)
        {
                printf("Null HeapSize\t=>\tpass\n");
        }
        else
        {
                printf("Null HeapSize\t=>\tfail\n");
        }
}

static void EmptyHeapSize()
{
        Vector *vec;
        Heap *heap;

        vec = VectorCreate(2, 3);

        heap = HeapBuild(vec, MaxIntHeap);

        if (HeapSize(heap) == 0)
        {
                printf("HeapSize for empty heap\t=>\tpass\n");
        }
        else
        {
                printf("HeapSize for empty heap\t=>\tfail\n");
        }

        VectorDestroy(&vec, NULL);
        HeapDestroy(&heap);
}

static void ValidHeapSize()
{
        Vector *vec;
        Heap *heap;
        int data1 = 100;
        int data2 = 39;
        int data3 = 77;
        int data4 = 5;

        vec = VectorCreate(2, 3);
        VectorAppend(vec, &data4);
        VectorAppend(vec, &data2);
        VectorAppend(vec, &data3);
        VectorAppend(vec, &data1);

        heap = HeapBuild(vec, MaxIntHeap);

        if (HeapSize(heap) == 4)
        {
                printf("HeapSize valid test\t=>\tpass\n");
        }
        else
        {
                printf("HeapSize valid test\t=>\tfail\n");
        }

        VectorDestroy(&vec, NULL);
        HeapDestroy(&heap);
}

static void HeapSizeAfterInsert()
{
        Vector *vec;
        Heap *heap;
        int data1 = 100;
        int data2 = 39;
        int data3 = 77;
        int data4 = 5;

        vec = VectorCreate(2, 3);
        VectorAppend(vec, &data4);
        VectorAppend(vec, &data2);
        VectorAppend(vec, &data3);

        heap = HeapBuild(vec, MaxIntHeap);

        HeapInsert(heap, &data1);

        if (HeapSize(heap) == 4)
        {
                printf("HeapSize After Insert\t=>\tpass\n");
        }
        else
        {
                printf("HeapSize After Insert\t=>\tfail\n");
        }

        VectorDestroy(&vec, NULL);
        HeapDestroy(&heap);
}

static void HeapSizeAfterExtract()
{
        Vector *vec;
        Heap *heap;
        int data1 = 100;
        int data2 = 39;
        int data3 = 77;
        int data4 = 5;

        vec = VectorCreate(2, 3);
        VectorAppend(vec, &data4);
        VectorAppend(vec, &data2);
        VectorAppend(vec, &data3);
        VectorAppend(vec, &data1);

        heap = HeapBuild(vec, MaxIntHeap);

        HeapExtract(heap);

        if (HeapSize(heap) == 3)
        {
                printf("HeapSize After Extract\t=>\tpass\n");
        }
        else
        {
                printf("HeapSize After Extract\t=>\tfail\n");
        }

        VectorDestroy(&vec, NULL);
        HeapDestroy(&heap);
}

static void HeapInsertTests()
{
        printf("\n*********************************************************************\n"
               "**************************Heap Insert Tests**************************\n"
               "*********************************************************************\n");
        ValidHeapInsert();
        NullHeapInsert();
        HeapInsertToEmpty();
}

static void NullHeapInsert()
{
        HeapResultCode result;
        int data1 = 100;

        if ((result = HeapInsert(NULL, &data1)) == HEAP_NOT_INITIALIZED)
        {
                printf("Null HeapInsert\t=>\tpass\n");
        }
        else
        {
                printf("Null HeapInsert\t=>\tfail\n");
        }
}

static void HeapInsertToEmpty()
{
        HeapResultCode result;
        Vector *vec;
        Heap *heap;
        int data1 = 100;

        vec = VectorCreate(2, 3);

        heap = HeapBuild(vec, MaxIntHeap);

        result = HeapInsert(heap, &data1);

        if (result == HEAP_SUCCESS)
        {
                printf("HeapInsert to empty heap\t=>\tpass\n");
        }
        else
        {
                printf("HeapInsert to empty heap\t=>\tfail\n");
        }

        VectorDestroy(&vec, NULL);
        HeapDestroy(&heap);
}

static void ValidHeapInsert()
{
        HeapResultCode result;
        Vector *vec;
        Heap *heap;
        int data1 = 100;
        int data2 = 39;
        int data3 = 77;
        int data4 = 5;
        int data5 = 51;

        vec = VectorCreate(2, 3);
        VectorAppend(vec, &data4);
        VectorAppend(vec, &data2);
        VectorAppend(vec, &data3);
        VectorAppend(vec, &data1);

        heap = HeapBuild(vec, MaxIntHeap);

        result = HeapInsert(heap, &data5);

        if (result == HEAP_SUCCESS)
        {
                printf("HeapInsert valid test\t=>\tpass\n");
        }
        else
        {
                printf("HeapInsert valid test\t=>\tfail\n");
        }

        VectorDestroy(&vec, NULL);
        HeapDestroy(&heap);
}

static void HeapPeekTests()
{
        printf("\n*********************************************************************\n"
               "***************************Heap Peek Tests***************************\n"
               "*********************************************************************\n");
        NullHeapPeek();
        EmptyHeapPeek();
}

static void NullHeapPeek()
{
        const void *max;

        max = HeapPeek(NULL);

        if (max == NULL)
        {
                printf("Null HeapPeek\t=>\tpass\n");
        }
        else
        {
                printf("Null HeapPeek\t=>\tfail\n");
        }
}

static void EmptyHeapPeek()
{
        Vector *vec;
        Heap *heap;
        const void *max;

        vec = VectorCreate(2, 3);

        heap = HeapBuild(vec, MaxIntHeap);

        max = HeapPeek(heap);

        if (max == NULL)
        {
                printf("HeapPeek empty heap\t=>\tpass\n");
        }
        else
        {
                printf("HeapPeek empty heap\t=>\tfail\n");
        }

        VectorDestroy(&vec, NULL);
        HeapDestroy(&heap);
}

static void HeapExtractTests()
{
        printf("\n*********************************************************************\n"
               "**************************Heap Extract Tests*************************\n"
               "*********************************************************************\n");
        ValidHeapExtract();
        NullHeapExtract();
        EmptyHeapExtract();
}

static void NullHeapExtract()
{
        void *max;

        max = HeapExtract(NULL);

        if (max == NULL)
        {
                printf("Null HeapExtract\t=>\tpass\n");
        }
        else
        {
                printf("Null HeapExtract\t=>\tfail\n");
        }
}

static void EmptyHeapExtract()
{
        Vector *vec;
        Heap *heap;
        void *max;

        vec = VectorCreate(2, 7);

        heap = HeapBuild(vec, MaxIntHeap);

        max = HeapExtract(heap);

        if (max == NULL)
        {
                printf("HeapExtract to empty heap\t=>\tpass\n");
        }
        else
        {
                printf("HeapExtract to empty heap\t=>\tfail\n");
        }

        VectorDestroy(&vec, NULL);
        HeapDestroy(&heap);
}

static void ValidHeapExtract()
{
        Vector *vec;
        Heap *heap;
        void *max;
        int data1 = 100;
        int data2 = 39;
        int data3 = 77;
        int data4 = 5;

        vec = VectorCreate(2, 3);
        VectorAppend(vec, &data4);
        VectorAppend(vec, &data2);
        VectorAppend(vec, &data3);
        VectorAppend(vec, &data1);

        heap = HeapBuild(vec, MaxIntHeap);

        max = HeapExtract(heap);

        if (*(int *)max == 100)
        {
                printf("HeapExtract valid test\t=>\tpass\n");
        }
        else
        {
                printf("HeapExtract valid test\t=>\tfail\n");
        }

        VectorDestroy(&vec, NULL);
        HeapDestroy(&heap);
}