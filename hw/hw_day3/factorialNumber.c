#include <stdio.h>

int main()
{
        int num, i;
        long factorial = 1;
        printf("Please enter a positive number\n");
        scanf("%d", &num);
        putchar('\n');

        if(num < 0) {
                printf("Error!! negative number.\nplease try again\n");
                return -1;
        }

        for ( i = 1; i <= num; i++) {
                factorial*=i;
        }

        printf("%d! = %ld", num, factorial);
        putchar('\n');
        putchar('\n');

        return 0;
}
