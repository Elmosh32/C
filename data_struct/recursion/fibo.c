#include <stdio.h>

unsigned long fiboRec(int n);
unsigned long fiboIter(int n);

int main() {
        printf("fiboIter(%d) = %ul\n",20,fiboIter(20));
        printf("fiboIter(%d) = %ul\n",40,fiboIter(40));
        printf("fiboIter(%d) = %ul\n",60,fiboIter(60));
        printf("fiboRec(%d) = %ul\n",20,fiboRec(20));
        printf("fiboRec(%d) = %ul\n",40,fiboRec(40));
        printf("fiboRec(%d) = %ul\n",60,fiboRec(60));

        return 0;
}

/*
   T(N) = T(N-1) + T(N-2)
   = 2T(N-1) + T(N-3)
   = 2T((N-2) + (N-3)) + T(N-3)

   Time complexity => O(2^N) */
unsigned long fiboRec(int n) {
        if (n>2) {
                return fiboRec(n-2)+fiboRec(n-1);
        }
        else if(n >0) {
                return 1;
        }
        else{
                return 0;
        }

}

/* Time complexity => O(N) */
unsigned long fiboIter(int n) {
        int i, first = 0, second =1;
        unsigned long fibo;

        for (i = 2; i <= n; i++) {
                fibo = first + second;
                first = second;
                second = fibo;
        }

        return fibo;
}
