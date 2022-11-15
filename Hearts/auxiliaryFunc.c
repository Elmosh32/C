#include "includes/auxiliaryFunc.h"

static int partition(Vector* _vec, size_t _begin, size_t _end);
static void swap(Vector* _vector, int _leftIndex, int _rightIndex);

static void Reverse(char str[]);

void QuickRec(Vector* _vec, size_t _begin, size_t _end){
        int pivot;

        if (_begin >= _end) {
                return;
        }

        pivot =  partition(_vec, _begin, _end);

        if (pivot > 0) {
                QuickRec(_vec, _begin, pivot - 1);
        }

        QuickRec(_vec, pivot + 1, _end);
}

static int partition(Vector* _vec, size_t _begin, size_t _end){
        int rightVal, leftVal, pivot, beginIndex = _begin;

        getVector(_vec, _begin, &pivot);
        _begin++;
        getVector(_vec, _end, &rightVal);
        getVector(_vec,  _begin, &leftVal);

        while(_begin < _end) {
                while(pivot < rightVal) {
                        _end--;
                        getVector(_vec, _end, &rightVal);
                }

                while(pivot >= leftVal && _begin < _end) {
                        _begin++;
                        getVector(_vec,  _begin, &leftVal);
                }

                if(_begin < _end) {
                        swap(_vec, _end, _begin);
                        getVector(_vec, _end, &rightVal);
                        getVector(_vec,  _begin, &leftVal);
                }
        }

        if(rightVal < pivot) {
                swap(_vec, _end, beginIndex);
        }

        return _end;
}

static void swap(Vector* _vector, int _leftIndex, int _rightIndex){
        int biggerVal, smallerVal;

        getVector(_vector, _leftIndex, &biggerVal);
        getVector(_vector, _rightIndex, &smallerVal);

        setVector(_vector, _rightIndex, biggerVal);
        setVector(_vector, _leftIndex, smallerVal);
}

void MyItoa(int _n, char str[])
{
        int i, sign;

        if ((sign = _n) < 0)
        {
                _n = -_n;
        }
        i = 0;
        do
        {
                str[i++] = _n % 10 + '0';
        } while ((_n /= 10) > 0);
        if (sign < 0)
                str[i++] = '-';
        str[i] = '\0';
        Reverse(str);
}

static void Reverse(char str[])
{
        int i, j;
        char c;

        for (i = 0, j = strlen(str)-1; i<j; i++, j--)
        {
                c = str[i];
                str[i] = str[j];
                str[j] = c;
        }
}
