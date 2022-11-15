#include <stdlib.h>             /*malloc*/
#include <stdio.h>             /*printf*/
#include <stddef.h>  /*size_t*/

#include "bst.h"
#include "ADTDefs.h"

void createTreeT1(){
        Tree* tree = TreeCreate();

        if(tree == NULL)
                printf("TreeCreate test\t=>\tFAIL\n");
        else
                printf("TreeCreate test\t=>\tPASS\n");
        destroyTree(tree);
}

void createTreeT2(){
        Tree* tree = TreeCreate();
        tree = TreeCreate();
        if(tree == NULL)
                printf("TreeCreate test\t=>\tFAIL\n");
        else
                printf("TreeCreate test\t=>\tPASS\n");
        destroyTree(tree);
}

void createTreeT3(){
        Tree* tree = TreeCreate();
        destroyTree(tree);
        tree = TreeCreate();

        if(tree == NULL)
                printf("TreeCreate test\t=>\tFAIL\n");
        else
                printf("TreeCreate test\t=>\tPASS\n");
        destroyTree(tree);
}

void TreeInsertT1(){
        if(TreeInsert(NULL,1) == ERR_OK)
                printf("TreeInsert test\t=>\tFAIL\n");
        else
                printf("TreeInsert test\t=>\tPASS\n");
}

void TreeInsertT2(){
        Tree* tree = TreeCreate();
        destroyTree(tree);

        if(TreeInsert(tree,1) == ERR_OK)
                printf("TreeInsert test\t=>\tFAIL\n");
        else
                printf("TreeInsert test\t=>\tPASS\n");
        destroyTree(tree);
}

void TreeInsertT3(){
        Tree* tree = TreeCreate();
        TreeInsert(tree,1);
        TreeInsert(tree,2);
        if(TreeInsert(tree,1) == ERR_OK)
                printf("TreeInsert test\t=>\tFAIL\n");
        else
                printf("TreeInsert test\t=>\tPASS\n");
        destroyTree(tree);
}

void TreeInsertT4(){
        Tree* tree = TreeCreate();
        TreeInsert(tree,5);
        TreeInsert(tree,2);
        if(TreeInsert(tree,1) != ERR_OK)
                printf("TreeInsert test\t=>\tFAIL\n");
        else
                printf("TreeInsert test\t=>\tPASS\n");
        destroyTree(tree);
}

void isFullTreeT1(){
        Tree* tree = TreeCreate();
        TreeInsert(tree,5);
        if(isFullTree(tree) != ERR_FULL_TREE)
                printf("isFullTree test\t=>\tFAIL\n");
        else
                printf("isFullTree test\t=>\tPASS\n");
        destroyTree(tree);
}

void isFullTreeT2(){
        Tree* tree = TreeCreate();
        TreeInsert(tree,5);
        TreeInsert(tree,1);

        if(isFullTree(tree) == ERR_FULL_TREE)
                printf("isFullTree test\t=>\tFAIL\n");
        else
                printf("isFullTree test\t=>\tPASS\n");
        destroyTree(tree);
}

void areSimilarT1(){
        Tree* tree1 = TreeCreate();
        Tree* tree2 = TreeCreate();

        TreeInsert(tree1,5);
        TreeInsert(tree1,7);

        TreeInsert(tree2,8);
        TreeInsert(tree2,9);
        if(areSimilarTree(tree1,tree2) != ERR_SIMILAR)
                printf("areSimilarTree test\t=>\tFAIL\n");
        else
                printf("areSimilarTree test\t=>\tPASS\n");
        destroyTree(tree1);
        destroyTree(tree2);
}

void areSimilarT2(){
        Tree* tree1 = TreeCreate();
        Tree* tree2 = TreeCreate();

        TreeInsert(tree1,5);
        TreeInsert(tree1,1);

        TreeInsert(tree2,1);
        TreeInsert(tree2,9);
        if(areSimilarTree(tree1,tree2) == ERR_SIMILAR)
                printf("areSimilarTree test\t=>\tFAIL\n");
        else
                printf("areSimilarTree test\t=>\tPASS\n");
        destroyTree(tree1);
        destroyTree(tree2);
}

void areSimilarT3(){
        Tree* tree1 = TreeCreate();
        Tree* tree2 = TreeCreate();

        if(areSimilarTree(tree1,tree2) == ERR_FULL_TREE)
                printf("areSimilarTree test\t=>\tFAIL\n");
        else
                printf("areSimilarTree test\t=>\tPASS\n");
        destroyTree(tree1);
        destroyTree(tree2);
}

void calcTreeLevelT1(){
        Tree* tree = TreeCreate();
        TreeInsert(tree,5);
        TreeInsert(tree,1);
        TreeInsert(tree, 7);

        if(calcTreeLevel(tree) != 1)
                printf("calcTreeLevel test\t=>\tFAIL\n");
        else
                printf("calcTreeLevel test\t=>\tPASS\n");
        destroyTree(tree);
}

void mirrorTreeT1(){
        Tree* tree = TreeCreate();
        TreeInsert(tree,5);
        TreeInsert(tree,1);
        TreeInsert(tree, 7);
        TreePrint(tree,POST_ORDER);
        mirrorTree(tree);
        TreePrint(tree,POST_ORDER);

        if(calcTreeLevel(tree) != 2)
                printf("calcTreeLevel test\t=>\tFAIL\n");
        else
                printf("calcTreeLevel test\t=>\tPASS\n");
        destroyTree(tree);
}
void isPerfectTreeT1(){
        Tree* tree = TreeCreate();
        TreeInsert(tree,5);
        TreeInsert(tree,1);
        TreeInsert(tree,7);
        TreeInsert(tree,6);
        TreeInsert(tree,8);

        if(isPerfectTree(tree) != ERR_PERFECT_TREE)
                printf("isPerfectTree test\t=>\tFAIL\n");
        else
                printf("isPerfectTree test\t=>\tPASS\n");
        destroyTree(tree);
}

int main(){
        printf("\n*************************************************************\n"
               "                     createTree tests\n"
               "*************************************************************\n");
        createTreeT1();
        createTreeT2();
        createTreeT3();

        printf("\n*************************************************************\n"
               "                     TreeInsert tests\n"
               "*************************************************************\n");
        TreeInsertT1();
        TreeInsertT2();
        TreeInsertT3();
        TreeInsertT4();

        isFullTreeT1();
        isFullTreeT2();

        areSimilarT1();
        areSimilarT2();
        areSimilarT3();
        calcTreeLevelT1();

        mirrorTreeT1();
        isPerfectTreeT1();
        return 0;
}
