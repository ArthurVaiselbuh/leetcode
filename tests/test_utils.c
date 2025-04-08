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
    Vector *v = VectorInit(2);

    char *item1 = "item1";
    char *item2 = "item2";
    char *item3 = "item3";

    VectorPushBack(v, (void*)item1);
    VectorPushBack(v, (void*)item2);
    VectorPushBack(v, (void*)item3);

    TEST_ASSERT_EQUAL(3, v->count);
    TEST_ASSERT_EQUAL_STRING("item1", (char*)v->buffer[0]);
    TEST_ASSERT_EQUAL_STRING("item2", (char*)v->buffer[1]);
    TEST_ASSERT_EQUAL_STRING("item3", (char*)v->buffer[2]);

    VectorRemoveLast(v);
    TEST_ASSERT_EQUAL(2, v->count);

    VectorTeardown(v);
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

void test_vector_init_size_and_push(void) {
    Vector *v = VectorInitSize(2);
    // printf("Original buffer positioned at %p\n", v->buffer);

    char *item1 = "item1";
    char *item2 = "item2";
    char *item3 = "item3";
    char *item4 = "item4";
    char *item5 = "item5";
    char *item6 = "item6";
    char *item7 = "item7";
    char *item8 = "item8";

    VectorPushBack(v, (void*)item1);
    VectorPushBack(v, (void*)item2);
    TEST_ASSERT_EQUAL(2, v->count);
    TEST_ASSERT_EQUAL_STRING("item1", (char*)v->buffer[0]);
    TEST_ASSERT_EQUAL_STRING("item2", (char*)v->buffer[1]);

    VectorPushBack(v, (void*)item3);
    VectorPushBack(v, (void*)item4);
    TEST_ASSERT_EQUAL(4, v->count);
    TEST_ASSERT_EQUAL_STRING("item1", (char*)v->buffer[0]);
    TEST_ASSERT_EQUAL_STRING("item2", (char*)v->buffer[1]);
    TEST_ASSERT_EQUAL_STRING("item3", (char*)v->buffer[2]);
    TEST_ASSERT_EQUAL_STRING("item4", (char*)v->buffer[3]);

    VectorPushBack(v, (void*)item5);
    VectorPushBack(v, (void*)item6);
    VectorPushBack(v, (void*)item7);
    VectorPushBack(v, (void*)item8);
    TEST_ASSERT_EQUAL(8, v->count);
    TEST_ASSERT_EQUAL_STRING("item1", (char*)v->buffer[0]);
    TEST_ASSERT_EQUAL_STRING("item2", (char*)v->buffer[1]);
    TEST_ASSERT_EQUAL_STRING("item3", (char*)v->buffer[2]);
    TEST_ASSERT_EQUAL_STRING("item4", (char*)v->buffer[3]);
    TEST_ASSERT_EQUAL_STRING("item5", (char*)v->buffer[4]);
    TEST_ASSERT_EQUAL_STRING("item8", (char*)v->buffer[7]);

    VectorTeardown(v);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_vector_push_back_and_remove_last);
    RUN_TEST(test_stack_push_and_pop);
    RUN_TEST(test_vector_init_size_and_push);
    return UNITY_END();
}
