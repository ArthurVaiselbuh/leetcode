#include <stdio.h>

#define DEBUG

#include "utils/vector.h"


struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct ListNode ListNode_t;
void PrintList(ListNode_t *l);

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    if (!head || !head->next || k == 1)
    {
        return head;
    }
    Vector *vec = VectorInitSize(k);
    ListNode_t *newHead = NULL;
    ListNode_t *lastKEnd = NULL;
    ListNode_t *pos = head;
    while (pos)
    {
        VectorPushBack(vec, pos);
        if (vec->count != k)
        {
            pos = pos->next;
            continue;
        }
#ifdef DEBUG
        char buf[20] = {0};
        if (lastKEnd)
        {
            snprintf(buf, sizeof(buf)/sizeof(buf[0]), "%d", lastKEnd->val);
        }
        printf("Count reached %d, starting to reverse. Current pos value: %d, lastKEnd value: %s\n",
            k,
            pos->val,
            lastKEnd ? buf : "NULL"
        );
#endif
        // time to reverse!
        ListNode_t *cur_next = pos->next;
        for (int i = k; i>=2; i--)
        {
            ((ListNode_t*)vec->buffer[i-1])->next = vec->buffer[i-2];
        }
        ((ListNode_t*)vec->buffer[0])->next=cur_next;
        if (lastKEnd)
        {
            lastKEnd->next = vec->buffer[k-1];
        }
        if (!newHead)
        {
            newHead = vec->buffer[k-1];
        }
        // empty the vector
        lastKEnd = vec->buffer[0];
        vec->count = 0;
        pos = cur_next;
#ifdef DEBUG
        printf("State after reversing: ");
        PrintList(newHead);
#endif
    }
    VectorTeardown(vec);
    if (!newHead)
    {
        // Less than k items in original list
        return head;
    }
    return newHead;
}

// Helpers

void PrintList(ListNode_t *l)
{
    while (l)
    {
        printf("%d->", l->val);
        l = l->next;
    }
    printf("NULL\n");
}

ListNode_t* BuildList(int arr[], size_t count)
{
    ListNode_t *head = NULL;
    ListNode_t *prev = NULL;
    for (int i=0;i<count;i++)
    {
        ListNode_t *node = malloc(sizeof(ListNode_t));
        node->val = arr[i];
        if (!head)
        {
            head = node;
        }
        if (prev)
        {
            prev->next = node;
        }
        prev = node;
    }
    return head;
}

void FreeList(ListNode_t* l)
{
    while (l)
    {
        ListNode_t *tmp = l->next;
        free(l);
        l = tmp;
    }
}

void test_build_list()
{
    int arr[5] = {1,2,3,4,5};
    ListNode_t *l = BuildList(arr, 5);
    PrintList(l);
    FreeList(l);
}

int main(int argc, char **argv)
{
    ListNode_t *l= BuildList((int[]){1, 2, 3, 4, 5}, 5);
    l = reverseKGroup(l, 2);
    printf("Final result:\n");
    PrintList(l);
    FreeList(l);

}
