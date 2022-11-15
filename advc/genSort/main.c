#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "genSort.h"

/** struct Person **/
typedef struct Person Person;

struct Person
{
        int m_id;
        char m_name[20];
        int m_age;
};

/*******************************************************
**********************sort criteria********************
*******************************************************/
static int SortAscendingAge(const void* _first, const void* _second)
{
        if(((Person*)_first)->m_age > ((Person*)_second)->m_age)
        {
                return 1;
        }
        return 0;
}

static int SortAscendingID(const void* _first, const void* _second)
{
        if(((Person*)_first)->m_id > ((Person*)_second)->m_id)
        {
                return 1;
        }
        return 0;
}

static int SortAscendingArr(const void* _first, const void* _second)
{
        if(*(int*)_first > *(int*)_second)
        {
                return 1;
        }
        return 0;
}

/*******************************************************
**********************print functions*******************
*******************************************************/
static void PrintPerson(Person* _person, size_t _size)
{
        int i;
        for (i = 0; i < _size; ++i)
        {
                printf("person[%d]:  person id = %d  person name = %s  person age = %d\n", i, _person[i].m_id, _person[i].m_name, _person[i].m_age);
        }
}

static void PrintArr(int* _arr, size_t _size)
{
        int i;
        for (i = 0; i < _size; ++i)
        {
                printf("arr[%d] = %d\t", i, _arr[i]);
        }
}

/*******************************************************
************************* TESTS *************************
*******************************************************/
void NullArrCheck()
{
        if(GenSort(NULL, sizeof(int), 5, SortAscendingArr) == ERR_NOT_INITIALIZED)
        {
                printf("TEST:arr null\t=>\tPASS\n");
                return;
        }
        printf("TEST:arr null\t=>\tFAIL\n");
}

void ElemSizeCheck()
{
        int arr[] = {7, 3, 2, 6, 4};

        if(GenSort(arr, 0, 5, SortAscendingArr) == ERR_INVALID_SIZE)
        {
                printf("TEST:Element size = 0\t=>\tPASS\n");
                return;
        }
        printf("TEST:Element size = 0\t=>\tFAIL\n");
}

void ArrLengthSizeCheck()
{
        int arr[] = {7, 3, 2, 6, 4};

        if(GenSort(arr, sizeof(int), 0, SortAscendingArr) == ERR_INVALID_SIZE)
        {
                printf("TEST:Arr Length size = 0\t=>\tPASS\n");
                return;
        }
        printf("TEST:Arr Length size = 0\t=>\tFAIL\n");
}

void NullSortCriteriaCheck()
{
        int arr[] = {7, 3, 2, 6, 4};
        if(GenSort(arr, sizeof(int), 5, NULL) == ERR_NOT_INITIALIZED)
        {
                printf("TEST:Sort Criteria Null\t=>\tPASS\n");
                return;
        }
        printf("TEST:Sort Criteria Null\t=>\tFAIL\n");
}

void ArrWithOneNum()
{
        int arr[] = {21};
        if(GenSort(arr, sizeof(int), 1, SortAscendingArr) == ERR_OK)
        {
                printf("TEST:array with one number\t=>\tPASS\n");
                return;
        }
        printf("TEST:array with one number\t=>\tFAIL\n");
}

void PositiveNumbersSort()
{
        int arr[] = {12, 5, 3, 22, 102};
        GenSort(arr, sizeof(int), 5, SortAscendingArr);
        if(arr[0] == 3)
        {
                printf("TEST:array valid sort\t=>\tPASS\n");
                return;
        }
        printf("TEST:array valid sort\t=>\tFAIL\n");
}

void NegetiveNumbersSort()
{
        int arr[5] = {-23, -1, -123, -13, -5};
        GenSort(arr, sizeof(int), 5, SortAscendingArr);
        if(arr[0] == -123)
        {
                printf("TEST:array valid sort\t=>\tPASS\n");
                return;
        }
        printf("TEST:array valid sort\t=>\tFAIL\n");
}

void NumbersSort()
{
        int arr[5] = {12, -3, 0, -12, 3};
        GenSort(arr, sizeof(int), 5, SortAscendingArr);
        if(arr[0] == -12)
        {
                printf("TEST:array valid sort\t=>\tPASS\n");
                return;
        }
        printf("TEST:array valid sort\t=>\tFAIL\n");
}

void PersonPositiveIDSort()
{
        Person person[3] = {{32,"lior",21},{31,"yakov",31},{38,"michal",46}};
        GenSort(person, sizeof(Person), 3, SortAscendingID);

        if(person[0].m_id == 31)
        {
                printf("TEST:Person valid ID sort\t=>\tPASS\n");
                return;
        }
        printf("TEST:Person valid ID sort\t=>\tFAIL\n");
}

void PersonNegetiveIDSort()
{
        Person person[3] = {{-32,"lior",21},{-131,"yakov",31},{-8,"michal",46}};
        GenSort(person, sizeof(Person), 3, SortAscendingID);

        if(person[0].m_id == -131)
        {
                printf("TEST:Person valid ID sort\t=>\tPASS\n");
                return;
        }
        printf("TEST:Person valid ID sort\t=>\tFAIL\n");
}

void PersonIDSort()
{
        Person person[3] = {{0,"yakov",31}, {-32,"lior",21}, {18,"michal",46}};
        GenSort(person, sizeof(Person), 3, SortAscendingID);

        if(person[0].m_id == -32)
        {
                printf("TEST:Person valid ID sort\t=>\tPASS\n");
                return;
        }
        printf("TEST:Person valid ID sort\t=>\tFAIL\n");
}

void PersonAgeSort()
{
        Person person[3] = {{32,"lior",61},{31,"yakov",31},{38,"michal",46}};
        GenSort(person, sizeof(Person), 3, SortAscendingAge);

        if(person[0].m_id == 31)
        {
                printf("TEST:Person valid age sort\t=>\tPASS\n");
                return;
        }
        printf("TEST:Person valid age sort\t=>\tFAIL\n");
}

int main(){
        NullArrCheck();
        ElemSizeCheck();
        ArrLengthSizeCheck();
        NullSortCriteriaCheck();
        ArrWithOneNum();
        PositiveNumbersSort();
        NegetiveNumbersSort();
        NumbersSort();
        PersonPositiveIDSort();
        PersonNegetiveIDSort();
        PersonIDSort();
        PersonAgeSort();

        return 0;
}
