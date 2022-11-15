#include <stdio.h>

int main()
{
        int num, remainder, remainder1;
        printf("Please enter a positive number\n");
        scanf("%d",&num);

        if(num < 0) {
                printf("Error!! negative number.\nplease try again\n");
                return -1;
        }

        while (num != 0) {
                if(num>9) {
                        remainder = num % 10;
                        num /=10;
                        remainder1 = num % 10;
                        num /=10;
                        if(remainder1>remainder) {
                                printf("01\n");
                                return 0;
                        }
                }else{
                        remainder = num;
                        if(remainder1<remainder) {
                                printf("0\n");
                                return 0;
                        }
                        num /=10;
                }
        }
        printf("1\n");
        return 1;
}
