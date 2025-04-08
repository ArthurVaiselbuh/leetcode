#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

// Vector structure definition
typedef struct Vector_st {
    void** buffer;
    size_t count;
    size_t _alloc_size;
} Vector;

// Function declarations
void VectorPushBack(Vector *v, void* value);
void VectorRemoveLast(Vector *v);

#endif // VECTOR_H
