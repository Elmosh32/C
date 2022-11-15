/**********************************************************************************
                                includes && define
**********************************************************************************/
#include <stdlib.h> /*malloc*/
#include <stdio.h>  /*printf*/
#include <stddef.h> /*size_t*/

#include "genBst.h"

/**********************************************************************************
                     Declaration of static test Functions
**********************************************************************************/
static void TreeCreateT1();
static void TreeCreateT2();

static void TreeDestroyT1();
static void TreeDestroyT2();
static void TreeDestroyT3();
static void TreeDestroyT4();

static void TreeInsertT1();
static void TreeInsertT2();
static void TreeInsertT4();

static void TreeFindFirstT1();
static void TreeFindFirstT2();

static void TreeItrBeginT1();
static void TreeItrBeginT2();

static void TreeItrEndT1();
static void TreeItrEndT2();

static void TreeRemoveT1();
static void TreeRemoveT2();
static void TreeRemoveT3();
static void TreeRemoveT4();

void FreeElement(void *_data)
{
        free(_data);
        return;
}

int LessTreeComp(void *_item1, void *_item2)
{
        if (*(int *)_item1 < *(int *)_item2)
        {
                return -1;
        }

        if (*(int *)_item1 > *(int *)_item2)
        {
                return 1;
        }
        return 0;
}

int ElementExist(void *_item1, void *_item2)
{
        if (*(int *)_item1 == *(int *)_item2)
        {
                return 0;
        }

        return 1;
}

int PrintTree(void *_item1, void *_item2)
{

        printf("%3d", *(int *)_item1);

        return 1;
}

int main()
{
        printf("\n*************************************************************\n"
               "                     createTree tests\n"
               "*************************************************************\n");
        TreeCreateT1();
        TreeCreateT2();

        printf("\n*************************************************************\n"
               "                     BSTreeDestroy tests\n"
               "*************************************************************\n");
        TreeDestroyT1();
        TreeDestroyT2();
        TreeDestroyT3();
        TreeDestroyT4();

        printf("\n*************************************************************\n"
               "                     BSTreeInsert tests\n"
               "*************************************************************\n");
        TreeInsertT1();
        TreeInsertT2();
        TreeInsertT4();

        printf("\n*************************************************************\n"
               "                   BSTreeFindFirst tests\n"
               "*************************************************************\n");
        TreeFindFirstT1();
        TreeFindFirstT2();

        printf("\n*************************************************************\n"
               "                   BSTreeItrBegin tests\n"
               "*************************************************************\n");
        TreeItrBeginT1();
        TreeItrBeginT2();

        printf("\n*************************************************************\n"
               "                   BSTreeItrEnd tests\n"
               "*************************************************************\n");
        TreeItrEndT1();
        TreeItrEndT2();

        printf("\n*************************************************************\n"
               "                   BSTreeItrRemove tests\n"
               "*************************************************************\n");
        TreeRemoveT1();
        TreeRemoveT2();
        TreeRemoveT3();
        TreeRemoveT4();
        return 0;
}

/**************************************************************
                        BSTreeCreate tests
***************************************************************/
/* TreeCreate POSITIVE TEST*/
static void TreeCreateT1()
{
        BSTree *tree;

        if ((tree = BSTreeCreate(LessTreeComp)) == NULL)
        {
                printf("(1) BSTreeCreate test\t=>\tFAIL\n");
        }
        else
        {
                printf("(1) BSTreeCreate test\t=>\tPASS\n");
        }

        BSTreeDestroy(&tree, NULL);
}

/* TreeCreate NEGATIVE TEST => LessComparator == NULL*/
static void TreeCreateT2()
{
        BSTree *tree;

        if ((tree = BSTreeCreate(NULL)) != NULL)
        {
                printf("(2) BSTreeCreate test\t=>\tFAIL\n");
        }
        else
        {
                printf("(2) BSTreeCreate test\t=>\tPASS\n");
        }

        BSTreeDestroy(&tree, NULL);
}

/**************************************************************
                        BSTreeDestroy tests
***************************************************************/
/* TreeCreate NEGATIVE TEST => BSTreeDestroy(NULL,NULL)*/
static void TreeDestroyT1()
{
        BSTreeDestroy(NULL, NULL);
        printf("(1) BSTreeDestroy test\t=>\tPASS\n");
}

/* TreeCreate NEGATIVE TEST => BSTreeDestroy TWICE*/
static void TreeDestroyT2()
{
        BSTree *tree;
        tree = BSTreeCreate(LessTreeComp);
        BSTreeDestroy(&tree, NULL);
        BSTreeDestroy(&tree, NULL);
        printf("(2) BSTreeDestroy test\t=>\tPASS\n");
}

/* TreeCreate POSITIVE TEST*/
static void TreeDestroyT3()
{
        BSTree *tree = BSTreeCreate(LessTreeComp);
        int *a[5];

        a[0] = malloc(sizeof(int));
        *a[0] = 4;
        BSTreeInsert(tree, (void *)a[0]);

        a[1] = malloc(sizeof(int));
        *a[1] = 5;
        BSTreeInsert(tree, (void *)a[1]);

        a[2] = malloc(sizeof(int));
        *a[2] = 2;
        BSTreeInsert(tree, (void *)a[2]);

        a[3] = malloc(sizeof(int));
        *a[3] = 1;
        BSTreeInsert(tree, (void *)a[3]);

        a[4] = malloc(sizeof(int));
        *a[4] = 3;
        BSTreeInsert(tree, (void *)a[4]);

        BSTreeDestroy(&tree, FreeElement);

        if (tree == NULL)
        {
                printf("(3) BSTreeDestroy test\t=>\tPASS\n");
        }
        else
        {
                printf("(3) BSTreeDestroy test\t=>\tFAIL\n");
        }
}

/* TreeCreate NEGATIVE TEST => BSTreeDestroy NULL TREE*/
static void TreeDestroyT4()
{
        BSTreeDestroy(NULL, FreeElement);
        printf("(4) BSTreeDestroy test\t=>\tPASS\n");
}

/**************************************************************
                        BSTreeInsert tests
***************************************************************/
/* BSTreeInsert NEGATIVE TEST => BSTreeInsert NULL TREE*/
static void TreeInsertT1()
{
        int num = 1;

        if (BSTreeInsert(NULL, &num) != NULL)
        {
                printf("(1) BSTreeInsert test\t=>\tFAIL\n");
        }
        else
        {
                printf("(1) BSTreeInsert test\t=>\tPASS\n");
        }
}

/* BSTreeInsert NEGATIVE TEST => BSTreeInsert AFTER DESTROY*/
static void TreeInsertT2()
{
        BSTree *tree = BSTreeCreate(LessTreeComp);
        int num = 1;

        BSTreeDestroy(&tree, NULL);

        if (BSTreeInsert(tree, &num) != NULL)
        {
                printf("(2) BSTreeInsert test\t=>\tFAIL\n");
        }
        else
        {
                printf("(2) BSTreeInsert test\t=>\tPASS\n");
        }

        BSTreeDestroy(&tree, NULL);
}

/* BSTreeInsert POSITIVE TEST => BSTreeInsert SAME VAL TWICE */
static void TreeInsertT4()
{
        BSTree *tree = BSTreeCreate(LessTreeComp);
        int *a[5];

        a[0] = malloc(sizeof(int));
        *a[0] = 1;
        BSTreeInsert(tree, (void *)a[0]);

        a[1] = malloc(sizeof(int));
        *a[1] = 2;
        BSTreeInsert(tree, (void *)a[1]);

        a[2] = malloc(sizeof(int));
        *a[2] = 1;
        BSTreeInsert(tree, (void *)a[2]);

        if (BSTreeInsert(tree, (void *)a[2]) == NULL)
        {
                printf("(4) BSTreeInsert test\t=>\tFAIL\n");
        }
        else
        {
                printf("(4) BSTreeInsert test\t=>\tPASS\n");
        }

        BSTreeDestroy(&tree, NULL);
}

/**************************************************************
                        BSTreeFindFirst tests
***************************************************************/
/* BSTreeItrRemove POSITIVE TEST => BSTreeItrRemove(BSTreeItrBegin(tree)) */
static void TreeFindFirstT1()
{
        BSTree *tree = BSTreeCreate(LessTreeComp);
        int *a[5];

        a[0] = malloc(sizeof(int));
        *a[0] = 4;

        if ((BSTreeFindFirst(tree, ElementExist, (void *)a[0])) == NULL)
        {
                printf("(1) BSTreeFindFirst test\t=>\tPASS\n");
        }
        else
        {
                printf("(1) BSTreeFindFirst test\t=>\tFAIL\n");
        }

        BSTreeDestroy(&tree, FreeElement);
}

/* BSTreeItrRemove POSITIVE TEST => BSTreeItrRemove(BSTreeItrBegin(tree)) */
static void TreeFindFirstT2()
{
        BSTree *tree = BSTreeCreate(LessTreeComp);
        int *a[5];

        a[0] = malloc(sizeof(int));
        *a[0] = 4;
        BSTreeInsert(tree, (void *)a[0]);

        a[1] = malloc(sizeof(int));
        *a[1] = 5;
        BSTreeInsert(tree, (void *)a[1]);

        a[2] = malloc(sizeof(int));
        *a[2] = 2;
        BSTreeInsert(tree, (void *)a[2]);

        a[3] = malloc(sizeof(int));
        *a[3] = 1;
        BSTreeInsert(tree, (void *)a[3]);

        a[4] = malloc(sizeof(int));
        *a[4] = 3;
        BSTreeInsert(tree, (void *)a[4]);

        if ((BSTreeFindFirst(tree, ElementExist, (void *)a[3])) != NULL)
        {
                printf("(2) BSTreeFindFirst test\t=>\tPASS\n");
        }
        else
        {
                printf("(2) BSTreeFindFirst test\t=>\tFAIL\n");
        }

        BSTreeDestroy(&tree, FreeElement);
}

/**************************************************************
                        BSTreeItrBegin tests
***************************************************************/
/* BSTreeItrRemove POSITIVE TEST => BSTreeItrRemove(BSTreeItrBegin(tree)) */
static void TreeItrBeginT1()
{
        BSTree *tree = BSTreeCreate(LessTreeComp);
        int *a[5];

        a[0] = malloc(sizeof(int));
        *a[0] = 4;
        BSTreeInsert(tree, (void *)a[0]);

        a[1] = malloc(sizeof(int));
        *a[1] = 5;
        BSTreeInsert(tree, (void *)a[1]);

        if (*(int *)(BSTreeItrGet(BSTreeItrBegin(tree))) == 4)
        {
                printf("(1) BSTreeItrBegin test\t=>\tPASS\n");
        }
        else
        {
                printf("(1) BSTreeItrBegin test\t=>\tFAIL\n");
        }

        BSTreeDestroy(&tree, FreeElement);
}

/* BSTreeItrRemove POSITIVE TEST => BSTreeItrRemove(BSTreeItrBegin(tree)) */
static void TreeItrBeginT2()
{
        BSTree *tree = BSTreeCreate(LessTreeComp);

        if (BSTreeItrBegin(tree) == BSTreeItrEnd(tree))
        {
                printf("(2) BSTreeItrBegin test\t=>\tPASS\n");
        }
        else
        {
                printf("(2) BSTreeItrBegin test\t=>\tFAIL\n");
        }

        BSTreeDestroy(&tree, FreeElement);
}

/**************************************************************
                        BSTreeItrEnd tests
***************************************************************/
/* BSTreeItrRemove POSITIVE TEST => BSTreeItrRemove(BSTreeItrBegin(tree)) */
static void TreeItrEndT1()
{
        BSTree *tree = BSTreeCreate(LessTreeComp);
        int *a[5];

        a[0] = malloc(sizeof(int));
        *a[0] = 4;
        BSTreeInsert(tree, (void *)a[0]);

        a[1] = malloc(sizeof(int));
        *a[1] = 5;
        BSTreeInsert(tree, (void *)a[1]);

        if (*(int *)(BSTreeItrGet(BSTreeItrPrev(BSTreeItrEnd(tree)))) == 5)
        {
                printf("(1) BSTreeItrEnd test\t=>\tPASS\n");
        }
        else
        {
                printf("(1) BSTreeItrEnd test\t=>\tFAIL\n");
        }

        BSTreeDestroy(&tree, FreeElement);
}

/* BSTreeItrRemove POSITIVE TEST => BSTreeItrRemove(BSTreeItrBegin(tree)) */
static void TreeItrEndT2()
{
        BSTree *tree = BSTreeCreate(LessTreeComp);
        int *a[5];

        a[0] = malloc(sizeof(int));
        *a[0] = 4;
        BSTreeInsert(tree, (void *)a[0]);

        if (*(int *)(BSTreeItrGet(BSTreeItrPrev(BSTreeItrEnd(tree)))) == 4)
        {
                printf("(2) BSTreeItrEnd test\t=>\tPASS\n");
        }
        else
        {
                printf("(2) BSTreeItrEnd test\t=>\tFAIL\n");
        }

        BSTreeDestroy(&tree, FreeElement);
}

/**************************************************************
                        BSTreeItrRemove tests
***************************************************************/
/* BSTreeItrRemove POSITIVE TEST => BSTreeItrRemove(BSTreeItrBegin(tree)) */
static void TreeRemoveT1()
{
        BSTree *tree = BSTreeCreate(LessTreeComp);
        int *a[5];

        a[0] = malloc(sizeof(int));
        *a[0] = 4;
        BSTreeInsert(tree, (void *)a[0]);

        a[1] = malloc(sizeof(int));
        *a[1] = 5;
        BSTreeInsert(tree, (void *)a[1]);

        a[2] = malloc(sizeof(int));
        *a[2] = 2;
        BSTreeInsert(tree, (void *)a[2]);

        a[3] = malloc(sizeof(int));
        *a[3] = 1;
        BSTreeInsert(tree, (void *)a[3]);

        a[4] = malloc(sizeof(int));
        *a[4] = 3;
        BSTreeInsert(tree, (void *)a[4]);

        BSTreeItrRemove(BSTreeItrBegin(tree));

        if ((BSTreeFindFirst(tree, ElementExist, (void *)a[3])) == NULL)
        {
                printf("(1) BSTreeItrRemove test\t=>\tPASS\n");
        }
        else
        {
                printf("(1) BSTreeItrRemove test\t=>\tFAIL\n");
        }

        BSTreeDestroy(&tree, FreeElement);
}

/* BSTreeItrRemove POSITIVE TEST => BSTreeItrRemove((BSTreeItrPrev(BSTreeItrEnd(tree)))) */
static void TreeRemoveT2()
{
        BSTree *tree = BSTreeCreate(LessTreeComp);
        int *a[5];

        a[0] = malloc(sizeof(int));
        *a[0] = 4;
        BSTreeInsert(tree, (void *)a[0]);

        a[1] = malloc(sizeof(int));
        *a[1] = 5;
        BSTreeInsert(tree, (void *)a[1]);

        a[2] = malloc(sizeof(int));
        *a[2] = 2;
        BSTreeInsert(tree, (void *)a[2]);

        a[3] = malloc(sizeof(int));
        *a[3] = 1;
        BSTreeInsert(tree, (void *)a[3]);

        a[4] = malloc(sizeof(int));
        *a[4] = 3;
        BSTreeInsert(tree, (void *)a[4]);

        BSTreeItrRemove((BSTreeItrPrev(BSTreeItrEnd(tree))));

        if ((BSTreeFindFirst(tree, ElementExist, (void *)a[1])) == NULL)
        {
                printf("(2) BSTreeItrRemove test\t=>\tPASS\n");
        }
        else
        {
                printf("(2) BSTreeItrRemove test\t=>\tFAIL\n");
        }

        BSTreeDestroy(&tree, FreeElement);
}

/* BSTreeItrRemove POSITIVE TEST => BSTreeItrRemove((BSTreeItrNext(BSTreeItrBegin(tree)))) */
static void TreeRemoveT3()
{
        BSTree *tree = BSTreeCreate(LessTreeComp);
        int *a[5];

        a[0] = malloc(sizeof(int));
        *a[0] = 4;
        BSTreeInsert(tree, (void *)a[0]);

        a[1] = malloc(sizeof(int));
        *a[1] = 5;
        BSTreeInsert(tree, (void *)a[1]);

        a[2] = malloc(sizeof(int));
        *a[2] = 2;
        BSTreeInsert(tree, (void *)a[2]);

        a[3] = malloc(sizeof(int));
        *a[3] = 1;
        BSTreeInsert(tree, (void *)a[3]);

        a[4] = malloc(sizeof(int));
        *a[4] = 3;
        BSTreeInsert(tree, (void *)a[4]);

        BSTreeItrRemove((BSTreeItrNext(BSTreeItrBegin(tree))));

        if ((BSTreeFindFirst(tree, ElementExist, (void *)a[2])) == NULL)
        {
                printf("(3) BSTreeItrRemove test\t=>\tPASS\n");
        }
        else
        {
                printf("(3) BSTreeItrRemove test\t=>\tFAIL\n");
        }

        BSTreeDestroy(&tree, NULL);
}

/* BSTreeItrRemove POSITIVE TEST => BSTreeItrRemove((BSTreeItrNext(BSTreeItrBegin(tree)))) */
static void TreeRemoveT4()
{
        BSTree *tree = BSTreeCreate(LessTreeComp);
        int *a[5];

        a[0] = malloc(sizeof(int));
        *a[0] = 4;
        BSTreeInsert(tree, (void *)a[0]);

        a[1] = malloc(sizeof(int));
        *a[1] = 5;
        BSTreeInsert(tree, (void *)a[1]);

        a[2] = malloc(sizeof(int));
        *a[2] = 2;
        BSTreeInsert(tree, (void *)a[2]);

        a[3] = malloc(sizeof(int));
        *a[3] = 1;
        BSTreeInsert(tree, (void *)a[3]);

        a[4] = malloc(sizeof(int));
        *a[4] = 3;
        BSTreeInsert(tree, (void *)a[4]);

        BSTreeItrRemove((BSTreeItrNext(BSTreeItrBegin(tree))));
        BSTreeItrRemove((BSTreeItrNext(BSTreeItrBegin(tree))));

        if ((BSTreeFindFirst(tree, ElementExist, (void *)a[2])) == NULL && (BSTreeFindFirst(tree, ElementExist, (void *)a[4])) == NULL)
        {
                printf("(4) BSTreeItrRemove test\t=>\tPASS\n");
        }
        else
        {
                printf("(4) BSTreeItrRemove test\t=>\tFAIL\n");
        }

        BSTreeDestroy(&tree, NULL);
}