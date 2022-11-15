#include <stdio.h>
#include <stdlib.h>

static void setbits(unsigned char _x, int _p, int _n, unsigned char _y);
static void setbitsV(unsigned int _w, unsigned int _i, unsigned int _j, unsigned int _value);
static void numOfPairs(unsigned char _num);
static void swapBits(unsigned char n);
static void intToB(unsigned int _num, char _l);
static void numToB(unsigned char _num, char _l);

int main()
{
        setbits(170, 1, 3, 167);
        setbits(170, 6, 3, 167);
        setbits(170, 1, 1, 167);
        printf("*******************************************\n");
        setbitsV(1,1,3,1);
        setbitsV(1,1,3,0);
        setbitsV(1,4,4,1);
        setbitsV(1,4,3,0);
        printf("*******************************************\n");
        numOfPairs(179);
        printf("*******************************************\n");
        swapBits(23);

        return 0;
}

static void setbits(unsigned char _x, int _p, int _n, unsigned char _y){
        int i;
        unsigned char num = 0;

        if(_p < _n || _p > 8 || _p < 1 || _n > 8 || _n < 1) {
                printf("invalid input!\n");
                return;
        }

        numToB(_x, 'x');
        numToB(_y, 'y');

        for (i = 0; i < _n; ++i) {
                num <<= 1;
                num |= 1;
        }

        _x &= ~(num << (_p - _n));
        _x |= (_y & num) << (_p - _n);

        printf("setbits n = %d, p = %d gives ",_n,_p );
        numToB(_x, 'x');
}

static void setbitsV(unsigned int _w, unsigned int _i, unsigned int _j, unsigned int _value){
        if(_i > 31 || _j > 31 || _i > _j || _value > 1) {
                printf("invalid input!\n");
                return;
        }

        while(_i <= _j) {
                if(_value) {
                        _w |= (1 << _i);
                }else{
                        _w &= ~(1 << _i);
                }

                ++_i;
        }

        intToB(_w,'x');
}

static void swapBits(unsigned char _num){
        unsigned char x;
        int i = 0;

        numToB(_num,'x');

        for ( i = 0; i < 8; i+=2) {
                x = ((_num >> i) & 1 ^ (_num >> i+1) & 1);
                x = (x << i) | (x << i+1);
                _num = _num^x;
        }

        printf("after swap\t=>\t");
        numToB(_num,'x');
}

static void numOfPairs(unsigned char _num){
        int i;
        int counter = 0;

        numToB(_num,'x');

        for (i = 7; i >= 0; i--) {
                if((_num & (1 << i) ^ _num & (1 << i+1)) == 0) {
                        counter++;
                        i-=2;
                }else if((_num & (0 << i) ^ _num & (0 << i+1)) == 0) {
                        counter++;
                        i-=2;
                }
        }

        printf("num of pairs:%d\n", counter);
}

static void intToB(unsigned int _num, char _l){
        int i;
        char *str;

        str = (char*) malloc(32*sizeof(char));

        for (i = 31; i >= 0; --i) {
                if((_num & (1 << i))!=0)
                        *(str+(31-i))='1';
                else
                        *(str+(31-i))='0';
        }
        *(str+32) = '\0';

        printf("%c = %d (demical) = %s (binary)\n",_l, _num, str);
}

static void numToB(unsigned char _num, char _l){
        int i;
        char *str;

        str = (char*) malloc(8*sizeof(char));

        for  (i = 0; i < 8; i++) {
                if((_num & (1 << i))!=0)
                        *(str+(7-i))='1';
                else
                        *(str+(7-i))='0';
        }
        *(str+8) = '\0';

        printf("%c = %d (demical) = %s (binary)\n",_l, _num, str);
}
