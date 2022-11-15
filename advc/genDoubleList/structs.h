#ifndef __LIST_STRUCTS_H__
#define __LIST_STRUCTS_H__

typedef struct Node Node;
typedef struct List List;

struct Node
{
    void *m_data;
    struct Node *m_next;
    struct Node *m_prev;
};

struct List
{
    Node m_head;
    Node m_tail;
};

#endif /* __LIST_STRUCTS_H__ */
