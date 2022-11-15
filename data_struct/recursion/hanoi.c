#include <stdio.h>

void Hanoi(int _n, char _from, char _to, char _via);

int main() {
        Hanoi(4,'a','b','c');

        return 0;
}

void Hanoi(int _n, char _from, char _to, char _via)
{
        if(_n > 0) {
                Hanoi(_n-1, _from, _via, _to);
                printf("\n Move disc %d from %c to %c", _n, _from, _to);
                Hanoi(_n-1, _via, _to, _from);
        }
}
