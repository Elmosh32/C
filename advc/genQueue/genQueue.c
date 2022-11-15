/**********************************************************************************
                                includes && define
**********************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "genQueue.h" /* queue function declartion */

#define FALSE 0
#define TRUE 1

/**********************************************************************************
                                    Queue struct
**********************************************************************************/
struct Queue
{
        void **m_que;
        size_t m_size;
        size_t m_head; /* Index of head in m_que. */
        size_t m_tail; /* Index of tail in m_que. */
        size_t m_nItems;
};

/**********************************************************************************
                                    api functions
**********************************************************************************/
Queue *QueueCreate(size_t _size)
{
        Queue *queue = NULL;

        if (_size == 0)
        {
                return NULL;
        }
        if ((queue = (Queue *)malloc(sizeof(Queue))) == NULL)
        {
                return NULL;
        }
        if ((queue->m_que = (void **)malloc(_size * sizeof(void *))) == NULL)
        {
                free(queue);
                return NULL;
        }

        queue->m_size = _size;
        queue->m_head = 0;
        queue->m_tail = 0;
        queue->m_nItems = 0;
        return queue;
}

void QueueDestroy(Queue **_queue, DestroyItem _itemDestroy)
{
        int i, numElement = (*_queue)->m_nItems;

        if (_queue == NULL || *_queue == NULL)
        {
                return;
        }

        if (_itemDestroy != NULL && (*_queue)->m_nItems != 0)
        {
                for (i = (*_queue)->m_head; numElement > 0; i = (i + 1) % ((*_queue)->m_size))
                {
                        if ((*_queue)->m_que[i] == NULL)
                        {
                                break;
                        }
                        _itemDestroy((*_queue)->m_que[i]);
                        numElement--;
                }
        }

        free((*_queue)->m_que);
        free(*_queue);
        *(_queue) = NULL;
}

QueueResult QueueInsert(Queue *_queue, void *_item)
{
        if (_queue == NULL)
                return QUEUE_UNINITIALIZED_ERROR;

        if (_queue->m_head == _queue->m_tail && _queue->m_nItems == _queue->m_size)
        {
                return QUEUE_OVERFLOW_ERROR;
        }

        _queue->m_que[_queue->m_tail] = _item;
        _queue->m_tail = (_queue->m_tail + 1) % _queue->m_size;
        _queue->m_nItems++;

        return QUEUE_SUCCESS;
}

QueueResult QueueRemove(Queue *_queue, void **_item)
{
        if (_queue == NULL)
        {
                return QUEUE_UNINITIALIZED_ERROR;
        }
        if (_item == NULL)
        {
                return QUEUE_DATA_UNINITIALIZED_ERROR;
        }
        if (_queue->m_nItems == 0)
        {
                return QUEUE_DATA_NOT_FOUND_ERROR;
        }
        *_item = _queue->m_que[_queue->m_head];
        _queue->m_nItems--;
        _queue->m_head = (_queue->m_head + 1) % (_queue->m_size);
        return QUEUE_SUCCESS;
}

size_t QueueIsEmpty(Queue *_queue)
{
        if (_queue == NULL || _queue->m_nItems == 0)
        {
                return TRUE;
        }

        return FALSE;
}

size_t QueueForEach(Queue *_queue, ActionFunction _action, void *_context)
{
        int i, j;

        if (_queue == NULL || _action == NULL)
        {
                return 0;
        }

        j = (_queue->m_head) - 1;
        for (i = 0; i < _queue->m_nItems; i++)
        {
                j = (j + 1) % (_queue->m_size);
                if (_action(_queue->m_que[j], _context) == 0)
                {
                        break;
                }
        }

        return i;
}

/**
void QueuePrint(Queue *_queue)
{
        size_t i = _queue->m_head;
        int counter = 0;

        if (_queue == NULL || _queue->m_nItems == 0)
        {
                return;
        }

        while (counter != _queue->m_nItems - 1)
        {
                if (i == _queue->m_size)
                        i = 0;

                printf("%d->  ", _queue->m_que[i]);
                i++;
                counter++;
        }

        if (i == _queue->m_size)
                i = 0;
        printf("%d\n", _queue->m_que[i]);
}
**/