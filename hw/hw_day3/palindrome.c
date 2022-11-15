#include <stdio.h>

int main()
{
        int num, numCopy, reversed=0, remainder;
        printf("Please enter a positive number\n");
        scanf("%d",&num);
        numCopy = num;

        if(num < 0) {
                printf("Error!! negative number.\nplease try again\n");
                return -1;
        }

        while (numCopy != 0) {
                remainder = numCopy % 10;
                reversed = reversed * 10 + remainder;
                numCopy /=10;
                printf("%d %d %d\n",numCopy,num,reversed);
        }

        if(reversed == num)
                return 1;
        else
                return 0;
}
