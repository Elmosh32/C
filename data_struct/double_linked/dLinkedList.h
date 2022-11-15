#ifndef __DLINKEDLIST_H__
#define __DLINKEDLIST_H__

#include <stddef.h>  /*size_t*/

#include "ADTDefs.h"

typedef struct List List;
typedef struct Node Node;

List* ListCreate();
void ListDestroy(List* _list);

ADTErr ListPushHead(List* _list, int _data);
ADTErr ListPushTail(List* _list, int _data);
ADTErr ListPopHead(List* _list, int* _data);
ADTErr ListPopTail(List* _list, int* _data);

size_t ListCountItems(List* _list);
int ListIsEmpty(List* _list);
void ListPrint(List* _list);

#endif /*__DLINKEDLIST_H__*/
