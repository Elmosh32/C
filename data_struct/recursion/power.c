#include <stdio.h>

int pow(int n, int k);

int main() {
        int n = 2, k = 5;
        printf("%d^%d = %d\n",n,k,pow(n,k));

        return 0;
}

int pow(int n, int k)
{
        if (k != 0)
                return n*pow(n, k-1);
        else
                return 1;
}
