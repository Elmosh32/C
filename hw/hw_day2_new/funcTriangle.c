#include <stdio.h>
#include "triangle.h"

#define OK 0
#define SIZE_ERROR -1
#define CHAR_ERROR -2

int checkParameter(char _charToPrint, int _size)
{
        if(_size > MAX_SIZE || _size < MIN_SIZE)
                return SIZE_ERROR;
        if(_charToPrint > MAX_CHAR || _charToPrint < MIN_CHAR )
                return CHAR_ERROR;

        return 0;
}

void printLine(char _charToPrint, int _size){
        int i;
        for(i=0; i < _size; i++) {
                putchar(_charToPrint);
        }
}

void printSpacesLine(char _charToPrint, int _size){
        int i;
        for(i=0; i < _size; i++) {
                putchar(_charToPrint);
                putchar(' ');

        }
}

int triangle1(char _charToPrint, int _size){
        int rows, result;

        if((result = checkParameter(_charToPrint, _size)) != OK)
                return result;

        for(rows = _size; rows >= 0; rows--) {
                printLine(_charToPrint, rows);
                putchar('\n');
        }

        return OK;
}

int triangle2(char _charToPrint, int _size){
        int rows, result;

        if((result = checkParameter(_charToPrint, _size)) != OK)
                return result;

        for(rows = 0; rows <= _size; rows++) {
                printLine(_charToPrint, rows);
                putchar('\n');
        }

        return OK;
}

int triangle3(char _charToPrint, int _size){
        int rows, result;

        if((result = triangle2(_charToPrint, _size)) != OK)
                return result;

        for(rows = _size - 1; rows > 0; rows--) {
                printLine(_charToPrint, rows);
                putchar('\n');
        }

        return OK;
}

int triangle4(char _charToPrint, int _size){
        int result, rows, cols, counter, spaceCounter=-1;

        if((result = checkParameter(_charToPrint, _size)) != OK)
                return result;

        for (rows = 0; rows <= _size-1; rows++) {
                spaceCounter++;
                counter = spaceCounter;
                while(counter != 0) {
                        putchar(' ');
                        counter--;
                }
                printSpacesLine(_charToPrint, rows);
                putchar('\n');
        }

        return OK;
}

int triangle5(char _charToPrint, int _size){
        int rows, cols, spaceCounter=_size;
        int counter;
        for (rows = _size; rows >= 0; rows--) {
                spaceCounter--;
                counter = spaceCounter;
                while(counter >= 0) {
                        putchar(' ');
                        counter--;
                }
                for (cols = rows; cols <= _size-1; cols++) {
                        putchar(_charToPrint);
                        putchar(' ');
                }
                putchar('\n');
        }
}

int triangle6(char _charToPrint, int _size){
        int rows, cols, spaceCounter=_size;
        int counter;
        for (rows = _size; rows > 0; rows--) {
                spaceCounter--;
                counter = spaceCounter;
                while(counter >= 0) {
                        putchar(' ');
                        counter--;
                }
                for (cols = rows; cols <= _size-1; cols++) {
                        putchar(_charToPrint);
                        putchar(' ');
                }
                putchar('\n');
        }

        spaceCounter=-1;
        for (rows = 0; rows <= _size-1; rows++) {
                spaceCounter++;
                counter = spaceCounter;
                while(counter != 0) {
                        putchar(' ');
                        counter--;
                }
                for (cols = rows; cols <= _size-1; cols++) {
                        putchar(_charToPrint);
                        putchar(' ');
                }
                putchar('\n');
        }
}
