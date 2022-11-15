#include <stdlib.h>             /*malloc*/
#include <stdio.h>             /*printf*/
#include <stddef.h>  /*size_t*/

#include "ADTDefs.h"
#include "bst.h"

#define MAGIC_NUM 90909090
#define TRUE 1
#define FALSE 0

struct Node
{
        int m_data;
        Node*   m_left;
        Node*   m_right;
        Node*   m_father;
};

struct Tree
{
        Node*   m_root;
        int m_magicNum;
};

static ADTErr nodeInsert(Node* _root, Node* _newNode);
static Node* CreateNode(int _data);
static int nodeExist(Node* _node, int _data);
static void destroyNodes(Node* _node);
static void inOrder(Node* _node);
static void postOrder(Node* _node);
static void preOrder(Node* _node);
static ADTErr fullTree(Node* _root);
static ADTErr areSimilar(Node* _root1, Node* _root2);
static int calcLevel(Node* _root);
static void mirror(Node* _root);
static ADTErr perfectSubTree(Node* _root);

ADTErr isPerfectTree(Tree* _tree){
        if (_tree == NULL || _tree->m_magicNum != MAGIC_NUM) {
                return ERR_NOT_INITIALIZED;
        }

        if(_tree->m_root == NULL || isFullTree(_tree) != ERR_FULL_TREE) {
                return ERR_NOT_PERFECT_TREE;
        }

        return perfectSubTree(_tree->m_root);
}

static ADTErr perfectSubTree(Node* _root){
        if(_root == NULL)
                return ERR_PERFECT_TREE;

        if(calcLevel(_root->m_right) != calcLevel(_root->m_left))
                return ERR_NOT_PERFECT_TREE;

        if(perfectSubTree(_root->m_right) == ERR_PERFECT_TREE) {
                return perfectSubTree(_root->m_left);
        }

        return ERR_NOT_PERFECT_TREE;

}


void mirrorTree(Tree* _tree){
        if (_tree == NULL || _tree->m_magicNum != MAGIC_NUM || _tree->m_root == NULL) {
                return;
        }

        mirror(_tree->m_root);
}

static void mirror(Node* _root)
{
        Node* temp;
        if(_root == NULL) {
                return;
        }
        temp = _root->m_left;
        _root->m_left = _root->m_right;
        _root->m_right = temp;
        mirror(_root->m_left);
        mirror(_root->m_right);
}


int calcTreeLevel(Tree* _tree){
        if (_tree == NULL || _tree->m_root == NULL || _tree->m_magicNum != MAGIC_NUM) {
                return -1;
        }

        if (_tree->m_root->m_left == NULL && _tree->m_root->m_right == NULL) {
                return 0;
        }

        return calcLevel(_tree->m_root);
}

static int calcLevel(Node* _root){
        int left,right;
        if(_root == NULL) {
                return -1;
        }

        left = calcLevel(_root->m_left);
        right = calcLevel(_root->m_right);

        if ((left>right)) {
                return left + 1;
        }else{
                return right + 1;
        }
}

ADTErr areSimilarTree(Tree* _tree1, Tree* _tree2){
        if ((_tree1 == NULL || _tree1->m_magicNum != MAGIC_NUM) || (_tree2 == NULL || _tree2->m_magicNum != MAGIC_NUM)) {
                return ERR_NOT_INITIALIZED;
        }

        if(_tree1->m_root == NULL && _tree2->m_root == NULL) {
                return ERR_SIMILAR;
        }

        return areSimilar(_tree1->m_root, _tree2->m_root);
}

static ADTErr areSimilar(Node* _root1, Node* _root2){
        if ((_root1 == NULL && _root2 == NULL)) {
                return ERR_SIMILAR;
        }
        if(((_root1 != NULL) && (_root2 == NULL)) || ((_root1 == NULL) && (_root2 != NULL))) {
                return ERR_NOT_SIMILAR;
        }

        if(areSimilar(_root1->m_left, _root2->m_left) == ERR_SIMILAR) {
                return areSimilar(_root1->m_right, _root2->m_right);
        }

        return ERR_NOT_SIMILAR;
}

ADTErr isFullTree(Tree* _tree){
        if (_tree == NULL || _tree->m_magicNum != MAGIC_NUM) {
                return ERR_NOT_INITIALIZED;
        }

        if(_tree->m_root == NULL) {
                return ERR_FULL_TREE;
        }

        return fullTree(_tree->m_root);
}

static ADTErr fullTree(Node* _root){
        if((_root->m_left == NULL && _root->m_right != NULL) || (_root->m_right == NULL && _root->m_left !=NULL)) {
                return ERR_NOT_FULL_TREE;
        }else if (_root->m_left == NULL && _root->m_right == NULL) {
                return ERR_FULL_TREE;
        }

        if(fullTree(_root->m_left) == ERR_FULL_TREE) {
                return fullTree(_root->m_right);
        }

        return ERR_NOT_FULL_TREE;
}

Tree* TreeCreate(){
        Tree* tree = NULL;

        if ((tree = (Tree*) malloc (sizeof(Tree))) == NULL)
                return NULL;

        tree->m_magicNum = MAGIC_NUM;
        tree->m_root = NULL;
        return tree;
}

void    destroyTree(Tree* _tree){
        Node *node = NULL;

        if (_tree == NULL || _tree->m_magicNum != MAGIC_NUM)
                return;

        if(_tree->m_root == NULL)
        {
                _tree->m_magicNum = 0;
                free(_tree);
                _tree = NULL;
                return;
        }
        destroyNodes(_tree->m_root);
        _tree->m_magicNum = 0;
        free(_tree);
        _tree =NULL;
}

static void destroyNodes(Node* _node){
        if(_node == NULL)
                return;

        destroyNodes(_node->m_left);
        destroyNodes(_node->m_right);
        free(_node);
        _node = NULL;
}

ADTErr  TreeInsert(Tree* _tree, int _data){
        Node* newNode = NULL;

        if (_tree == NULL || _tree->m_magicNum != MAGIC_NUM)
                return ERR_NOT_INITIALIZED;

        if(nodeExist(_tree->m_root,_data) == TRUE)
                return ERR_DUPLICATE_NODE;

        newNode= CreateNode(_data);
        if(newNode == NULL)
                return ERR_ALLOCATION_FAILED;

        if(_tree->m_root == NULL) {
                _tree->m_root = newNode;
                newNode->m_father = NULL;
                return ERR_OK;
        }
        return nodeInsert(_tree->m_root, newNode);
}


static Node* CreateNode(int _data){
        Node* newNode;

        newNode  = (Node*)malloc(sizeof(Node));

        if(newNode == NULL)
                return NULL;

        newNode->m_data = _data;
        newNode->m_left = NULL;
        newNode->m_right = NULL;
        return newNode;
}

static ADTErr nodeInsert(Node* _root, Node* _newNode){
        if(_root->m_left == NULL && _root->m_data > _newNode->m_data) {
                _root->m_left = _newNode;
                _newNode->m_father =_root;
                return ERR_OK;
        }else if(_root->m_right == NULL && _root->m_data < _newNode->m_data) {
                _root->m_right = _newNode;
                _newNode->m_father = _root;
                return ERR_OK;
        }

        if(_root->m_data > _newNode->m_data) {
                return nodeInsert(_root->m_left, _newNode);
        }
        return nodeInsert(_root->m_right, _newNode);
}

static int nodeExist(Node* _node, int _data){
        if (_node == NULL) {
                return FALSE;
        }

        if (_node->m_data == _data) {
                return TRUE;
        }

        if(_data > _node->m_data)
                nodeExist(_node->m_right,_data);
        nodeExist(_node->m_left,_data);
}

void    TreePrint(Tree* _tree, TreeTraverse _traverseMode){
        if (_tree == NULL || _tree->m_magicNum != MAGIC_NUM)
                return;

        if (_traverseMode == IN_ORDER) {
                printf("IN ORDER:\t");
                inOrder(_tree->m_root);
                printf("\n");
        }else if (_traverseMode == POST_ORDER) {
                printf("POST ORDER:\t");
                postOrder(_tree->m_root);
                printf("\n");
        }else{
                printf("PRE ORDER:\t");
                preOrder(_tree->m_root);
                printf("\n");

        }

}

static void inOrder(Node* _node){
        if (_node == NULL)
                return;

        inOrder(_node->m_left);
        printf("%d ",_node->m_data);
        inOrder(_node->m_right);
}

static void postOrder(Node* _node){
        if (_node == NULL)
                return;

        postOrder(_node->m_left);
        postOrder(_node->m_right);
        printf("%d ",_node->m_data);
}

static void preOrder(Node* _node){
        if (_node == NULL)
                return;

        printf("%d ",_node->m_data);
        preOrder(_node->m_left);
        preOrder(_node->m_right);
}
