#include <stdio.h>

void multTable(int n, int m, int k);

int main() {
        multTable(1, 1, 10);
        return 0;
}

void multTable(int n, int m, int s) {
        if(n<=s && m<=s) {
                printf("%d\t", n * (m));
                multTable(n, m+1, s);
        }else if(n<s+1 && m==s+1) {
                printf("\n");
                multTable(n+1, 1, s);
        }else if(n==1+s && m==1+s) {
                return;
        }
}
