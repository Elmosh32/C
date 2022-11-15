#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct Queue Queue;

/**
   Description- The function creates a new queue.
   Input-   size_t _size <=> the size of the new queue.
   Output-  NULL || the new queue address
   Error-   NULL <=>
            if _size == 0 || struct allocation failed || array allocation failed
 **/
Queue*    QueueCreate (size_t _size);

/**
   Description- The function destroys the queue in the given address.
   Input-   Queue *_queue
   Output-  void
   Error-   X
 **/
void      QueueDestroy(Queue *_queue);

/**
   Description- The function inserts values into the queue.
   Input-   Queue *_queue  <=> The address of the queue.
            int _item      <=> item to add.
   Output- OK <=> If the item was successfully added to the queue ||
           NOT_INITIALIZED <=> ||
           FULL_QUEUE <=>
   Error-   NOT_INITIALIZED || FULL_QUEUE
 **/
ADTErr    QueueInsert (Queue *_queue, int _item);
ADTErr    QueueRemove (Queue *_queue, int *_item);
ADTErr    QueueIsEmpty(Queue *_queue);
void      QueuePrint(Queue *_queue);
#endif /* __QUEUE_H__ */
