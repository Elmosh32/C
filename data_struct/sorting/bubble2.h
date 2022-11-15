#ifndef __BUBBLE_2__
#define __BUBBLE_2__

#include <stddef.h>
#define TRUE 1
#define FALSE 0
typedef int (*CompareFunc)(void*,void*);

int bubbleSort(CompareFunc _less,  int _array[], size_t _arrSize);
#endif /* ifndef __BUBBLE_2__ */
