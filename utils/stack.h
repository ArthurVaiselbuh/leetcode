#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

typedef struct StackNode_st {
    void* value;
    struct StackNode_st *down;
} StackNode;

typedef struct Stack_st {
    StackNode *top;
    int size;
} Stack;

Stack* StackInit();
void StackPush(Stack *s, void* value);
void* StackPop(Stack *s);

#endif // STACK_H