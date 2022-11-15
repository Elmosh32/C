#include <stdio.h>

/* Assertion Macro (without abort) */
#define ASSERT(X) (X) ? 0 : (fprintf(stderr, "Assertion failed (" #X ") in file " __FILE__ "on line %d, created on "__DATE__ \
                                             "...\n",                                                                        \
                                     __LINE__))

#define ASSERT1(X) (X) ? 0 : (fprintf(stderr, "Assertion failed (" #X ") in file %s" \
                                              " on line %d, created on %s....\n ",   \
                                      __FILE__, __LINE__, __DATE__))

int main()
{
    int i = 0;
    ASSERT(i);

    printf("after assert\n");

    ASSERT1(i);

    return 0;
}