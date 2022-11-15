/**********************************************************************************
                                includes && defines
**********************************************************************************/
#include <stdio.h>

#define BYTE 8
#define SIZE_OF_LUT 256
#define MASK 0xFF

/**********************************************************************************
                     Declaration of static Auxiliary Functions
**********************************************************************************/
static void BuildCounterLut(unsigned char *_counterLut);

static void BuildRevLut(unsigned int *_lut);
static unsigned char GetRevNum(unsigned char _num);

static void BuildFlipLut(unsigned char *_flipLut);
static unsigned char Flip(unsigned char _num);

static void BuildThirdBitLut(unsigned char *_firstBit, unsigned char *_secondBit, unsigned char *_thirdBit);
static int BitIndex(unsigned char _num, int _bit);

static int GetNumOfOnBits(unsigned char _num);
static int IsBeatOn(unsigned int _bit, int _n);

/**********************************************************************************
                                main functions
**********************************************************************************/
int CountChar(unsigned char _num)
{
    static unsigned char counterLut[SIZE_OF_LUT];
    static char counterFlag;

    if (!counterFlag)
    {
        BuildCounterLut(counterLut);
        counterFlag = 1;
    }

    return counterLut[_num];
}

int CountInt(unsigned int _num)
{
    static unsigned char counterLut[SIZE_OF_LUT];
    static char counterFlag;

    size_t i;
    int counter = 0;

    if (!counterFlag)
    {
        BuildCounterLut(counterLut);
        counterFlag = 1;
    }

    for (i = 0; i < sizeof(int); i++)
    {
        counter += counterLut[_num & MASK];
        _num >>= BYTE;
    }

    return counter;
}

unsigned int ReverseBits(unsigned int _num)
{
    static char revFlag;
    static unsigned int revLut[SIZE_OF_LUT];

    unsigned int counter = 0;
    int i;

    if (!revFlag)
    {
        BuildRevLut(revLut);
        revFlag = 1;
    }

    for (i = 0; i < sizeof(unsigned int); i++)
    {
        /**printf("um:%d\n", revLut[(_num & mask)]);**/
        counter += (revLut[_num & MASK]);
        /**printf("counter:\t%d\n", counter);**/
        _num >>= BYTE;

        if (_num == 0)
        {
            break;
        }
        counter = counter << BYTE;
    }

    return counter;
}

unsigned int FlipBits(unsigned int _num)
{
    static unsigned char flipLut[SIZE_OF_LUT];
    static int flipFlag = 0;

    unsigned int swapBits = 0, temp = 0;
    int i;

    if (flipFlag == 0)
    {
        BuildFlipLut(flipLut);
        flipFlag = 1;
    }

    swapBits = flipLut[_num & MASK];

    for (i = 0; i < sizeof(unsigned int) - 1; i++)
    {
        if (_num == 0)
        {
            break;
        }

        _num >>= BYTE;
        temp = flipLut[_num & MASK];
        temp <<= BYTE * (i + 1);
        swapBits = swapBits | temp;
    }

    return swapBits;
}

int ThirdBit(unsigned int _num)
{
    unsigned int number, index;
    int counter = 0;

    number = _num;

    for (index = 0; index < (sizeof(int) - 1) * BYTE; index++)
    {
        if (IsBeatOn(number, index) == 1)
        {
            counter++;
            if (counter == 3)
            {
                return index;
            }
        }
    }

    return 0;
}

int ThirdBitLut(unsigned int _num)
{
    static unsigned char firstBit[SIZE_OF_LUT];
    static unsigned char secondBit[SIZE_OF_LUT];
    static unsigned char thirdBit[SIZE_OF_LUT];
    static int thirdBitFlag = 0;

    static unsigned char counterLut[SIZE_OF_LUT];
    static char counterFlag;

    int i, counter = 0, numOfBitOn = 0;

    if (thirdBitFlag == 0)
    {
        BuildThirdBitLut(firstBit, secondBit, thirdBit);
        thirdBitFlag = 1;
    }

    if (!counterFlag)
    {
        BuildCounterLut(counterLut);
        counterFlag = 1;
    }

    for (i = 0; i < sizeof(unsigned int); i++)
    {
        numOfBitOn = counterLut[_num & MASK];
        counter += numOfBitOn;

        if (counter >= 3)
        {
            if (counter - numOfBitOn == 0)
            {
                return i * BYTE + thirdBit[_num & MASK];
            }

            if (counter - numOfBitOn == 1)
            {
                return i * BYTE + secondBit[_num & MASK];
            }

            if (counter - numOfBitOn == 2)
            {
                return i * BYTE + firstBit[_num & MASK];
            }
        }
        _num >>= BYTE;
    }

    return 0;
}

/**********************************************************************************
                                    Main
**********************************************************************************/
int main()
{
    printf("CountInt(3):\t%d\n", CountInt(3));
    printf("CountInt(7):\t%d\n", CountInt(7));
    printf("CountInt(127):\t%d\n", CountInt(127));
    printf("CountInt(0):\t%d\n\n", CountInt(0));

    printf("CountChar(3):\t%d\n", CountChar(3));
    printf("CountChar(7):\t%d\n", CountChar(7));
    printf("CountChar(250):\t%d\n", CountChar(250));
    printf("CountChar(0):\t%d\n\n", CountChar(0));

    printf("ReverseBits(3): \t%d\n", ReverseBits(3));
    /**
    3    =>                 0000-0011
    rev  =>     192   =>    1100-0000
    **/

    printf("ReverseBits(7): \t%d\n", ReverseBits(7));
    /**
    7    =>                 0000-0111
    rev  =>     224   =>    1110-0000
    **/

    printf("ReverseBits(127):\t%d\n", ReverseBits(127));
    /**
    127  =>                 0111-1111
    rev  =>     254   =>    1111-1110
    **/
    printf("ReverseBits(0): \t%d\n", ReverseBits(0));
    printf("ReverseBits(300):\t%d\n\n", ReverseBits(300));
    /**
    300         => 0000-0001-0010-1100
    13312       => 0011-0100-0000-0000
    46080       => 1011-0100-0000-0000
    rev 13440   => 0011-0100-1000-0000
    **/

    printf("FlipBits(0):\t%d\n", FlipBits(0));
    printf("FlipBits(1):\t%d\n", FlipBits(1));
    /**
    1           => 0001
    flip 2      => 0010
    **/

    printf("FlipBits(10):\t%d\n", FlipBits(10));
    /**
    10           => 1010
    flip 5       => 0101
    **/

    printf("FlipBits(1024): %d\n", FlipBits(1024));
    /**
    1024                  => 0000-0100-0000-0000
    flip    => 2048       => 0000-1000-0000-0000
    **/

    printf("FlipBits(2048): %d\n\n", FlipBits(2048));
    /**
    2048                   => 0000-1000-0000-0000
    flip    => 1024        => 0000-0100-0000-0000
    **/

    printf("ThirdBit(0):\t%d\n", ThirdBit(0));
    printf("ThirdBit(3):\t%d\n", ThirdBit(3));

    printf("ThirdBit(7):\t%d\n", ThirdBit(7));
    /**
    7                   => 0111
    Third-Bit index     =>   2
    **/
    printf("ThirdBit(1027):\t%d\n", ThirdBit(1027));

    printf("ThirdBitLut(0):\t%d\n", ThirdBitLut(0));
    printf("ThirdBitLut(3):\t%d\n", ThirdBitLut(3));
    /**
     3                   => 0011
     Third-Bit index        => 0
     **/

    printf("ThirdBitLut(7):\t%d\n", ThirdBitLut(7));
    printf("ThirdBitLut(1027):\t%d\n", ThirdBitLut(1027));
    /**
    1027                   => 0000-0100-0000-0011
    Third-Bit index        => 10
    **/

    return 0;
}

/*********************************************************
  CountChar & CountInt & ThirdBitLut auxiliary functions
*********************************************************/
static void BuildCounterLut(unsigned char *_counterLut)
{
    unsigned int i = 0;

    while (i < SIZE_OF_LUT)
    {
        _counterLut[i] = GetNumOfOnBits(i);
        i++;
    }
}

static int GetNumOfOnBits(unsigned char _num)
{
    int counter = 0;
    int i;

    for (i = 0; i < BYTE; i++)
    {
        if (IsBeatOn(_num, i) == 1)
        {
            counter++;
        }
    }

    return counter;
}

static int IsBeatOn(unsigned int _bit, int _n)
{
    int result;
    result = _bit & (1 << _n);

    if (result == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*********************************************************
  ReverseBits auxiliary functions
*********************************************************/
static void BuildRevLut(unsigned int *_revLut)
{
    int i = 0;

    while (i < SIZE_OF_LUT)
    {
        _revLut[i] = GetRevNum((unsigned char)i);
        i++;
    }
}

static unsigned char GetRevNum(unsigned char _num)
{
    unsigned char revNum = 0;
    int i;

    for (i = 0; i < BYTE; i++)
    {
        if (_num & (1 << i))
        {
            revNum |= 1 << ((BYTE - 1) - i);
        }
    }

    return revNum;
}

/*********************************************************
  FlipBits auxiliary functions
*********************************************************/
static void BuildFlipLut(unsigned char *_flipLut)
{
    int i = 0;
    while (i < SIZE_OF_LUT)
    {
        _flipLut[i] = Flip(i);
        i++;
    }
}

static unsigned char Flip(unsigned char _num)
{
    unsigned int result;
    int index;

    result = _num;

    for (index = 0; index < BYTE - 1; index += 2)
    {
        if (IsBeatOn(result, index) != IsBeatOn(result, index + 1))
        {
            result ^= (1 << index);
            result ^= (1 << (index + 1));
        }
    }

    return result;
}

/*********************************************************
  ThirdBitLut auxiliary functions
*********************************************************/
static void BuildThirdBitLut(unsigned char *_firstBit, unsigned char *_secondBit, unsigned char *_thirdBit)
{
    int i = 0;

    while (i < SIZE_OF_LUT)
    {
        _firstBit[i] = BitIndex(i, 1);
        _secondBit[i] = BitIndex(i, 2);
        _thirdBit[i] = BitIndex(i, 3);
        i++;
    }
}

static int BitIndex(unsigned char _num, int _bit)
{
    unsigned int result;
    int counter = 0;
    int index;

    result = _num;

    for (index = 0; index < BYTE - 1; index++)
    {
        if (IsBeatOn(result, index) == 1)
        {
            counter++;
            if (counter == _bit)
            {
                return index;
            }
        }
    }

    return -1;
}
