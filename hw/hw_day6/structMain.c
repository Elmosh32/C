#include "struct.h"

int main(){
        struct DynamicArray* da;

        da=DynamicArrayCreate(5,0);
        DynamicArrayInsert(da,7);
        DynamicArrayInsert(da,3);
        DynamicArrayInsert(da,2);
        DynamicArrayInsert(da,1);
        DynamicArrayInsert(da,3);
        printf("arraysizeBlock = 0\tDynamicArrayInsert(da.%d) = %d\n",1,DynamicArrayInsert(da,1) );
        DynamicArrayDestroy(da);
        printf("\n");

        da=DynamicArrayCreate(3,2);
        printf("dArraySize:%d\tdArrayBlockSize:%d\n",da->dArraySize,da->dArrayBlockSize);
        DynamicArrayInsert(da,1);
        DynamicArrayInsert(da,2);
        DynamicArrayInsert(da,3);
        printf("NumOfElements:%d\t\tdArraySize:%d\n",da->NumOfElements,da->dArraySize);
        DynamicArrayInsert(da,4);
        DynamicArrayInsert(da,5);
        DynamicArrayInsert(da,6);
        printf("NumOfElements:%d\t\tdArraySize:%d\n",da->NumOfElements,da->dArraySize);
        DynamicArrayDelete(da,da->dArray);
        DynamicArrayInsert(da,92);
        printf("after delete and insert \nNumOfElements is:%d\tdArraySize:%d\n",da->NumOfElements,da->dArraySize);
        DynamicArrayDestroy(da);

        da=DynamicArrayCreate(8,2);
        DynamicArrayInsert(da,7);
        DynamicArrayInsert(da,3);
        DynamicArrayInsert(da,35);
        DynamicArrayDelete(da,da->dArray);
        DynamicArrayInsert(da,12);


        return 0;
}
