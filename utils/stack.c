#include <stdlib.h>

typedef struct StackNode_st {
    void* value;
    struct StackNode_st *down;
} StackNode;

typedef struct Stack_st {
    StackNode *top;
    int size;
} Stack;

Stack* StackInit()
{
    Stack *ret = calloc(1, sizeof(Stack));
    return ret;
}

void StackPush(Stack *s, void* value)
{
#ifdef DEBUG
    printf("Pushing %s\n", value);
#endif
    StackNode *newTop = malloc(sizeof(StackNode));
    newTop->value = value;
    newTop->down = s->top;
    ++s->size;
    s->top = newTop;
}

void* StackPop(Stack *s)
{
#ifdef DEBUG
    if (s->size == 0)
    {
        printf("Attempted to pop from an empty stack?!\n");
        exit(1);
    }
#endif

    StackNode *node = s->top;
    s->top = node->down;
    --s->size;
    void* ret = node->value;
    free(node);
#ifdef DEBUG
    printf("Popping %s\n", ret);
#endif
    return ret;
}