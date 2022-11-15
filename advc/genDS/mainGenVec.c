/**********************************************************************************
                                includes
**********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "../genVec/genVector.h"

typedef Vector *(*dLibFuncC)(size_t _initialCapacity, size_t _blockSize);
typedef void (*dLibFuncD)(Vector **_vector, void (*_elementDestroy)(void *_item));
typedef VectorResult (*dLibFuncA)(Vector *_vector, void *_item);
typedef size_t (*dLibFuncF)(void *_element, size_t _index, void *_context);

int IntVecPrint(void *_element, size_t _index, void *_context)
{
        printf("%d ", *(int *)_element);
        return 1;
}

int main()
{
        Vector *vec = NULL;
        dLibFuncC dlfuncCreate;
        dLibFuncD dlfuncDestroy;
        dLibFuncA dlfuncAppend;
        dLibFuncF dlfuncForEach;
        int *a[5];

        void *dl = dlopen("libgenDL.so", RTLD_LAZY);
        if (dl == NULL)
        {
                printf("dlopen Failed\n");
                return (-1);
        }

        dlfuncCreate = (dLibFuncC)dlsym(dl, "VectorCreate");
        dlfuncDestroy = (dLibFuncD)dlsym(dl, "VectorDestroy");
        dlfuncAppend = (dLibFuncA)dlsym(dl, "VectorAppend");
        dlfuncForEach = (dLibFuncF)dlsym(dl, "VectorForEach");

        if (dlfuncDestroy == NULL || dlfuncCreate == NULL || dlfuncAppend == NULL || dlfuncForEach == NULL)
        {
                printf("dlsym Failed\n");
                return (-2);
        }

        vec = dlfuncCreate(2, 4);

        a[0] = malloc(sizeof(int));
        *a[0] = 10;
        dlfuncAppend(vec, (void *)a[0]);

        a[1] = malloc(sizeof(int));
        *a[1] = 30;
        dlfuncAppend(vec, (void *)a[1]);

        a[2] = malloc(sizeof(int));
        *a[2] = 20;
        dlfuncAppend(vec, (void *)a[2]);

        a[3] = malloc(sizeof(int));
        *a[3] = 220;
        dlfuncAppend(vec, (void *)a[3]);

        a[4] = malloc(sizeof(int));
        *a[4] = 154;
        dlfuncAppend(vec, (void *)a[4]);

        dlfuncForEach(vec, IntVecPrint, NULL);
        printf("\n");

        dlfuncDestroy(&vec, NULL);

        return 1;
}
