#define DEBUG

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils/vector.h"

#ifndef NULL
#define NULL 0
#endif

#ifndef NULLPTR
#define NULLPTR (void*)0
#endif

typedef char bool;


void skip_slashes(char** path)
{
    while (**path == '/')
    {
        ++(*path);
    }
}

size_t getNextDirFile(char** remainder_ref)
{
    if (!**remainder_ref)
    {
        return 0;
    }
    skip_slashes(remainder_ref);
    char* remainder = *remainder_ref;
    char* next = strstr(remainder, "/");
    if (!next)
    {
        return strlen(remainder);
    }
    return next - remainder;
}

char* simplifyPath(char* path) {

#ifdef DEBUG
    printf("\n\nBegin simplifying:\n%s\n", path);
#endif
    size_t original_len = strlen(path);
    // TODO: alternative solution if I parse it from the back - I will know in advance how many levels of "up" I can skip in advance
    Vector *vec = VectorInit();
    char *tmp = calloc(2, sizeof(char));
    tmp[0] = '/';
    VectorPushBack(vec, tmp);
    size_t next_size = 0;
    // Total len of resulting string
    while ((next_size = getNextDirFile(&path)))
    {
        if (next_size == 1 && *path == '.'){
            path++;
            continue;
        }
        if (next_size == 2 && !strncmp(path, "..", 2))
        {
            path += next_size;
            if (vec->count == 1)
            {
                // Don't remove root
                continue;
            }
            free(VectorRemoveLast(vec));
            continue;
        }
        tmp = malloc(next_size + 1);
        memcpy(tmp, path, next_size);
        tmp[next_size] = '\0';
        VectorPushBack(vec, tmp);
        path += next_size;
    }

#ifdef DEBUG
    printf("Done simpliying! Parts are\n");
    for (int i=0; i< vec->count;i++)
    {
        printf("%d: %s\n", i, (char*)vec->buffer[i]);
    }
#endif
    // Build return string
    char *ret = malloc(original_len+1);
    size_t write_idx = 0;
    for (int i=0; i<vec->count; i++)
    {
        size_t part_len = strlen((char*)vec->buffer[i]);
        if (i>1)
        {
            ret[write_idx++] = '/';
        }
        memcpy(ret + write_idx, (char*)vec->buffer[i], part_len);
        write_idx += part_len;
    }
    ret[write_idx] = '\0';
    return ret;
}

#define ASSERT(x) if (!(x)) {printf("Failed on line %d !\n", __LINE__); exit(1);};
void test_cmp(char* a_to_free, char* b) {
#ifdef DEBUG
    printf("Comparing <%s> to <%s>\n", a_to_free, b);
#endif
    ASSERT(a_to_free);
    ASSERT(b);
    ASSERT(!strncmp(a_to_free, b, 100));
    free(a_to_free);
}

int main(int argc, char **argv)
{
    // test_stack();
    // return 0;
    test_cmp(simplifyPath("/home/"), "/home");
    test_cmp(simplifyPath("/home"), "/home");
    test_cmp(simplifyPath("/"), "/");
    test_cmp(simplifyPath("//////"), "/");
    test_cmp(simplifyPath("/home/////"), "/home");
    test_cmp(simplifyPath("/home/..////"), "/");
    test_cmp(simplifyPath("/home/../a/..///"), "/");
    test_cmp(simplifyPath("/home//a/././..///"), "/home");
    test_cmp(simplifyPath("/../"), "/");
    test_cmp(simplifyPath("/home/user/Documents/../Pictures"), "/home/user/Pictures");
    test_cmp(simplifyPath("user/Documents/../Pictures"), "/user/Pictures");
    test_cmp(simplifyPath("/oCTY/XJwyB/zA/qgfp/RQFl/kY/./Pa/nth/"), "/oCTY/XJwyB/zA/qgfp/RQFl/kY/Pa/nth");

}
