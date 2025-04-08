#include <stdlib.h>

typedef struct QueueNode_st {
    void* value;
    struct QueueNode_st *next;
    struct QueueNode_st *prev;
} QueueNode;

typedef struct Queue_st {
    QueueNode *first;
    QueueNode *last;
    size_t size;
} Queue;

Queue* QueueInit()
{
    Queue *ret = calloc(1, sizeof(Queue));
    return ret;
}

void QueuePushBack(Queue *q, void* value)
{
#ifdef DEBUG
    printf("Enqueue %s\n", value);
#endif
    QueueNode *new = malloc(sizeof(QueueNode));
    new->prev = q->last;
    if (q->last)
    {
        q->last->next = new;
        q->last = new;
    }
    ++q->size;
}