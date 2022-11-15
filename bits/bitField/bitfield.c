/**********************************************************************************
                                includes && defines
**********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTE 8

/**********************************************************************************
                                Bit field struct
**********************************************************************************/
typedef struct Comp Comp;

struct Comp
{
    unsigned char right : 4;
    unsigned char left : 4;
};

/**********************************************************************************
                     Declaration of static Auxiliary Functions
**********************************************************************************/
static unsigned char Compress(char _leftChar, char _rightChar);
static void PrintBinaryString(char *_str);
static void PrintBinary(unsigned char _byte);

/**********************************************************************************
                                main function
**********************************************************************************/
int CompressString(char _str[])
{
    int i = 0, j = 0;
    int size;

    if (_str == NULL)
    {
        return 0;
    }

    size = strlen(_str);
    while (i < size)
    {
        _str[j++] = Compress(_str[i], _str[i + 1]);
        i += 2;
    }
    _str[j] = '\0';

    return 1;
}

/**********************************************************************************
                                    Main
**********************************************************************************/
int main()
{
    char letters[50] = "abcdefghijklmno";

    if (CompressString(letters) == 1)
    {
        PrintBinaryString(letters);
    }
    printf("\n");

    return 0;
}

/*********************************************************
  CompressString auxiliary functions
*********************************************************/
static unsigned char Compress(char _leftChar, char _rightChar)
{
    unsigned char res = 0;
    Comp *p = &res;

    if (_rightChar != 0)
    {
        _rightChar = _rightChar - 'a' + 1;
    }

    _leftChar = _leftChar - 'a' + 1;
    p->left = _leftChar;
    p->right = _rightChar;
    /**printf("str:%0x\t%0x %0x\n", res, p->left, p->right);**/

    return res;
}

static void PrintBinaryString(char *_str)
{
    int i, size;

    if (_str == NULL)
    {
        return;
    }

    size = strlen(_str);

    for (i = 0; i < size; i++)
    {
        printf("str:%0x\n", _str[i]);
    }

    for (i = 0; i < size; i++)
    {
        PrintBinary(_str[i]);
    }
}

static void PrintBinary(unsigned char _byte)
{
    int i;
    unsigned char byteCopy;

    for (i = BYTE - 1; i >= 0; i--)
    {
        byteCopy = _byte;

        if (byteCopy &= (1 << i))
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }

    printf("  ");
}