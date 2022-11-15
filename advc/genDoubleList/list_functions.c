#include <stdlib.h>
#include "list_functions.h"

typedef int (*InnearFunc)(int _returnVal, void *_inContext);

typedef struct Info Info;

struct Info
{
    ListActionFunction m_originalFunc;
    void *m_originalContext;
    InnearFunc m_innearFunc;
    void *m_innearContext;
};

static ListItr GenEngine(ListItr _begin, ListItr _end, Info *_info);
static int InFindFirst(int _returnVal, void *_inContext);
static int InCountIf(int _returnVal, void *_inContext);
static int InForEach(int _returnVal, void *_inContext);

ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void *_context)
{
    Info info;
    ListItr itr;

    if (_begin == NULL || _end == NULL || _predicate == NULL || _context == NULL)
    {
        return NULL;
    }

    info.m_originalFunc = _predicate;
    info.m_originalContext = _context;
    info.m_innearFunc = InCountIf;
    info.m_innearContext = NULL;
    itr = GenEngine(_begin, _end, &info);

    return itr;
}

size_t ListItrCountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void *_context)
{
    Info info;
    size_t counter = 0;

    if (_begin == NULL || _end == NULL || _predicate == NULL || _context == NULL)
    {
        return 0;
    }

    info.m_originalFunc = _predicate;
    info.m_originalContext = _context;
    info.m_innearFunc = InFindFirst;
    info.m_innearContext = &counter;
    GenEngine(_begin, _end, &info);

    return counter;
}

ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void *_context)
{
    Info info;
    ListItr itr = _begin;
    if (_begin == NULL || _end == NULL || _action == NULL)
    {
        return NULL;
    }

    info.m_originalFunc = _action;
    info.m_originalContext = _context;
    info.m_innearFunc = InForEach;
    info.m_innearContext = NULL;
    itr = GenEngine(_begin, _end, &info);

    return itr;
}

static ListItr GenEngine(ListItr _begin, ListItr _end, Info *info)
{
    ListItr itr = _begin;
    void *element;

    while (itr != _end)
    {
        element = ListItrGet(itr);
        if (info->m_innearFunc(info->m_originalFunc(element, info->m_originalContext), info->m_innearContext))
        {
            break;
        }

        itr = ((Node *)itr)->m_next;
    }

    return itr;
}

static int InFindFirst(int _returnVal, void *_context)
{
    return !_returnVal;
}

static int InCountIf(int _returnVal, void *_context)
{
    if (_returnVal != 0)
    {
        (*(size_t *)_context)++;
        return _returnVal;
    }

    return 0;
}

static int InForEach(int _returnVal, void *_context)
{
    return _returnVal;
}