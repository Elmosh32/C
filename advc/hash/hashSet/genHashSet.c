
/**********************************************************************************
                                includes && define
**********************************************************************************/
#include <stdlib.h> /*malloc*/
#include <stdio.h>
#include <stddef.h> /*size_t*/
#include <math.h>   /*sqrt*/

#include "genHashSet.h"

#define PERCENTAGE 1.3
#define FALSE 0
#define TRUE 1

/**********************************************************************************
                                HashSet struct
**********************************************************************************/

struct Hash
{
    void **m_data;
    char *m_state;
    size_t (*m_hashFunction)(void *_data);
    int (*m_equalityFunction)(void *_firstData, void *_secondData);
    size_t m_hashSize;              /*original size given by the client*/
    size_t m_capacity;              /*real hash size */
    size_t m_numOfItems;            /*number of occupied places in the table*/
    size_t m_maxOfRehashOperations; /*maximum amount of rehash operations which have been done over one insertion*/
    size_t m_counterOfInsertions;   /*total amount of insertions into the table*/
    size_t m_allRehashOperations;   /*all rehash operations mutual counter*/
};

typedef enum State
{
    ABSOLUTE_EMPTY = 0,
    NOT_EMPTY = 1,
    EMPTY_BUT_NOT_ABSOLUTE = 2
} State;

/**********************************************************************************
                     Declaration of static Auxiliary Functions
**********************************************************************************/
static size_t getHashTableSize(size_t _capacity);
static int IsPrimeNumber(size_t _num);
static void DestroyCells(Hash *_hash, void (*_keyDestroy)(void *_data));
static size_t ReHash(size_t _index, size_t _size);

/**********************************************************************************
                                    api functions
**********************************************************************************/
Hash *HashCreate(size_t _size, size_t (*_hashFunction)(void *), int (*_equalityFunction)(void *, void *))
{
    Hash *hash = NULL;
    char *state = NULL;
    size_t newSize;
    if (_hashFunction == NULL || _equalityFunction == NULL)
    {
        return NULL;
    }

    if (_size == 0)
    {
        return NULL;
    }

    if ((hash = (Hash *)malloc(sizeof(Hash))) == NULL)
    {
        return NULL;
    }

    newSize = getHashTableSize(_size);

    if ((hash->m_data = (void **)malloc(newSize * sizeof(void *))) == NULL)
    {
        free(hash);
        return NULL;
    }

    if ((state = (char *)calloc(newSize, sizeof(char))) == NULL)
    {
        free(hash->m_data);
        free(hash);
        return NULL;
    }

    hash->m_state = state;
    hash->m_hashFunction = _hashFunction;
    hash->m_equalityFunction = _equalityFunction;
    hash->m_hashSize = _size;
    hash->m_capacity = newSize;
    hash->m_numOfItems = 0;
    hash->m_maxOfRehashOperations = 0;
    hash->m_counterOfInsertions = 0;
    hash->m_allRehashOperations = 0;

    return hash;
}

void HashDestroy(Hash **_hash, void (*_keyDestroy)(void *_data))
{
    if (_hash == NULL || *_hash == NULL)
    {
        return;
    }

    if (_keyDestroy)
    {
        DestroyCells(*_hash, _keyDestroy);
    }

    free((*_hash)->m_data);
    free((*_hash)->m_state);
    free(*_hash);

    *_hash = NULL;
}

HashSet_Result HashInsert(Hash *_hash, void *_data)
{
    size_t reHashCounter = 0, index, flag = 0;

    if (_hash == NULL || _data == NULL)
    {
        return SET_UNINITIALIZED;
    }

    if (_hash->m_capacity == _hash->m_numOfItems)
    {
        return SET_OVERFLOW;
    }

    if (HashIsFound(_hash, _data) == SET_KEY_DUPLICATE)
    {
        return SET_KEY_DUPLICATE;
    }

    index = _hash->m_hashFunction(_data) % _hash->m_capacity;
    while (1)
    {
        if (_hash->m_state[index] != NOT_EMPTY)
        {
            _hash->m_data[index] = _data;
            _hash->m_state[index] = NOT_EMPTY;

            _hash->m_numOfItems++;
            _hash->m_counterOfInsertions++;
            break;
        }

        _hash->m_allRehashOperations++;
        reHashCounter++;

        index = ReHash(index, _hash->m_capacity);
    }

    if (_hash->m_maxOfRehashOperations < reHashCounter)
    {
        _hash->m_maxOfRehashOperations = reHashCounter;
    }

    return SET_SUCCESS;
}

HashSet_Result HashRemove(Hash *_hash, void *_key, void **_data)
{
    size_t reHashCounter, index;

    if (_hash == NULL || _key == NULL || _data == NULL)
    {
        return SET_UNINITIALIZED;
    }

    index = _hash->m_hashFunction(_key) % _hash->m_capacity;

    for (reHashCounter = 0; reHashCounter <= _hash->m_maxOfRehashOperations; reHashCounter++)
    {
        if (_hash->m_state[index] == NOT_EMPTY && _hash->m_equalityFunction(_hash->m_data[index], _key))
        {
            *_data = _hash->m_data[index];
            _hash->m_state[index] = EMPTY_BUT_NOT_ABSOLUTE;

            _hash->m_numOfItems--;

            return SET_SUCCESS;
        }
        else if (_hash->m_state[index] == ABSOLUTE_EMPTY)
        {
            break;
        }

        index = ReHash(index, _hash->m_capacity);
    }

    return SET_KEY_NOT_FOUND;
}

int HashIsFound(const Hash *_hash, void *_key)
{
    size_t reHashCount, index;

    if (_hash == NULL || _key == NULL)
    {
        return SET_UNINITIALIZED;
    }

    index = _hash->m_hashFunction(_key) % _hash->m_capacity;

    for (reHashCount = 0; reHashCount <= _hash->m_maxOfRehashOperations; reHashCount++)
    {
        if (_hash->m_state[index] == NOT_EMPTY && _hash->m_equalityFunction(_hash->m_data[index], _key) == 1)
        {
            return SET_KEY_DUPLICATE;
        }
        else if (_hash->m_state[index] == ABSOLUTE_EMPTY)
        {
            break;
        }

        index = ReHash(index, _hash->m_capacity);
    }

    return SET_KEY_NOT_FOUND;
}

size_t HashNumOfItems(const Hash *_hash)
{
    if (_hash == NULL)
    {
        return SET_UNINITIALIZED;
    }

    return _hash->m_numOfItems;
}

size_t HashCapacity(const Hash *_hash)
{
    if (_hash == NULL)
    {
        return SET_UNINITIALIZED;
    }

    return _hash->m_hashSize;
}

double HashAverageRehashes(const Hash *_hash)
{
    if (_hash == NULL)
    {
        return SET_UNINITIALIZED;
    }

    if (_hash->m_counterOfInsertions > 0)
    {
        return ((double)_hash->m_allRehashOperations / _hash->m_counterOfInsertions);
    }

    return 0;
}

size_t HashMaxReHash(const Hash *_hash)
{
    if (_hash == NULL)
    {
        return SET_UNINITIALIZED;
    }

    return _hash->m_maxOfRehashOperations;
}

void HashPrint(const Hash *_hash, void (*PrintKey)(void *))
{
    size_t i;

    if (_hash == NULL || PrintKey == NULL)
    {
        return;
    }

    for (i = 0; i < _hash->m_capacity; i++)
    {

        if (_hash->m_state[i] == NOT_EMPTY)
        {
            PrintKey(_hash->m_data[i]);
        }
    }
}

/*The hash table size:
The hash table array should have 1.3 times the total number of keys, and its length should be a prime number.
This will greatly reduce the likelihood of collisions in the hash table.*/
static size_t getHashTableSize(size_t _size)
{
    size_t newSize = _size * PERCENTAGE;

    while (1)
    {

        if (IsPrimeNumber(newSize) == TRUE)
        {
            break;
        }

        newSize++;
    }

    return newSize;
}

static int IsPrimeNumber(size_t _num)
{
    size_t i;

    for (i = 2; i <= sqrt(_num); i++)
    {
        if (_num % i == 0)
        {
            return FALSE;
        }
    }

    return TRUE;
}

static void DestroyCells(Hash *_hash, void (*_keyDestroy)(void *_data))
{
    size_t i;

    for (i = 0; i < _hash->m_capacity; i++)
    {
        if (_hash->m_state[i] == NOT_EMPTY)
        {
            _keyDestroy(_hash->m_data[i]);
        }
    }
}

static size_t ReHash(size_t _index, size_t _size)
{
    return ((_index % _size) + 1);
}