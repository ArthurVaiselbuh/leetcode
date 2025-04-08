#include <stdlib.h>
#include <stdio.h>

#include "vector.h"


Vector* VectorInitSize(size_t initial_count)
{
    Vector *vec =  calloc(1, sizeof(Vector));
    if (!vec)
    {
        goto err;
    }
    vec->_alloc_count = initial_count;
    vec->buffer = malloc(initial_count * sizeof(void*));
    vec->count = 0;
    if (!vec->buffer)
    {
        goto err;
    }
#ifdef DEBUG
    printf("Allocated vector with size %zu\n", initial_count);
#endif
    return vec;
err:
    if (vec){
        if (vec->buffer)
        {
            free(vec->buffer);
        }
        free(vec);
    }
    return NULL;
}

Vector* VectorInit()
{
    return VectorInitSize(8);
}

void VectorPushBack(Vector *v, void* value)
{
#ifdef DEBUG
    printf("PushBack %s\n", (char*)value);
#endif
    if (v->_alloc_count == v->count)
    {
        v->_alloc_count *= 2;
#ifdef DEBUG
        printf("Reallocating buffer to size %zu\n", v->_alloc_count * sizeof(void*));
#endif
        void* new_buffer = realloc(v->buffer, v->_alloc_count  * sizeof(void*));
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

void* VectorRemoveLast(Vector *v)
{
#ifdef DEBUG
    if (v->count == 0)
    {
        printf("Attempting to remove from an empty vector");
    }
#endif
    return v->buffer[--v->count];
}

void VectorTeardown(Vector* vec)
{
    if (!vec)
        return;
    if (vec->buffer)
        free(vec->buffer);
    free(vec);
}