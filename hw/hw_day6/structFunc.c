#include "struct.h"

struct DynamicArray * DynamicArrayCreate(int _size, int _blockSize){
        struct DynamicArray* da;
        int* dArr;

        if(_size <= 0 && _blockSize <= 0)
                return POINTER_NOT_INITIALIZE;
        if((da = (struct DynamicArray*) malloc (sizeof(struct DynamicArray))) == NULL)
                return POINTER_NOT_INITIALIZE;
        if((dArr = (int*)malloc(_size * sizeof(int))) == NULL) {
                free(da);
                return POINTER_NOT_INITIALIZE;
        }

        da->dArray = dArr;
        da->dArraySize = _size;
        da->dArrayBlockSize = _blockSize;
        da->NumOfElements = 0;

        return da;
}


void DynamicArrayDestroy(struct DynamicArray *_DynaminArrayPtr){
        if(_DynaminArrayPtr != NULL) {
                free(_DynaminArrayPtr->dArray);
                free(_DynaminArrayPtr);
        }
}


int DynamicArrayInsert(struct DynamicArray * _DynaminArrayPtr, int _data){
        struct DynamicArray* da;
        int newSize;

        if(_DynaminArrayPtr == NULL || _DynaminArrayPtr->dArrayBlockSize == 0)
                return OVERFLOW;

        newSize = (_DynaminArrayPtr->dArraySize)*sizeof(int) + (_DynaminArrayPtr->dArrayBlockSize)*sizeof(int);

        if(_DynaminArrayPtr->dArraySize > _DynaminArrayPtr->NumOfElements) {
                _DynaminArrayPtr->dArray[_DynaminArrayPtr->NumOfElements] = _data;
                _DynaminArrayPtr->NumOfElements++;
        }else{
                if((da->dArray = realloc(_DynaminArrayPtr->dArray,newSize))!= NULL) {
                        _DynaminArrayPtr->dArray = da->dArray;
                        _DynaminArrayPtr->dArraySize += _DynaminArrayPtr->dArrayBlockSize;
                        _DynaminArrayPtr->dArray[_DynaminArrayPtr->NumOfElements] = _data;
                        _DynaminArrayPtr->NumOfElements++;
                }else
                        return REALLOC_FAIL;
        }

        return OK;
}

int DynamicArrayDelete( struct DynamicArray *_DynaminArrayPtr, int* _data){
        if(_DynaminArrayPtr == NULL || _data == NULL)
                return UNDERFLOW;

        _DynaminArrayPtr->NumOfElements--;
        *_data = _DynaminArrayPtr->dArray[(_DynaminArrayPtr->NumOfElements-1)];

        return OK;
}
