#include <stdio.h>

int main() {
        int num, i, flag = 0;
        printf("Please enter a positive number\n");
        scanf("%d", &num);

        if (num == 0 || num == 1)
                flag = 1;

        for (i = 2; i < num; ++i)
                if (num % i == 0) {
                        flag = 1;
                        break;
                }


        if (flag == 0) {
                printf("1\n");
                return 1;
        }else
                printf("0\n");

        return 0;
}
