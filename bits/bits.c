#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int intNumOfBits(unsigned int _num);
static int charNumOfBits(unsigned char _num);
static void numToB(unsigned char _num, char _l);
static void inverted(unsigned char _num);
static int rotate(unsigned char _num, int _bitsToRotate);
static int asciNewFormat(char _str[]);
static int TestBit(int _n, unsigned char _byte);
static void intToB(unsigned int _num, char _l);

int main()
{
        printf("int:%d\n", intNumOfBits(7));

        printf("char:%d\n", charNumOfBits(7));

        /**
           asciNewFormat(str);

           printf("int:%d\n", intNumOfBits(x));

           printf("char:%d\n", charNumOfBits(y));

           printf("\n******************************************************************\n"
               "                           Invert                                 \n"
               "******************************************************************\n");
           inverted(y);
           inverted(0);
           inverted(1);
           inverted(2);
           inverted(3);
           inverted(4);

           printf("\n******************************************************************\n"
               "                            Rotate                                \n"
               "******************************************************************\n");
           rotate(y,-3);
           rotate(y,1);
           rotate(y,2);
           rotate(y,3);
           rotate(y,4);
           rotate(y,5);
           rotate(y,6);
           rotate(y,7);
           rotate(y,8);
           rotate(y,9);
           rotate(y,10);
           rotate(y,11);
         **/
        return 0;
}

static int intNumOfBits(unsigned int _num)
{
        int counter = 0;
        while (_num)
        {
                _num &= (_num - 1);
                counter++;
        }
        return counter;
}

static int charNumOfBits(unsigned char _num)
{
        int counter = 0, i;

        for (i = 0; i < 8; i++)
        {
                if ((_num & (1 << i)) != 0)
                        counter++;
        }
        return counter;
}

static void intToB(unsigned int _num, char _l)
{
        int i;
        char *str;

        str = (char *)malloc(32 * sizeof(char));

        for (i = 31; i >= 0; --i)
        {
                if ((_num & (1 << i)) != 0)
                        *(str + (31 - i)) = '1';
                else
                        *(str + (31 - i)) = '0';
        }
        *(str + 32) = '\0';

        printf("%c = %d (demical) = %s (binary)\n", _l, _num, str);
}

static void numToB(unsigned char _num, char _l)
{
        int i;
        char *str;

        str = (char *)malloc(8 * sizeof(char));

        for (i = 0; i < 8; i++)
        {
                if ((_num & (1 << i)) != 0)
                        *(str + (7 - i)) = '1';
                else
                        *(str + (7 - i)) = '0';
        }
        *(str + 8) = '\0';

        printf("%c = %d (demical) = %s (binary)\n", _l, _num, str);
}

static void inverted(unsigned char _num)
{
        int demicalVal;

        numToB(_num, 'x');
        demicalVal = _num ^ 255;
        printf("inverted\t=>\t");
        numToB(demicalVal, 'x');
        printf("------------------------------------------------------------------\n");
}

static int rotate(unsigned char _num, int _bitsToRotate)
{
        int i;
        unsigned char left = 0, right = 0;

        if (_bitsToRotate < 0)
                return -1;
        numToB(_num, 'x');

        for (i = 0; i < _bitsToRotate % 8; i++)
        {
                if ((_num & (1 << 0)) != 0)
                {
                        _num = _num >> 1;
                        _num ^= (1 << 7);
                }
                else
                {
                        _num = _num >> 1;
                }
        }

        printf("rotated by %d\t=>\t", _bitsToRotate);
        numToB(_num, 'x');
        printf("------------------------------------------------------------------\n");
        return 0;
}

static int asciNewFormat(char _str[])
{
        int i, j, k = 0, check;
        int strLen = strlen(_str);

        for (i = 0; i < strLen; i++)
        {
                if (_str[i] > 'o' || _str[i] < 'a')
                {
                        printf("invalid characters");
                        return;
                }
        }

        for (i = 0; i < strLen - 1; i++)
        {
                _str[i] = (_str[i] - 'a' + 1);
        }

        if (strLen % 2 == 0)
        {
                for (i = 0; i < strLen - 1; i = i + 2)
                {
                        _str[i] = _str[i] << 4;
                        _str[i] = _str[i] | _str[i + 1];
                        _str[k] = _str[i];
                        k++;
                }
                _str[k] = '\0';

                for (i = 0; i < strLen / 2; i++)
                {
                        for (j = 7; j > -1; j--)
                        {
                                check = _str[i] & (1 << j);
                                if (check == 0)
                                        printf("0");
                                else
                                        printf("1");
                        }
                        printf(" ");
                }

                printf("\n");
        }
        else
        {
                for (i = 0; i < strLen / 2; i = i + 2)
                {
                        _str[i] = _str[i] << 4;
                        _str[i] = _str[i] | _str[i + 1];
                        _str[k] = _str[i];
                        k++;
                }
                _str[i] = _str[i] << 4;
                _str[i] = _str[i] | _str[i + 1];
                _str[k] = _str[i];

                for (i = 0; i < strLen / 2 + 1; i++)
                {
                        for (j = 7; j > -1; j--)
                        {
                                check = _str[i] & (1 << j);
                                if (check == 0)
                                        printf("0");
                                else
                                        printf("1");
                        }
                        printf(" ");
                }

                printf("\n");
        }
}
