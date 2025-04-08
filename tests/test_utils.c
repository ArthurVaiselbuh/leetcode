#include "../unity/unity.h"
#include "../utils/vector.h"
#include "../utils/stack.h"

void setUp(void) {
    // Set up before each test
}

void tearDown(void) {
    // Clean up after each test
}

void test_vector_push_back_and_remove_last(void) {
    Vector v = {0};
    v.buffer = malloc(2 * sizeof(void*));
    v._alloc_size = 2;
    v.count = 0;

    char *item1 = "item1";
    char *item2 = "item2";
    char *item3 = "item3";

    VectorPushBack(&v, item1);
    VectorPushBack(&v, item2);
    VectorPushBack(&v, item3);

    TEST_ASSERT_EQUAL(3, v.count);
    TEST_ASSERT_EQUAL_STRING("item1", (char*)v.buffer[0]);
    TEST_ASSERT_EQUAL_STRING("item2", (char*)v.buffer[1]);
    TEST_ASSERT_EQUAL_STRING("item3", (char*)v.buffer[2]);

    VectorRemoveLast(&v);
    TEST_ASSERT_EQUAL(2, v.count);

    free(v.buffer);
}

void test_stack_push_and_pop(void) {
    Stack *s = StackInit();

    char *item1 = "item1";
    char *item2 = "item2";
    char *item3 = "item3";

    StackPush(s, item1);
    StackPush(s, item2);
    StackPush(s, item3);

    TEST_ASSERT_EQUAL(3, s->size);

    char *popped = (char*)StackPop(s);
    TEST_ASSERT_EQUAL_STRING("item3", popped);
    TEST_ASSERT_EQUAL(2, s->size);

    StackPop(s);
    StackPop(s);
    free(s);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_vector_push_back_and_remove_last);
    RUN_TEST(test_stack_push_and_pop);
    return UNITY_END();
}
