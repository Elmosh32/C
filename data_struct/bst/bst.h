#ifndef __BST__
#define __BST__

#include "ADTDefs.h"

typedef struct Tree Tree;
typedef struct Node Node;

typedef enum
{
        PRE_ORDER,
        IN_ORDER,
        POST_ORDER
} TreeTraverse;

Tree*   TreeCreate();
void    TreeDestroy(Tree* _tree);
ADTErr  TreeInsert(Tree* _tree, int _data);
void    TreePrint(Tree* _tree, TreeTraverse _traverseMode);
ADTErr isFullTree(Tree* _tree);
ADTErr areSimilarTree(Tree* _tree1, Tree* _tree2);
int calcTreeLevel(Tree* _tree);
void mirrorTree(Tree* _tree);
ADTErr isPerfectTree(Tree* _tree);
#endif /*__BST__*/
