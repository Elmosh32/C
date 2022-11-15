
/**********************************************************************************
                                includes && define
**********************************************************************************/
#include <stdlib.h> /*malloc*/
#include <stdio.h>
#include <stddef.h> /*size_t*/
#include <math.h>   /*sqrt*/

#include "genHashMap.h"
#include "../../genDoubleList/list_functions.h"

#define FALSE 0
#define TRUE 1

/**********************************************************************************
                                HashMap struct
**********************************************************************************/
typedef struct Data Data;
typedef struct forEachData forEachData;

struct HashMap
{
    List **m_data;
    size_t (*m_hashFunction)(const void *_data);
    int (*m_equalityFunction)(void *_firstData, void *_secondData);
    size_t m_capacity;   /*real hash size */
    size_t m_numOfItems; /*number of occupied places in the table*/
};

struct Data
{
    void *m_key;
    void *m_value;
};

struct forEachData
{
    KeyValueActionFunction m_KeyValueFunc;
    void *m_context;
};

/**********************************************************************************
                     Declaration of static Auxiliary Functions
**********************************************************************************/
static size_t getHashTableSize(size_t _capacity);
static int IsPrimeNumber(size_t _num);
static void DestroyElements(List *_list, void (*_keyDestroy)(void *_key), void (*_valDestroy)(void *_value));
static void DestroyData(Data *_data, void (*_keyDestroy)(void *_key), void (*_valDestroy)(void *_value));
static ListItr FindKey(const HashMap *_map, const void *_keyToFind, size_t _index);
static int PredicateFunc(Data *_data, forEachData *_forEachData);

/**********************************************************************************
                                    api functions
**********************************************************************************/
HashMap *HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
    HashMap *hash = NULL;
    size_t newSize;

    if (_hashFunc == NULL || _keysEqualFunc == NULL)
    {
        return NULL;
    }

    if (_capacity < MIN_SIZE)
    {
        return NULL;
    }

    if ((hash = (HashMap *)malloc(sizeof(HashMap))) == NULL)
    {
        return NULL;
    }

    newSize = getHashTableSize(_capacity);
    if ((hash->m_data = (List **)calloc(newSize, sizeof(List *))) == NULL)
    {
        free(hash);
        return NULL;
    }

    hash->m_capacity = newSize;
    hash->m_hashFunction = _hashFunc;
    hash->m_equalityFunction = _keysEqualFunc;
    hash->m_numOfItems = 0;

    return hash;
}

void HashMap_Destroy(HashMap **_map, void (*_keyDestroy)(void *_key), void (*_valDestroy)(void *_value))
{
    int i;

    if (_map == NULL || *_map == NULL)
    {
        return;
    }

    for (i = 0; i < (*_map)->m_capacity; i++)
    {
        if ((*_map)->m_data[i])
        {
            DestroyElements((*_map)->m_data[i], _keyDestroy, _valDestroy);
            ListDestroy(&((*_map)->m_data[i]), NULL);
        }
    }

    free((*_map)->m_data);
    free(*_map);
    *_map = NULL;
}

/**
Map_Result HashMap_Rehash(HashMap *_map, size_t newCapacity)
{
}
**/

Map_Result HashMap_Insert(HashMap *_map, const void *_key, const void *_value)
{
    size_t index;
    Data *data = NULL;

    if (_map == NULL)
    {
        return MAP_UNINITIALIZED_ERROR;
    }

    if (_key == NULL)
    {
        return MAP_KEY_NULL_ERROR;
    }

    index = _map->m_hashFunction(_key) % _map->m_capacity;
    if (_map->m_data[index] == NULL)
    {
        _map->m_data[index] = ListCreate();
        if (_map->m_data[index] == NULL)
        {
            return MAP_ALLOCATION_ERROR;
        }
    }
    else
    {
        if (FindKey(_map, _key, index) != NULL)
        {
            return MAP_KEY_DUPLICATE_ERROR;
        }
    }

    if ((data = (Data *)malloc(sizeof(Data))) == NULL)
    {
        return MAP_ALLOCATION_ERROR;
    }

    data->m_key = (void *)_key;
    data->m_value = (void *)_value;

    if (ListPushTail(_map->m_data[index], data) != LIST_SUCCESS)
    {
        free(data);
        return MAP_ALLOCATION_ERROR;
    }

    _map->m_numOfItems++;

    return MAP_SUCCESS;
}

Map_Result HashMap_Remove(HashMap *_map, const void *_searchKey, void **_pKey, void **_pValue)
{
    ListItr found;
    Data *data;
    size_t index;

    if (_map == NULL)
    {
        return MAP_UNINITIALIZED_ERROR;
    }

    if (_searchKey == NULL)
    {
        return MAP_KEY_NULL_ERROR;
    }

    if (_map->m_numOfItems == 0)
    {
        return MAP_EMPTY_ERROR;
    }

    index = _map->m_hashFunction(_searchKey) % _map->m_capacity;
    if ((found = FindKey(_map, _searchKey, index)) == NULL)
    {
        return MAP_KEY_NOT_FOUND_ERROR;
    }

    data = (Data *)ListItrRemove(found);

    *_pValue = data->m_value;
    *_pKey = data->m_key;

    DestroyData(data, NULL, NULL);
    _map->m_numOfItems--;

    return MAP_SUCCESS;
}

Map_Result HashMap_Find(const HashMap *_map, const void *_key, void **_pValue)
{
    ListItr found;
    size_t index;

    if (_map == NULL)
    {
        return MAP_UNINITIALIZED_ERROR;
    }

    if (_key == NULL)
    {
        return MAP_KEY_NULL_ERROR;
    }

    if (_map->m_numOfItems == 0)
    {
        return MAP_EMPTY_ERROR;
    }

    index = _map->m_hashFunction(_key) % _map->m_capacity;
    if ((found = FindKey(_map, _key, index)) == NULL)
    {
        return MAP_KEY_NOT_FOUND_ERROR;
    }

    *_pValue = ((Data *)ListItrGet(found))->m_value;

    return MAP_SUCCESS;
}

size_t HashMap_Size(const HashMap *_map)
{
    if (_map == NULL)
    {
        return 0;
    }

    return _map->m_numOfItems;
}

size_t HashMap_ForEach(const HashMap *_map, KeyValueActionFunction _action, void *_context)
{
    size_t i, count = 0;
    ListItr begin, end;
    void *data;

    if (_map == NULL || _action == NULL)
    {
        return 0;
    }

    for (i = 0; i < _map->m_capacity; i++)
    {
        begin = ListItrBegin(_map->m_data[i]);
        end = ListItrEnd(_map->m_data[i]);
        while (begin != end)
        {
            data = ListItrGet(begin);
            /**printf("hash[%ld]-index:%ld\t", i, indexCounter);**/
            if (_action(((Data *)data)->m_key, ((Data *)data)->m_value, _context) == 0)
            {
                break;
            }
            count++;
            /**indexCounter++;**/
            begin = ListItrNext(begin);
        }
    }
    return count;
}

/**
Map_Stats HashMap_GetStatistics(const HashMap *_map)
{
}
**/

/**********************************************************************************
                            HashMap_Create Auxiliary Functions
**********************************************************************************/
static size_t getHashTableSize(size_t _size)
{
    size_t newSize = _size;

    while (TRUE)
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

/**********************************************************************************
                            HashMap_Destroy Auxiliary Functions
**********************************************************************************/
static void DestroyElements(List *_list, void (*_keyDestroy)(void *_key), void (*_valDestroy)(void *_value))
{
    ListItr end, itr;
    Data *data = NULL;

    itr = ListItrBegin(_list);
    end = ListItrEnd(_list);

    while (ListItrEquals(itr, end) == 0)
    {
        data = (Data *)ListItrGet(itr);
        DestroyData(data, _keyDestroy, _valDestroy);
        itr = ListItrNext(itr);
    }
}

/**********************************************************************************
                            HashMap_Destroy Auxiliary Function
                            HashMap_Remove  Auxiliary Function
**********************************************************************************/
static void DestroyData(Data *_data, void (*_keyDestroy)(void *_key), void (*_valDestroy)(void *_value))
{
    if (_keyDestroy)
    {
        _keyDestroy(_data->m_key);
    }

    if (_valDestroy)
    {
        _valDestroy(_data->m_value);
    }

    free(_data);
}

/**********************************************************************************
                            HashMap_Insert  Auxiliary Function
                            HashMap_Remove  Auxiliary Function
                            HashMap_Find    Auxiliary Function
**********************************************************************************/
static ListItr FindKey(const HashMap *_map, const void *_keyToFind, size_t _index)
{
    ListItr end, itr;
    void *data = NULL;

    itr = ListItrBegin(_map->m_data[_index]);
    end = ListItrEnd(_map->m_data[_index]);

    while (itr != end)
    {
        data = ListItrGet(itr);
        if (data != NULL)
        {
            if (_map->m_equalityFunction((void *)((Data *)data)->m_key, (void *)_keyToFind) != 0)
            {
                return itr;
            }
        }

        itr = ListItrNext(itr);
    }

    return NULL;
}

static int PredicateFunc(Data *_data, forEachData *_forEachData)
{
    return _forEachData->m_KeyValueFunc(_data->m_key, _data->m_value, _forEachData->m_context);
}