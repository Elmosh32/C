#include <stdio.h>
#include <string.h>

int isPalindrome(char *arr, int start, int end);

int main() {
        char str[] = "abcaaba";
        int len = strlen(str);
        printf("%d\n", isPalindrome(str,0,len-1));

        return 0;
}

int isPalindrome(char *_str, int _start, int _end)
{
        int res;
        if (_start < _end)
        {
                if (*(_str+_start) ==  *(_str+_end)) {
                        res = isPalindrome(_str, _start + 1, _end - 1);
                        return res;
                }else
                        return 0;
        }else
                return 1;
}
