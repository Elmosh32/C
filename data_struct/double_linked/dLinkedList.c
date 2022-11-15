#include <stdlib.h> /*malloc*/
#include <stdio.h>  /*printf*/

#include "ADTDefs.h"
#include "dLinkedList.h"

#define MAGIC_NUM 90909090

struct Node
{
        int m_data;
        struct Node *m_next;
        struct Node *m_prev;
};

struct List
{
        Node m_head;
        Node m_tail;
        int m_magicNum;
};

static void deleteNode(Node *_node, int *_data);

List *ListCreate()
{
        List *ptr = NULL;

        ptr = (List *)malloc(sizeof(List));

        if (ptr == NULL)
                return NULL;

        ptr->m_head.m_prev = NULL;
        ptr->m_head.m_next = &(ptr->m_tail);
        ptr->m_tail.m_prev = &(ptr->m_head);
        ptr->m_tail.m_next = NULL;
        ptr->m_magicNum = MAGIC_NUM;

        return ptr;
}

void ListDestroy(List *_list)
{
        Node *node = NULL;
        Node *next = NULL;

        if (_list == NULL || _list->m_magicNum != MAGIC_NUM)
                return;

        _list->m_magicNum = 0;
        node = _list->m_head.m_next;
        while (node != &(_list->m_tail))
        {
                next = node->m_next;
                free(node);
                node = next;
        }
        free(_list);
}

ADTErr ListPushHead(List *_list, int _data)
{
        Node *node = NULL;

        if (_list == NULL || _list->m_magicNum != MAGIC_NUM)
                return ERR_NOT_INITIALIZED;

        node = (Node *)malloc(sizeof(Node));

        if (node == NULL)
                return ERR_ALLOCATION_FAILED;

        node->m_data = _data;
        /** add to func**/
        node->m_prev = &_list->m_head;
        node->m_next = _list->m_head.m_next;
        _list->m_head.m_next->m_prev = node;
        _list->m_head.m_next = node;

        return ERR_OK;
}

ADTErr ListPopHead(List *_list, int *_data)
{
        if (_list == NULL || _data == NULL)
                return ERR_NOT_INITIALIZED;

        if (_list->m_head.m_next == &(_list->m_tail))
                return ERR_UNDERFLOW;

        deleteNode(_list->m_head.m_next, _data);

        return ERR_OK;
}

ADTErr ListPopTail(List *_list, int *_data)
{
        if (_list == NULL || _data == NULL)
                return ERR_NOT_INITIALIZED;

        if (_list->m_tail.m_prev == &(_list->m_head))
                return ERR_UNDERFLOW;

        deleteNode(_list->m_tail.m_prev, _data);

        return ERR_OK;
}

static void deleteNode(Node *_node, int *_data)
{
        *_data = _node->m_data;
        _node->m_prev->m_next = _node->m_next;
        _node->m_next->m_prev = _node->m_prev;

        free(_node);
}

ADTErr ListPushTail(List *_list, int _data)
{
        Node *node = NULL;

        if (_list == NULL)
                return ERR_NOT_INITIALIZED;

        node = (struct Node *)malloc(sizeof(struct Node));
        if (node == NULL)
                return ERR_ALLOCATION_FAILED;

        node->m_data = _data;
        /** add func**/
        node->m_prev = _list->m_tail.m_prev;
        node->m_next = &_list->m_tail;
        node->m_prev->m_next = node;
        node->m_next->m_prev = node;

        return ERR_OK;
}

size_t ListCountItems(List *_list)
{
        size_t counter = 0;
        Node *node = NULL;

        if (_list == NULL)
                return 0;

        node = _list->m_head.m_next;
        while (node != &(_list->m_tail))
        {
                node = node->m_next;
                counter++;
        }

        return counter;
}

int ListIsEmpty(List *_list)
{
        if (_list == NULL || _list->m_head.m_next == &(_list->m_tail))
        {
                return 1;
        }

        return 0;
}

void ListPrint(List *_list)
{
        Node *node;
        int i;

        if (_list == NULL)
        {
                printf("ERR NOT INITIALIZED!\n");
                return;
        }

        if (ListIsEmpty(_list) == 1)
        {
                printf("Empty list!\n");
                return;
        }

        node = _list->m_head.m_next;
        for (i = 0; node != &_list->m_tail; i++)
        {
                printf("%d -> ", node->m_data);
                node = node->m_next;
        }
}
