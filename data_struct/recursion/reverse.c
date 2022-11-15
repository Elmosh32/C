#include <stdio.h>
#include <string.h>

void reverseString(char *arr, int start, int end);

int main() {
        char str[] = "abc";

        int len = strlen(str);
        reverseString(str,0,len-1);
        printf("%s\n", str);

        return 0;
}

void reverseString(char *_str, int _start, int _end)
{
        if (_start < _end)
        {
                char temp = (*(_str+_start));
                (*(_str+_start)) =  (*(_str+_end));
                (*(_str+_end)) = temp;
                reverseString(_str, _start + 1, _end - 1);
        }else
                return;
}
