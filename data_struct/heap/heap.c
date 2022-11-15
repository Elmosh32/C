#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "vector.h"
#include "heap.h"
#include "ADTDefs.h"

#define MAGIC_NUMBER 999111
#define TRUE 1
#define FALSE 0

#define PARENT(i) ((i)-1) / 2
#define LEFT_CHILD(i) (i) * 2 + 1
#define RIGHT_CHILD(i) ((i) + 1) * 2

struct Heap
{
        Vector *m_vec;
        size_t m_heapSize;
        int m_magicNum;
};

/** Auxiliary Functions **/
static void heapify(Heap *_heap, int _index);
static ADTErr isFatherGreater(Heap *_heap, int _index);
static int getVal(Heap *_heap, int _index);
static int rightSonExist(Heap *_heap, int _index);
static void bubbleUp(Heap *_heap);
static void swap(Heap *_heap, int _biggerIndex, int _smallerIndex);

Heap *HeapBuild(Vector *_vec)
{
        Heap *heap;
        size_t numOfltems;
        int i;

        if (_vec == NULL)
        {
                return NULL;
        }

        if ((heap = ((Heap *)malloc(sizeof(Heap)))) == NULL)
        {
                return NULL;
        }

        getNumOfItems(_vec, &numOfltems);
        heap->m_vec = _vec;
        heap->m_heapSize = numOfltems;
        heap->m_magicNum = MAGIC_NUMBER;

        i = PARENT(heap->m_heapSize - 1);
        while (i >= 0)
        {
                heapify(heap, i);
                i--;
        }

        return heap;
}

static void heapify(Heap *_heap, int _index)
{
        int iLeftChild;

        if (LEFT_CHILD(_index) > _heap->m_heapSize - 1)
        {
                return;
        }

        if (isFatherGreater(_heap, _index) == TRUE)
        {
                return;
        }
        else if (isFatherGreater(_heap, _index) == ERR_LEFT_SON_BIGGER)
        {
                swap(_heap, LEFT_CHILD(_index), _index);
                heapify(_heap, LEFT_CHILD(_index));
        }
        else
        {
                swap(_heap, RIGHT_CHILD(_index), _index);
                heapify(_heap, RIGHT_CHILD(_index));
        }
}

static void swap(Heap *_heap, int _biggerIndex, int _smallerIndex)
{
        int biggerVal, smallerVal;

        biggerVal = getVal(_heap, _biggerIndex);
        smallerVal = getVal(_heap, _smallerIndex);
        setVector(_heap->m_vec, _biggerIndex, smallerVal);
        setVector(_heap->m_vec, _smallerIndex, biggerVal);
}

static ADTErr isFatherGreater(Heap *_heap, int _index)
{

        if (rightSonExist(_heap, _index) == TRUE)
        {
                if ((getVal(_heap, _index) <= getVal(_heap, LEFT_CHILD(_index))) || (getVal(_heap, _index) <= getVal(_heap, RIGHT_CHILD(_index))))
                        if (getVal(_heap, LEFT_CHILD(_index)) >= getVal(_heap, RIGHT_CHILD(_index)))
                        {
                                return ERR_LEFT_SON_BIGGER;
                        }
                        else
                        {
                                return ERR_RIGHT_SON_BIGGER;
                        }
        }
        else
        {
                if (getVal(_heap, _index) <= getVal(_heap, LEFT_CHILD(_index)))
                {
                        return ERR_RIGHT_SON_BIGGER;
                }
        }
        return TRUE;
}

static int getVal(Heap *_heap, int _index)
{
        ADTErr err;
        int val;

        if (getVector(_heap->m_vec, _index, &val) == ERR_OK)
                return val;
}

static int rightSonExist(Heap *_heap, int _index)
{
        int rsIndex;
        rsIndex = RIGHT_CHILD(_index);
        if (_heap->m_heapSize >= rsIndex)
        {
                return TRUE;
        }
        else
        {
                return FALSE;
        }
}

void HeapDestroy(Heap *_heap)
{
        if (_heap == NULL || _heap->m_magicNum != MAGIC_NUMBER)
        {
                return;
        }

        _heap->m_magicNum = 0;
        free(_heap);
}

ADTErr HeapInsert(Heap *_heap, int _data)
{
        ADTErr err;
        if (_heap == NULL || _heap->m_magicNum != MAGIC_NUMBER)
        {
                return ERR_NOT_INITIALIZED;
        }

        err = VectorAdd(_heap->m_vec, _data);
        if (err != ERR_OK)
        {
                return err;
        }

        _heap->m_heapSize++;
        bubbleUp(_heap);

        return ERR_OK;
}

static void bubbleUp(Heap *_heap)
{
        int index = _heap->m_heapSize - 1;
        while (1)
        {
                if (getVal(_heap, index) > getVal(_heap, PARENT(index)))
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

ADTErr HeapMax(Heap *_heap, int *_data)
{
        if (_heap == NULL || _heap->m_magicNum != MAGIC_NUMBER || _data == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        if (_heap->m_heapSize == 0)
        {
                return ERR_UNDERFLOW;
        }

        getVector(_heap->m_vec, 0, _data);
        return ERR_OK;
}

ADTErr HeapExtractMax(Heap *_heap, int *_data)
{
        int last;

        if (_heap == NULL || _heap->m_magicNum != MAGIC_NUMBER || _data == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        if (_heap->m_heapSize == 0)
        {
                return ERR_UNDERFLOW;
        }

        if (_heap->m_heapSize > 1)
        {
                getVector(_heap->m_vec, 0, _data);
                VectorDelete(_heap->m_vec, &last);
                setVector(_heap->m_vec, 0, last);
                _heap->m_heapSize--;
                heapify(_heap, 0);
        }
        else
        {
                VectorDelete(_heap->m_vec, &last);
                _heap->m_heapSize--;
        }

        return ERR_OK;
}

size_t HeapItemsNum(Heap *_heap)
{
        if (_heap == NULL || _heap->m_magicNum != MAGIC_NUMBER)
        {
                return ERR_NOT_INITIALIZED;
        }

        return _heap->m_heapSize;
}

void HeapPrint(Heap *_heap)
{
        if (_heap == NULL || _heap->m_magicNum != MAGIC_NUMBER)
        {
                return;
        }

        VectorPrint(_heap->m_vec);
}
