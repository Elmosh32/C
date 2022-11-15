#include <stdio.h>
#include <stdlib.h>

#include "../includes/vector.h"
#include "../includes/ADTDefs.h"

#define MAGIC_NUMBER 6534445

struct Vector
{
        int *m_items;
        size_t m_originalSize; /* original allocated space for items */
        size_t m_size;         /* actual allocated space for items*/
        size_t m_nItems;       /* actual number of items */
        size_t m_blockSize;    /* the chunk size to be allocated when no space*/
        int m_magicNum;
};

Vector *VectorCreate(size_t _initialSize, size_t _extensionBlockSize)
{
        struct Vector *vec;
        int *vArr;

        if (_initialSize == 0 && _extensionBlockSize == 0)
                return NULL;
        if ((vec = (struct Vector *)malloc(sizeof(struct Vector))) == NULL)
                return NULL;
        if ((vArr = (int *)malloc(_initialSize * sizeof(int))) == NULL)
        {
                free(vec);
                return NULL;
        }

        vec->m_items = vArr;
        vec->m_originalSize = _initialSize;
        vec->m_size = _initialSize;
        vec->m_nItems = 0;
        vec->m_blockSize = _extensionBlockSize;
        vec->m_magicNum = MAGIC_NUMBER;
        return vec;
}

void VectorDestroy(Vector *_vector)
{
        if (_vector == NULL || _vector->m_magicNum != MAGIC_NUMBER)
        {
                return;
        }

        _vector->m_magicNum = 0;
        free(_vector->m_items);
        free(_vector);
}

/* Add item to end. */
ADTErr VectorAdd(Vector *_vector, int _item)
{
        ADTErr result;
        if (_vector == NULL)
                return ERR_NOT_INITIALIZED;

        if (_vector->m_nItems == _vector->m_size)
        {
                if ((result = increase(_vector)) != ERR_OK)
                {
                        return result;
                }
        }

        _vector->m_items[_vector->m_nItems] = _item;
        _vector->m_nItems++;

        return ERR_OK;
}

ADTErr increase(Vector *_vector)
{
        int *tmp, newSize;

        if (_vector->m_blockSize == 0)
        {
                return ERR_OVERFLOW;
        }
        newSize = _vector->m_size + _vector->m_blockSize;

        if ((tmp = (int *)realloc(_vector->m_items, newSize * sizeof(int))) == NULL)
        {
                return ERR_REALLOCATION_FAILED;
        }

        _vector->m_items = tmp;
        _vector->m_size = newSize;

        return ERR_OK;
}

/* Delete item from the end. */
ADTErr VectorDelete(Vector *_vector, int *_item)
{
        Vector *vec = NULL;
        int *tmp = NULL;
        if (_vector == NULL || _item == NULL)
                return ERR_NOT_INITIALIZED;

        if (_vector->m_nItems == 0)
                return ERR_UNDERFLOW;

        if (_vector->m_size > _vector->m_originalSize && _vector->m_size - _vector->m_nItems >= _vector->m_blockSize * 2)
        {
                tmp = (int *)realloc(_vector->m_items, _vector->m_size - _vector->m_blockSize);
                if (tmp != NULL)
                {
                        _vector->m_items = vec->m_items;
                        _vector->m_size -= _vector->m_blockSize;
                }
        }

        *_item = _vector->m_items[(_vector->m_nItems - 1)];
        _vector->m_nItems--;

        return ERR_OK;
}

ADTErr setVector(Vector *_vector, size_t _index, int _item)
{
        if (_vector == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        if (_index >= _vector->m_nItems)
        {
                return ERR_WRONG_INDEX;
        }

        _vector->m_items[_index] = _item;

        return ERR_OK;
}
/*getters*/
ADTErr getNumOfItems(Vector *_vector, size_t *_numOfItems)
{
        if (_vector == NULL)
        {
                *_numOfItems = 0;
                return ERR_GENERAL;
        }

        *_numOfItems = _vector->m_nItems;
        return ERR_OK;
}

ADTErr getMagicNum(Vector *_vector, int *_magicNum)
{
        if (_vector == NULL)
        {
                return ERR_GENERAL;
        }
        *_magicNum = _vector->m_magicNum;
        return ERR_OK;
}

ADTErr getVector(Vector *_vector, size_t _index, int *_item)
{
        if (_vector == NULL || _item == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }
        if (_index >= _vector->m_nItems)
        {
                return ERR_WRONG_INDEX;
        }

        *_item = _vector->m_items[_index];
        return ERR_OK;
}

void VectorPrint(Vector *_vector)
{
        size_t i;

        if (_vector == NULL || _vector->m_magicNum != MAGIC_NUMBER || _vector->m_nItems == 0)
        {
                return;
        }

        for (i = 0; i < _vector->m_nItems - 1; i++)
        {
                printf("%d->  ", _vector->m_items[i]);
        }
        printf("%d\n", _vector->m_items[_vector->m_nItems - 1]);
}
