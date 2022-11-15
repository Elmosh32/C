#include "str.h"

/**QUESTION 4**/
int squeeze(char *_str1, char *_str2){
        int w = 0, r, lenStr1, lenStr2;
        char asc[128];
        if (nullCheck(_str1) == 1 || nullCheck(_str2) == 1) {
                return NULL_ERROR;
        }

        lenStr1 = strlen(_str1);
        lenStr2 = strlen(_str2);
        for(r=0; r < lenStr2; r++)
                asc[_str2[r]] = 1;

        for(r=0; r < lenStr1; r++) {
                if(asc[_str1[r]] != 1) {
                        _str1[w]=_str1[r];
                        w++;
                }
        }
        _str1[w]='\0';
        return 0;
}

/**QUESTION 5**/
int location(char _str1[], char _str2[]){
        int i, strLen1, strLen2;

        if (nullCheck(_str1) == 1 || nullCheck(_str2) == 1) {
                return NULL_ERROR;
        }

        strLen1 = strlen(_str1);
        strLen2 = strlen(_str2);
        if (strLen1 < strLen2) {
                return -2;
        }

        for (i = 0; i < strLen1 - strLen2 + 1; i++) {
                if(strncmp(_str1,_str2,strLen2) == 0)
                        return i;
                _str1++;
        }
        return -1;
}

/**QUESTION 6**/
int sTrim(char _str[]){
        int w=0,r, length;

        if (nullCheck(_str) == 1) {
                return NULL_ERROR;
        }

        length = strlen(_str);

        for(r=0; r < length; r++) {
                if(_str[r] == ' ' && _str[r+1] == ' ') {
                        while(_str[r+1] == ' ' && _str[r+1] != '\0') {
                                r++;
                        }
                }
                _str[w]=_str[r];
                w++;
        }
        _str[w]='\0';
        return 0;
}

/**QUESTION 7**/
int replace(char *_str1, char *_str2){
        int r, lenStr1, lenStr2;
        char asc[128];
        if (nullCheck(_str1) == 1 || nullCheck(_str2) == 1) {
                return NULL_ERROR;
        }

        lenStr1 = strlen(_str1);
        lenStr2 = strlen(_str2);
        for(r=0; r < lenStr2; r++)
                asc[_str2[r]] = 1;

        for(r=0; r < lenStr1; r++)
                if(asc[_str1[r]] == 1)
                        _str1[r]='*';

        return 0;
}

int myStrcpy(char _str1[], char _str2[]){
        int i;
        int len = strlen(_str2);
        for (i = 0; i < len; i++) {
                _str1[i] = _str2[i];
        }
        return 0;
}

int myStrcat(char _str1[], char _str2[]){
        int i;
        int len1 = strlen(_str1);
        int len2 = strlen(_str2);

        for (i = 0; i < len2; i++) {
                _str1[i+len1] = _str2[i];
        }
        return 0;
}

int myStrcmp(char _str1[], char _str2[]){
        int i;
        int len1 = strlen(_str1);
        int len2 = strlen(_str2);

        for (i = 0; i < len2; i++) {
                if(_str1[i]>_str2[i])
                        return 1;
                else if(_str1[i]<_str2[i])
                        return -1;
        }

        if(len2>len1)
                return -1;
        if(len2<len1)
                return 1;
        return 0;
}

/**auxiliary functions**/
int nullCheck(char *str){
        if (str == NULL)
                return 1;
        return 0;
}
