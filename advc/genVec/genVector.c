#include <stdlib.h>

#include "genVector.h"

struct Vector
{
        void **m_items;
        size_t m_originalSize; /* original allocated space for items */
        size_t m_size;         /* actual allocated space for items*/
        size_t m_nItems;       /* actual number of items */
        size_t m_blockSize;    /* the chunk size to be allocated when no space*/
};

static VectorResult increase(Vector *_vector);

Vector *VectorCreate(size_t _initialCapacity, size_t _blockSize)
{
        Vector *vec;

        if (_initialCapacity == 0 && _blockSize == 0)
        {
                return NULL;
        }

        if ((vec = (Vector *)malloc(sizeof(Vector))) == NULL)
        {
                return NULL;
        }

        if ((vec->m_items = (void **)malloc(_initialCapacity * sizeof(void *))) == NULL)
        {
                free(vec);
                return NULL;
        }

        vec->m_originalSize = _initialCapacity;
        vec->m_size = _initialCapacity;
        vec->m_nItems = 0;
        vec->m_blockSize = _blockSize;
        return vec;
}

void VectorDestroy(Vector **_vector, void (*_elementDestroy)(void *_item))
{
        size_t i;

        if (_vector == NULL || *_vector == NULL)
        {
                return;
        }

        if (_elementDestroy != NULL && (*_vector)->m_nItems != 0)
        {
                for (i = 0; i < (*_vector)->m_nItems; ++i)
                {
                        if ((*_vector)->m_items[i])
                        {
                                (*_elementDestroy)((*_vector)->m_items[i]);
                        }
                }
        }

        free((*_vector)->m_items);
        free(*_vector);
        *(_vector) = NULL;
}

VectorResult VectorAppend(Vector *_vector, void *_item)
{
        VectorResult result;

        if (_vector == NULL)
        {
                return VECTOR_UNINITIALIZED_ERROR;
        }

        if (_item == NULL)
        {
                return VECTOR_ITEM_UNINITIALIZED_ERROR;
        }

        if (_vector->m_nItems == _vector->m_size)
        {
                if ((result = increase(_vector)) != VECTOR_SUCCESS)
                {
                        return result;
                }
        }

        _vector->m_items[_vector->m_nItems] = _item;
        _vector->m_nItems++;

        return VECTOR_SUCCESS;
}

/* Delete item from the end. */
VectorResult VectorRemove(Vector *_vector, void **_pValue)
{
        void **tmp;

        /**add to func**/
        if (_vector == NULL || _pValue == NULL)
        {
                return VECTOR_UNINITIALIZED_ERROR;
        }

        /**add to func**/
        if (_vector->m_nItems == 0)
        {
                return VECTOR_UNDERFLOW_ERROR;
        }

        _vector->m_nItems--;
        *_pValue = _vector->m_items[(_vector->m_nItems)];

        /**add define to number=>2 **/
        if (_vector->m_size > _vector->m_originalSize && _vector->m_size - _vector->m_nItems >= _vector->m_blockSize * 2)
        {
                tmp = realloc(_vector->m_items, sizeof(void *) * (_vector->m_size - _vector->m_blockSize));
                if (tmp != NULL)
                {
                        _vector->m_items = tmp;
                        _vector->m_size -= _vector->m_blockSize;
                }
        }

        return VECTOR_SUCCESS;
}

VectorResult VectorSet(Vector *_vector, size_t _index, void *_value)
{
        if (_vector == NULL)
        {
                return VECTOR_UNINITIALIZED_ERROR;
        }

        if (_value == NULL)
        {
                return VECTOR_ITEM_UNINITIALIZED_ERROR;
        }

        if (_index >= _vector->m_nItems)
        {
                return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
        }

        _vector->m_items[_index] = _value;

        return VECTOR_SUCCESS;
}

/*getters*/
size_t VectorSize(const Vector *_vector)
{
        if (_vector == NULL)
        {
                return 0;
        }

        return _vector->m_nItems;
}

size_t VectorCapacity(const Vector *_vector)
{
        if (_vector == NULL)
        {
                return 0;
        }

        return _vector->m_size;
}

VectorResult VectorGet(const Vector *_vector, size_t _index, void **_pValue)
{
        if (_vector == NULL || _pValue == NULL)
        {
                return VECTOR_UNINITIALIZED_ERROR;
        }

        if (_index >= _vector->m_nItems)
        {
                return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
        }

        *_pValue = _vector->m_items[_index];
        return VECTOR_SUCCESS;
}

size_t VectorForEach(const Vector *_vector, VectorElementAction _action, void *_context)
{
        size_t i;

        if (_vector == NULL || _action == NULL)
        {
                return 0;
        }

        for (i = 0; i < _vector->m_nItems; i++)
        {
                if ((*_action)(_vector->m_items[i], i, _context) == 0)
                {
                        break;
                }
        }

        return i;
}

static VectorResult increase(Vector *_vector)
{
        int newSize;
        void **tmp;

        if (_vector->m_blockSize == 0)
        {
                return VECTOR_OVERFLOW_ERROR;
        }

        newSize = _vector->m_size + _vector->m_blockSize;
        if ((tmp = (void **)realloc(_vector->m_items, newSize * sizeof(void *))) == NULL)
        {
                return VECTOR_REALLOCATION_FAILED;
        }

        _vector->m_items = tmp;
        _vector->m_size = newSize;

        return VECTOR_SUCCESS;
}