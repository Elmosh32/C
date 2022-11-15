
#include <stdlib.h>
#include <stdio.h>

#include "structs.h"
#include "list_itr.h"

ListItr ListItrBegin(const List *_list)
{
    if (_list == NULL)
    {
        return NULL;
    }

    return (ListItr)_list->m_head.m_next;
}

ListItr ListItrEnd(const List *_list)
{
    if (_list == NULL)
    {
        return NULL;
    }

    return (ListItr) & (_list->m_tail);
}

int ListItrEquals(const ListItr _a, const ListItr _b)
{
    return (_a == _b);
}

ListItr ListItrNext(ListItr _itr)
{
    if (_itr == NULL)
    {
        return NULL;
    }

    if ((((Node *)(_itr))->m_next) == NULL)
    {
        return NULL;
    }

    return (((Node *)(_itr))->m_next);
}

ListItr ListItrPrev(ListItr _itr)
{
    if (_itr == NULL)
    {
        return NULL;
    }

    if (((Node *)_itr)->m_prev == ((Node *)_itr)->m_prev->m_prev)
    {
        return _itr;
    }

    return ((Node *)_itr)->m_prev;
}

void *ListItrGet(ListItr _itr)
{
    if (_itr == NULL)
    {
        return NULL;
    }

    if (_itr == ((Node *)_itr)->m_next)
    {
        return NULL;
    }

    return ((Node *)_itr)->m_data;
}

void *ListItrSet(ListItr _itr, void *_element)
{
    void *temp = NULL;

    if (_itr == NULL || _element == NULL || ((Node *)_itr)->m_next == _itr)
    {
        return NULL;
    }

    temp = ((Node *)_itr)->m_data;
    ((Node *)_itr)->m_data = _element;
    return temp;
}

ListItr ListItrInsertBefore(ListItr _itr, void *_element)
{
    Node *newNode = NULL;

    if (_itr == NULL || _element == NULL)
    {
        return NULL;
    }

    if ((newNode = (Node *)malloc(sizeof(Node))) == NULL)
    {
        return NULL;
    }

    newNode->m_data = (void *)_element;
    newNode->m_prev = ((Node *)_itr)->m_prev;
    newNode->m_next = (Node *)_itr;

    newNode->m_prev->m_next = newNode;
    newNode->m_next->m_prev = newNode;

    return (ListItr)newNode;
}

void *ListItrRemove(ListItr _itr)
{
    void *del = NULL;

    if (_itr == NULL || _itr == ((Node *)_itr)->m_next)
    {
        return NULL;
    }

    del = ((Node *)_itr)->m_data;
    ((Node *)_itr)->m_prev->m_next = ((Node *)_itr)->m_next;
    ((Node *)_itr)->m_next->m_prev = ((Node *)_itr)->m_prev;
    free(_itr);

    return del;
}
