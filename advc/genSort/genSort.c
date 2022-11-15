#include <stdlib.h>
#include <string.h>

#include "ADTDefs.h"
#include "genSort.h"ג

static void GenSwap(void* _first, void* _sec, void* _temp, size_t _elemSize);

ADTErr GenSort(void* _arr, size_t _elemSize, size_t _arrLength, Criteria _sortCriteria)
{
        void* currentItem;
        void* prevItem;
        void* temp;
        int i, j, flag = 0;
        int len = _arrLength * _elemSize;

        if(NULL == _arr || NULL == _sortCriteria)
        {
                return ERR_NOT_INITIALIZED;
        }

        if (_elemSize == 0 || _arrLength == 0)
        {
                return ERR_INVALID_SIZE;
        }
        
        if((temp = malloc(_elemSize)) == NULL)
        {
                return ERR_ALLOCATION_FAILED;
        }

        for(i = 0; i < len-1; i+=_elemSize)
        {
                flag = 0;
                for(j = _elemSize; j < len - i; j+=_elemSize)
                {
                        prevItem = (void*)((char*)_arr + (j - _elemSize));
                        currentItem = (void*)((char*)_arr + j);

                        if(_sortCriteria(prevItem, currentItem))
                        {
                                GenSwap(prevItem, currentItem, temp, _elemSize);
                        }
                }
        }

        free(temp);

        return ERR_OK;
}

static void GenSwap(void* _first, void* _sec, void* _temp, size_t _elemSize)
{
        memcpy(_temp, _sec, _elemSize);
        memcpy(_sec, _first, _elemSize);
        memcpy(_first, _temp, _elemSize);
}
