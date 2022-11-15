#define OK 0
#define SIZE_ERROR -1
#define GARBAGE_POINTER -2
#define MAX_SIZE 40
/**
   Description- sorting the array
   Input-  arr: the declared array from the main
          _size: the  arr[] size
   Output- error code.
   Error- @return OK 0 if the array size is is not bigger from 40
          @return SIZE_ERROR -1 if the array size is bigger from 40
 **/
int sortArray(int arr[], int size);

/**
   Description- the func prints the sorted array.
   Input-  arr: the declared array from the main,
           _size: the  arr[] size
   Output- void
   Error- X
 **/
void printArray(int arr[], int size);
