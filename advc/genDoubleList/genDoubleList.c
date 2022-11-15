#include <stdlib.h> /*malloc*/
#include <stdio.h>  /*printf*/

#include "structs.h"
#include "genDoubleList.h"

static void deleteNode(Node *_node, void **_pItem);
static void AddNode(Node *_node, Node *_next);

List *ListCreate()
{
        List *list = NULL;

        if ((list = (List *)malloc(sizeof(List))) == NULL)
        {
                return NULL;
        }

        list->m_head.m_data = NULL;
        list->m_head.m_prev = &(list->m_head);
        list->m_head.m_next = &(list->m_tail);

        list->m_tail.m_data = NULL;
        list->m_tail.m_next = &(list->m_tail);
        list->m_tail.m_prev = &(list->m_head);

        return list;
}

void ListDestroy(List **_pList, void (*_elementDestroy)(void *_item))
{
        Node *node, *nextNode;

        if (_pList == NULL || *_pList == NULL)
        {
                return;
        }

        node = (*_pList)->m_head.m_next;
        while (node != &((*_pList)->m_tail))
        {
                nextNode = node->m_next;

                if (_elementDestroy != NULL)
                {
                        _elementDestroy(node->m_data);
                }

                free(node);
                node = nextNode;
        }

        free(*_pList);
        *_pList = NULL;
}

ListResult ListPushHead(List *_list, void *_item)
{
        Node *node = NULL;

        if (_list == NULL)
        {
                return LIST_UNINITIALIZED_ERROR;
        }

        if (_item == NULL)
        {
                return LIST_NULL_ELEMENT_ERROR;
        }

        if ((node = (Node *)malloc(sizeof(Node))) == NULL)
        {
                return LIST_ALLOCATION_ERROR;
        }

        node->m_data = _item;
        AddNode(node, _list->m_head.m_next);

        return LIST_SUCCESS;
}

ListResult ListPushTail(List *_list, void *_item)
{
        Node *node = NULL;

        if (_list == NULL)
        {
                return LIST_UNINITIALIZED_ERROR;
        }

        if (_item == NULL)
        {
                return LIST_NULL_ELEMENT_ERROR;
        }

        if ((node = (Node *)malloc(sizeof(Node))) == NULL)
        {
                return LIST_ALLOCATION_ERROR;
        }

        node->m_data = _item;
        AddNode(node, &_list->m_tail);

        return LIST_SUCCESS;
}

ListResult ListPopHead(List *_list, void **_pItem)
{
        if (_list == NULL || (*_pItem) == NULL)
        {
                return LIST_UNINITIALIZED_ERROR;
        }

        if (_list->m_head.m_next == &(_list->m_tail))
        {
                return LIST_UNDERFLOW_ERROR;
        }

        deleteNode(_list->m_head.m_next, _pItem);

        return LIST_SUCCESS;
}

ListResult ListPopTail(List *_list, void **_pItem)
{
        if (_list == NULL || (*_pItem) == NULL)
        {
                return LIST_UNINITIALIZED_ERROR;
        }

        if (_list->m_tail.m_prev == &(_list->m_head))
        {
                return LIST_UNDERFLOW_ERROR;
        }

        deleteNode(_list->m_tail.m_prev, _pItem);

        return LIST_SUCCESS;
}

size_t ListSize(const List *_list)
{
        size_t counter = 0;
        Node *node = NULL;

        if (_list == NULL)
        {
                return 0;
        }

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

static void deleteNode(Node *_node, void **_pItem)
{
        *_pItem = _node->m_data;
        _node->m_next->m_prev = _node->m_prev;
        _node->m_prev->m_next = _node->m_next;

        free(_node);
}

static void AddNode(Node *_node, Node *_next)
{
        _node->m_prev = _next->m_prev;
        _node->m_next = _next;
        _next->m_prev->m_next = _node;
        _next->m_prev = _node;
}
