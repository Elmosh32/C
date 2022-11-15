#include <stdio.h>
#include <stdlib.h>

#include "ADTDefs.h"  /* Errors declartion */
#include "queue.h"    /* queue function declartion */

#define MAGIC_NUMBER 6543210 /* flag- if m_magicNum == MAGIC_NUMBER the queue exists otherwise the queue is destroyed */

struct Queue
{
        int*    m_que;
        size_t m_size;
        size_t m_head;     /* Index of head in m_que. */
        size_t m_tail;     /* Index of tail in m_que. */
        size_t m_nItems;
        int m_magicNum;    /* using the MAGIC_NUMBER constant to check if the queue destroyed */
};

Queue* QueueCreate (size_t _size){
        struct Queue* queue = NULL;
        int *qArr;

        if(_size == 0)
                return NULL;
        if((queue = (struct Queue*) malloc (sizeof(struct Queue))) == NULL)
                return NULL;
        if((qArr = (int*)malloc(_size * sizeof(int))) == NULL) {
                free(queue);
                return NULL;
        }

        queue->m_que = qArr;
        queue->m_size = _size;
        queue->m_head = 0;
        queue->m_tail = 0;
        queue->m_nItems = 0;
        queue->m_magicNum = MAGIC_NUMBER;
        return queue;
}

void QueueDestroy(Queue *_queue){
        if (_queue == NULL || _queue->m_magicNum != MAGIC_NUMBER) {
                return;
        }

        _queue->m_magicNum = 0;
        free(_queue->m_que);
        free(_queue);
}

ADTErr QueueInsert (Queue *_queue, int _item){
        if(_queue == NULL || _queue->m_magicNum != MAGIC_NUMBER)
                return NOT_INITIALIZED;

        if(_queue->m_head == _queue->m_tail && _queue->m_nItems == _queue->m_size) {
                return FULL_QUEUE;
        }

        _queue->m_que[_queue->m_tail] = _item;
        _queue->m_tail = (_queue->m_tail + 1) % _queue->m_size;
        _queue->m_nItems++;

        return OK;
}

ADTErr QueueRemove (Queue *_queue, int *_item){
        size_t next;
        if(_queue == NULL || _queue->m_magicNum != MAGIC_NUMBER) {
                return NOT_INITIALIZED;
        }

        if(_queue->m_nItems == 0) {
                return EMPTY_QUEUE;
        }

        next = (_queue->m_head + 1) % _queue->m_size;
        _item = _queue->m_que;
        _queue->m_head = next;
        _queue->m_nItems--;

        return OK;
}

ADTErr QueueIsEmpty(Queue *_queue){
        if(_queue == NULL || _queue->m_magicNum != MAGIC_NUMBER) {
                return NOT_INITIALIZED;
        }

        if(_queue->m_nItems == 0) {
                return EMPTY_QUEUE;
        }

        return OK;
}

void QueuePrint(Queue *_queue){
        size_t i = _queue->m_head;
        int counter=0;

        if (_queue == NULL || _queue->m_magicNum != MAGIC_NUMBER || _queue->m_nItems == 0) {
                return;
        }

        while (counter != _queue->m_nItems-1) {
                if(i == _queue->m_size)
                        i=0;

                printf("%d->  ", _queue->m_que[i]);
                i++;
                counter++;
        }

        if(i == _queue->m_size)
                i=0;
        printf("%d\n", _queue->m_que[i]);
}
