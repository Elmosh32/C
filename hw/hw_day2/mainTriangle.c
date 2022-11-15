#include <stdio.h>
#include "triangle.h"

int main()
{
        int num1;
        char c;
        printf("Please enter char:\n");
        scanf("%c", &c);

        printf("Please enter number:\n");
        scanf("%d", &num1);

        ex1(c, num1);
        printf("\n");
        ex2(c, num1);
        printf("\n");
        ex3(c, num1);
        printf("\n");
        ex4(c, num1);
        printf("\n");
        ex5(c, num1);
        printf("\n");
        ex6(c, num1);
        printf("\n");
        return 0;
}
