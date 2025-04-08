#include <stdlib.h>
#include <stdio.h>

#include "vector.h"


void VectorPushBack(Vector *v, void* value)
{
#ifdef DEBUG
    printf("PushBack %s\n", value);
#endif
    if (v->_alloc_size == v->count)
    {
        v->_alloc_size *= 2;
#ifdef DEBUG
        printf("Reallocating buffer to size %d\n", v->_alloc_size);
#endif
        void* new_buffer = realloc(v->buffer, v->_alloc_size);
        if (!new_buffer)
        {
            printf("Out of memory in %s:%d", __FILE__, __LINE__);
            exit(1);
        }
        v->buffer = new_buffer;
    }
    v->buffer[v->count] = value;
    ++v->count;
}

void VectorRemoveLast(Vector *v)
{
#ifdef DEBUG
    if (v->count == 0)
    {
        printf("Attempting to remove from an empty vector");
    }
#endif
    --v->count;
}
