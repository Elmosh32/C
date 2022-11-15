#include <assert.h>
#include <stdio.h>

/*
(Assert Truth of Expression) In the C Programming Language,
assert is a macro that is designed to be used like a function.

Following is syntax for assertion:
            void assert( int expression );

Case I  : WHEN expression EVALUATES true,
          nothing happens and the compiler proceeds to execute successive
          statements
Case II : WHEN expression EVALUATES false,
          the expression, sourcecode filename, and line number are
          sent to the standard error, and then abort() function is called.
*/
int main()
{
    int *ptr = NULL;
    assert(ptr == NULL);
    printf("after assert\n");
    assert(ptr);

    return 0;
}