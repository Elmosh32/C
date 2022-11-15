/**********************************************************************************
                                include && define
**********************************************************************************/
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "../genVec/genVector.h"
#include "genHeap.h"

#define TRUE 1
#define FALSE 0

#define PARENT(i) ((i)-1) / 2
#define LEFT_CHILD(i) (i) * 2 + 1
#define RIGHT_CHILD(i) ((i) + 1) * 2

/**********************************************************************************
                                heap struct
**********************************************************************************/
struct Heap
{
        Vector *m_vec;
        size_t m_heapSize;
        LessThanComparator m_compFunc;
};

/**********************************************************************************
                     Declaration of static Auxiliary Functions
**********************************************************************************/
static void heapify(Heap *_heap, int _index);
static int rightSonExist(Heap *_heap, int _index);
static void bubbleUp(Heap *_heap);
static void swap(Heap *_heap, int _biggerIndex, int _smallerIndex);

/**********************************************************************************
                                api Functions
**********************************************************************************/
Heap *HeapBuild(Vector *_vector, LessThanComparator _pfLess)
{
        Heap *heap;
        int i;

        if (!_vector || !_pfLess)
        {
                return NULL;
        }

        if ((heap = (Heap *)malloc(sizeof(Heap))) == NULL)
        {
                return NULL;
        }

        heap->m_vec = _vector;
        heap->m_heapSize = VectorSize(_vector);
        heap->m_compFunc = _pfLess;

        i = PARENT(heap->m_heapSize - 1);
        while (i >= 0)
        {
                heapify(heap, i);
                i--;
        }

        return heap;
}

Vector *HeapDestroy(Heap **_heap)
{
        Vector *vec;

        if (_heap == NULL || *_heap == NULL)
        {
                return NULL;
        }

        vec = (*_heap)->m_vec;
        free(*_heap);
        *_heap = NULL;

        return vec;
}

HeapResultCode HeapInsert(Heap *_heap, void *_element)
{
        VectorResult result;

        if (_heap == NULL)
        {
                return HEAP_NOT_INITIALIZED;
        }

        if (_element == NULL)
        {
                return HEAP_ELEMENT_NOT_INITIALIZED;
        }

        if ((result = VectorAppend(_heap->m_vec, _element)) == VECTOR_ALLOCATION_ERROR)
        {
                return HEAP_REALLOCATION_FAILED;
        }

        _heap->m_heapSize++;
        bubbleUp(_heap);
        return HEAP_SUCCESS;
}

const void *HeapPeek(const Heap *_heap)
{
        void *element;

        if (_heap == NULL || _heap->m_heapSize == 0)
        {
                return NULL;
        }

        VectorGet(_heap->m_vec, 0, &element);
        return element;
}

void *HeapExtract(Heap *_heap)
{
        void *element, *lastElement;

        if (_heap == NULL || _heap->m_heapSize == 0)
        {
                return NULL;
        }

        if (_heap->m_heapSize > 1)
        {
                VectorGet(_heap->m_vec, 0, &element);
                VectorRemove(_heap->m_vec, &lastElement);
                VectorSet(_heap->m_vec, 0, lastElement);
                _heap->m_heapSize--;
                heapify(_heap, 0);
        }
        else
        {
                VectorGet(_heap->m_vec, 0, &element);
                VectorRemove(_heap->m_vec, &lastElement);
                _heap->m_heapSize--;
        }

        return element;
}

size_t HeapSize(const Heap *_heap)
{
        if (_heap == NULL)
        {
                return 0;
        }

        return _heap->m_heapSize;
}

size_t HeapForEach(const Heap *_heap, ActionFunction _act, void *_context)
{
        void *item;
        size_t index;

        if (_heap == NULL || _act == NULL)
        {
                return 0;
        }

        for (index = 0; index < _heap->m_heapSize; index++)
        {
                VectorGet(_heap->m_vec, index, &item);

                if (!_act(item, _context))
                {
                        break;
                }
        }

        return index;
}

/**********************************************************************************
                        static Auxiliary Functions
**********************************************************************************/
static void heapify(Heap *_heap, int _index)
{
        void *leftVal = NULL, *rightVal = NULL, *parentVal = NULL;

        if (LEFT_CHILD(_index) > _heap->m_heapSize - 1)
        {
                return;
        }

        if (rightSonExist(_heap, _index) == TRUE)
        {
                VectorGet(_heap->m_vec, _index, &parentVal);
                VectorGet(_heap->m_vec, RIGHT_CHILD(_index), &rightVal);
                VectorGet(_heap->m_vec, LEFT_CHILD(_index), &leftVal);
                if ((_heap->m_compFunc(parentVal, rightVal)) != 0 && (_heap->m_compFunc(parentVal, leftVal)) != 0)
                {
                        return;
                }

                if ((_heap->m_compFunc(leftVal, rightVal)) != 0)
                {
                        if ((_heap->m_compFunc(leftVal, parentVal)) != 0)
                        {
                                swap(_heap, LEFT_CHILD(_index), _index);
                                heapify(_heap, LEFT_CHILD(_index));
                        }
                }

                if ((_heap->m_compFunc(rightVal, leftVal)) != 0)
                {
                        if ((_heap->m_compFunc(rightVal, parentVal)) != 0)
                        {
                                swap(_heap, RIGHT_CHILD(_index), _index);
                                heapify(_heap, RIGHT_CHILD(_index));
                        }
                }
        }
        else
        {
                VectorGet(_heap->m_vec, _index, &parentVal);
                VectorGet(_heap->m_vec, LEFT_CHILD(_index), &leftVal);

                if ((_heap->m_compFunc(leftVal, parentVal)) != 0)
                {
                        swap(_heap, LEFT_CHILD(_index), _index);
                        heapify(_heap, LEFT_CHILD(_index));
                }
        }
}

static void bubbleUp(Heap *_heap)
{
        void *currVal = NULL, *parentVal = NULL;
        int index = _heap->m_heapSize - 1;

        while (1)
        {
                VectorGet(_heap->m_vec, index, &currVal);
                VectorGet(_heap->m_vec, PARENT(index), &parentVal);
                if ((_heap->m_compFunc(currVal, parentVal)) != 0)
                {
                        swap(_heap, index, PARENT(index));
                        index = PARENT(index);
                }
                else
                {
                        break;
                }
        }
}

static int rightSonExist(Heap *_heap, int _index)
{
        int rsIndex;
        rsIndex = RIGHT_CHILD(_index);
        if (_heap->m_heapSize > rsIndex)
        {
                return TRUE;
        }
        else
        {
                return FALSE;
        }
}

static void swap(Heap *_heap, int _biggerIndex, int _smallerIndex)
{
        void *biggerVal = NULL, *smallerVal = NULL;

        VectorGet(_heap->m_vec, _biggerIndex, &biggerVal);
        VectorGet(_heap->m_vec, _smallerIndex, &smallerVal);

        VectorSet(_heap->m_vec, _biggerIndex, smallerVal);
        VectorSet(_heap->m_vec, _smallerIndex, biggerVal);
}