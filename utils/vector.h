#pragma once

#include <stdlib.h>

// Vector structure definition
typedef struct Vector_st {
    void** buffer;
    size_t count;
    size_t _alloc_count;
} Vector;

// Function declarations
Vector* VectorInit();
Vector* VectorInitSize(size_t initial_size);
void VectorTeardown(Vector *vec);
void VectorPushBack(Vector *v, void* value);
void* VectorRemoveLast(Vector *v);
