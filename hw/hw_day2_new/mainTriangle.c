#include <stdio.h>
#include "triangle.h"

int main()
{
        int _size;
        char _charToPrint;
        printf("Please enter char:\n");
        scanf("%c", &_charToPrint);

        printf("Please enter number:\n");
        scanf("%d", &_size);

        putchar('\n');
        triangle1(_charToPrint, _size);
        triangle2(_charToPrint, _size);
        putchar('\n');
        triangle3(_charToPrint, _size);
        putchar('\n');
        triangle4(_charToPrint, _size);
        putchar('\n');
        triangle5(_charToPrint, _size);
        putchar('\n');
        triangle6(_charToPrint, _size);
        putchar('\n');

        return 0;
}
