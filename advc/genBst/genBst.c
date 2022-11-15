/**********************************************************************************
                                includes && define
**********************************************************************************/
#include <stdlib.h> /*malloc*/
#include <stddef.h> /*size_t*/

#include "genBst.h"

#define TRUE 1
#define FALSE 0

#define IS_SENTINEL(n) (n->m_father == n)
#define IS_LEAF(n) (n->m_left == NULL && n->m_right == NULL)
#define IS_HAVE_ONE_CHILD(n) ((n->m_left != NULL && n->m_right == NULL) || (n->m_left == NULL && n->m_right != NULL))
#define IS_LEFT_CHILD(n) (n->m_father->m_left == n)
#define IS_RIGHT_CHILD(n) (n->m_father->m_right == n)

/**********************************************************************************
                                BSTree& Node structs
**********************************************************************************/
typedef struct Node Node;

struct Node
{
    void *m_data;
    Node *m_left;
    Node *m_right;
    Node *m_father;
};

struct BSTree
{
    Node m_sentinel;
    LessComparator m_less;
};

/**********************************************************************************
                     Declaration of static Auxiliary Functions
**********************************************************************************/
static BSTreeItr nodeInsert(LessComparator _less, Node *_root, Node *_newNode);
static Node *CreateNode(void *_data);

static void destroyNodes(Node *_node, void (*_destroyer)(void *));

static BSTreeItr findBegin(Node *_node);

static Node *NextItr(Node *_node, Node *_nextNode, int _whereFindTheNext);
static Node *PrevItr(Node *_node, Node *_prevNode, int _whereFindThePrev);

static BSTreeItr inOrder(Node *_node, ActionFunction _action, void *_context);
static BSTreeItr preOrder(Node *_node, ActionFunction _action, void *_context);
static BSTreeItr postOrder(Node *_node, ActionFunction _action, void *_context);

static void *RemoveLeap(BSTreeItr _it);
static void *RmParentWithOneChild(BSTreeItr _it);
static void *RmParentWithTwoChild(BSTreeItr _it);
static void *Swap(BSTreeItr _it);

/**********************************************************************************
                                    api functions
**********************************************************************************/
BSTree *BSTreeCreate(LessComparator _less)
{
    BSTree *tree = NULL;

    if (_less == NULL)
    {
        return NULL;
    }

    if ((tree = (BSTree *)malloc(sizeof(BSTree))) == NULL)
    {
        return NULL;
    }

    tree->m_less = _less;
    tree->m_sentinel.m_father = &tree->m_sentinel;
    tree->m_sentinel.m_left = NULL;
    tree->m_sentinel.m_right = NULL;

    return tree;
}

void BSTreeDestroy(BSTree **_tree, void (*_destroyer)(void *))
{
    Node *node = NULL;

    if (_tree == NULL || *_tree == NULL)
    {
        return;
    }

    node = (*_tree)->m_sentinel.m_left;
    destroyNodes(node, _destroyer);

    free(*_tree);
    *_tree = NULL;
}

BSTreeItr BSTreeInsert(BSTree *_tree, void *_item)
{
    Node *newNode = NULL;
    void *returnVal;

    if (_tree == NULL)
    {
        return NULL;
    }

    newNode = CreateNode(_item);
    if (newNode == NULL)
    {
        return BSTreeItrEnd(_tree);
    }

    if (_tree->m_sentinel.m_left == NULL)
    {
        _tree->m_sentinel.m_left = newNode;
        newNode->m_father = &(_tree->m_sentinel);
        return (BSTreeItr)newNode;
    }

    if ((returnVal = nodeInsert(_tree->m_less, _tree->m_sentinel.m_left, newNode)) == NULL)
    {
        free(newNode);
        return BSTreeItrEnd(_tree);
    }

    return returnVal;
}

BSTreeItr BSTreeFindFirst(const BSTree *_tree, PredicateFunction _predicate, void *_context)
{
    if (_tree == NULL || _predicate == NULL || _tree->m_sentinel.m_left == NULL)
    {
        return NULL;
    }

    return BSTreeForEach(_tree, BST_TRAVERSAL_IN_ORDER, _predicate, _context);
}

BSTreeItr BSTreeItrBegin(const BSTree *_tree)
{
    if (_tree == NULL)
    {
        return NULL;
    }

    if (_tree->m_sentinel.m_left == NULL)
    {
        return (BSTreeItr)&_tree->m_sentinel;
    }
    return findBegin(_tree->m_sentinel.m_left);
}

BSTreeItr BSTreeItrEnd(const BSTree *_tree)
{
    if (_tree == NULL)
    {
        return NULL;
    }

    return (BSTreeItr)&_tree->m_sentinel;
}

int BSTreeItrEquals(BSTreeItr _a, BSTreeItr _b)
{
    return _a == _b;
}

BSTreeItr BSTreeItrNext(BSTreeItr _it)
{
    int leftLeafOfRightSon = 1, leftSonOfParent = 0;
    BSTreeItr *returnVal;
    /** add check sentinel and null*/

    if (((Node *)_it)->m_right != NULL)
    {
        returnVal = (BSTreeItr)NextItr((Node *)_it, ((Node *)_it)->m_right, leftLeafOfRightSon);
    }
    else
    {
        returnVal = (BSTreeItr)NextItr((Node *)_it, ((Node *)_it)->m_father, leftSonOfParent);
    }

    return returnVal;
}

BSTreeItr BSTreeItrPrev(BSTreeItr _it)
{
    int rightLeafOfLeftSon = 1, rightSonOfParent = 0;
    BSTreeItr *returnVal;
    /** add check sentinel and null*/
    if (((Node *)_it)->m_left != NULL)
    {
        returnVal = (BSTreeItr)(PrevItr((Node *)_it, ((Node *)_it)->m_left, rightLeafOfLeftSon));
    }
    else
    {
        returnVal = (BSTreeItr)(PrevItr((Node *)_it, ((Node *)_it)->m_father, rightSonOfParent));
    }

    return returnVal;
}

void *BSTreeItrRemove(BSTreeItr _it)
{
    /** add macro is_sentinel to check and return null**/
    if (_it == NULL || IS_SENTINEL(((Node *)_it)))
    {
        return NULL;
    }

    if (IS_LEAF(((Node *)_it)))
    {
        return RemoveLeap(_it);
    }
    else if (IS_HAVE_ONE_CHILD(((Node *)_it)))
    {
        return RmParentWithOneChild(_it);
    }
    else
    {
        return RmParentWithTwoChild(_it);
    }

    return NULL;
}

void *BSTreeItrGet(BSTreeItr _it)
{
    if (_it != NULL || !IS_SENTINEL(((Node *)_it)))
    {
        return ((Node *)_it)->m_data;
    }

    return NULL;
}

BSTreeItr BSTreeForEach(const BSTree *_tree, BSTreeTraversalMode _mode, ActionFunction _action, void *_context)
{
    BSTreeItr returnVal = NULL;

    if (_tree == NULL || _tree->m_sentinel.m_left == NULL || _action == NULL)
    {
        return NULL;
    }

    switch (_mode)
    {
    case BST_TRAVERSAL_IN_ORDER:
        returnVal = inOrder(_tree->m_sentinel.m_left, _action, _context);
        break;

    case BST_TRAVERSAL_PRE_ORDER:
        returnVal = preOrder(_tree->m_sentinel.m_left, _action, _context);
        break;

    case BST_TRAVERSAL_POST_ORDER:
        returnVal = postOrder(_tree->m_sentinel.m_left, _action, _context);
        break;
    }

    return returnVal;
}

/*********************************************************
  BSTreeInsert auxiliary functions
*********************************************************/
static Node *CreateNode(void *_data)
{
    Node *newNode;

    newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        return NULL;
    }

    newNode->m_data = _data;
    newNode->m_left = NULL;
    newNode->m_right = NULL;

    return newNode;
}

static BSTreeItr nodeInsert(LessComparator _less, Node *_root, Node *_newNode)
{
    /**add less result**/
    if (_root->m_left == NULL && _less(_root->m_data, _newNode->m_data) < 0)
    {
        _root->m_left = _newNode;
        _newNode->m_father = _root;
        return (BSTreeItr)_newNode;
    }
    else if (_root->m_right == NULL && _less(_root->m_data, _newNode->m_data) > 0)
    {
        _root->m_right = _newNode;
        _newNode->m_father = _root;
        return (BSTreeItr)_newNode;
    }
    else if (_less(_root->m_data, _newNode->m_data) == 0)
    {
        /** if duplicate node**/
        return NULL;
    }

    if (_less(_root->m_data, _newNode->m_data) < 0)
    {
        return nodeInsert(_less, _root->m_left, _newNode);
    }
    return nodeInsert(_less, _root->m_right, _newNode);
}

/*********************************************************
  BSTreeDestroy auxiliary functions
*********************************************************/
static void destroyNodes(Node *_node, void (*_destroyer)(void *))
{
    if (_node == NULL)
    {
        return;
    }

    destroyNodes(_node->m_left, _destroyer);
    destroyNodes(_node->m_right, _destroyer);

    if (_destroyer != NULL)
    {
        _destroyer(_node->m_data);
    }

    free(_node);
}

/*********************************************************
  BSTreeForEach auxiliary functions
*********************************************************/
static BSTreeItr inOrder(Node *_node, ActionFunction _action, void *_context)
{
    BSTreeItr returnVal = NULL;

    if (_node == NULL)
    {
        return NULL;
    }

    returnVal = inOrder(_node->m_left, _action, _context);
    if (returnVal)
    {
        return returnVal;
    }

    if (_action(_node->m_data, _context) == 0)
    {
        return _node;
    }

    return inOrder(_node->m_right, _action, _context);
}

static BSTreeItr postOrder(Node *_node, ActionFunction _action, void *_context)
{
    void *value;

    if (_node == NULL)
    {
        return (BSTreeItr)_node;
    }

    postOrder(_node->m_left, _action, _context);
    postOrder(_node->m_right, _action, _context);

    value = _node->m_data;
    if (_action(value, _context) == 0)
    {
        return (BSTreeItr)_node;
    }

    return (BSTreeItr)_node;
}

static BSTreeItr preOrder(Node *_node, ActionFunction _action, void *_context)
{
    void *value;

    if (_node == NULL)
    {
        return (BSTreeItr)_node;
    }

    value = _node->m_data;
    if (_action(value, _context) == 0)
    {
        return (BSTreeItr)_node;
    }

    preOrder(_node->m_left, _action, _context);
    preOrder(_node->m_right, _action, _context);

    return (BSTreeItr)_node;
}

/*********************************************************
  BSTreeItrRemove auxiliary functions
*********************************************************/
static void *RmParentWithTwoChild(BSTreeItr _it)
{
    BSTreeItr itr;

    itr = Swap(_it);

    if (IS_LEAF(((Node *)itr)))
    {
        return RemoveLeap(itr);
    }
    else
    {
        return RmParentWithOneChild(itr);
    }
}

static void *Swap(BSTreeItr _it)
{
    void *temp, *next;
    Node *nextItr = ((Node *)BSTreeItrNext(_it));

    next = (nextItr)->m_data;
    temp = ((Node *)_it)->m_data;

    ((Node *)_it)->m_data = next;
    nextItr->m_data = temp;

    return nextItr;
}

static void *RmParentWithOneChild(BSTreeItr _it)
{
    void *data = ((Node *)_it)->m_data;

    if (IS_LEFT_CHILD(((Node *)_it)))
    {
        ((Node *)_it)->m_father->m_left = ((Node *)_it)->m_left;
        ((Node *)_it)->m_left->m_father = ((Node *)_it)->m_father;
    }
    else if (IS_RIGHT_CHILD(((Node *)_it)))
    {
        ((Node *)_it)->m_father = ((Node *)_it)->m_right;
        ((Node *)_it)->m_right->m_father = ((Node *)_it)->m_father;
    }

    free(_it);
    return data;
}

static void *RemoveLeap(BSTreeItr _it)
{
    void *data = ((Node *)_it)->m_data;

    if (IS_LEFT_CHILD(((Node *)_it)))
    {
        ((Node *)_it)->m_father->m_left = NULL;
    }
    else
    {
        ((Node *)_it)->m_father->m_right = NULL;
    }

    free(_it);
    return data;
}

/*********************************************************
  BSTreeItrNext & BSTreeItrPrev auxiliary functions
*********************************************************/
static Node *NextItr(Node *_node, Node *_nextNode, int _whereFindTheNext)
{

    if (_whereFindTheNext == 1)
    {
        if (_nextNode->m_left == NULL)
        {
            return _nextNode;
        }
        else
        {
            return NextItr(_node, _nextNode->m_left, 1);
        }
    }

    if (_node == _nextNode->m_left)
    {
        return _nextNode;
    }
    else
    {
        return NextItr(_node, _nextNode->m_father, 0);
    }
}

static Node *PrevItr(Node *_node, Node *_prevNode, int _whereFindThePrev)
{
    if (_whereFindThePrev == 1)
    {
        if (_prevNode->m_right == NULL)
        {
            return _prevNode;
        }
        else
        {
            return PrevItr(_node, _prevNode->m_right, 1);
        }
    }

    if (_node == _prevNode)
    {
        return _node;
    }

    if (_node == _prevNode->m_right)
    {
        return _prevNode;
    }
    else
    {
        return PrevItr(_node, _prevNode->m_father, 0);
    }
}

/*********************************************************
  BSTreeItrBegin auxiliary functions
*********************************************************/
static BSTreeItr findBegin(Node *_node)
{
    if (_node->m_left == NULL)
    {
        return (BSTreeItr)_node;
    }

    return findBegin(_node->m_left);
}
