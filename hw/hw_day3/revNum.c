#include <stdio.h>

int main()
{
        int num, reversed=0, remainder;
        printf("Please enter a positive number\n");
        scanf("%d",&num);

        if(num < 0) {
                printf("Error!! negative number.\nplease try again\n");
                return -1;
        }

        while (num != 0) {
                remainder = num % 10;
                reversed = reversed * 10 + remainder;
                num /=10;
        }

        printf("%d\n",reversed);

        return 0;
}
