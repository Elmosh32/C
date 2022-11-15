#include <stdio.h>
#include <string.h>
#include "str.h"

char* reverse(char *_str){
        int size = strlen(_str);
        char  *retVal;
        int i, counter = size-1;

        if (_str == NULL) {
                return "NULL_ERROR";
        }

        for(i=0; i<size; i++) {
                *(retVal+i)=*(_str+counter);
                counter--;
        }
        *(retVal+i)= '\0';

        return retVal;
}


int isPal(char *_str, char *_revStr){

        if(strcmp(_revStr,_str)==0)
                return 1;
        else
                return 0;
}


int myAtoI(char *_str){
        int num = 0, sign;
        int i;

        if (_str == NULL) {
                return NULL_ERROR;
        }

        i = skipBlanks(_str);
        sign = checkSign(_str, i);
        num = calculateNum(_str, i, sign);

        return num*sign;
}

int skipBlanks(char *_str){
        int i;
        int size = strlen(_str);

        for(i=0; i<size; i++) {
                if(*(_str+i) != ' ') {
                        break;
                }
        }
        return i;
}

int checkSign(char * _str, int _i){
        int sign;
        if(*(_str+_i) == '-') {
                sign = -1;
        }else if(*(_str+_i) == '+')
                sign = 1;
        else
                sign = 0;

        return sign;
}

int calculateNum(char * _str, int _i, int _sign){
        int num, flag = 0;
        if(_sign!=0)
                _i++;
        while (*(_str+_i) >=ZERO_ASCI_VAL && *(_str+_i) <= NINE_ASCI_VAL) {
                if(flag == 0) {
                        num += *(_str+_i) -ZERO_ASCI_VAL;
                        flag = 1;
                        _i++;
                }else{
                        num*=10;
                        num += *(_str+_i) -ZERO_ASCI_VAL;
                        _i++;
                }
        }
        return num;
}

char* myItoA(int _num, char *_buf){
        int numCopy = _num;
        int i=0;

        if(_num<0) {
                *(_buf) = '-';
                numCopy *= -1;
                i++;
        }

        while (numCopy > 0) {
                *(_buf+i) = (numCopy%10) + ZERO_ASCI_VAL;
                numCopy/=10;
                i++;
        }

        *(_buf+i) = '\0';

        if(*(_buf) == '-')
                rotate(_buf, 1, strlen(_buf)-1);
        else
                rotate(_buf, 0, strlen(_buf)-1);

        return _buf;
}


void rotate(char *_buf, int _start, int _end)
{
        char c;
        while (_start < _end)
        {
                c = *(_buf+_start);
                *(_buf+_start) = *(_buf+_end);
                *(_buf+_end)= c;
                _start++;
                _end--;
        }
}
