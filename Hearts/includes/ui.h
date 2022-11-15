#ifndef _UI_H_
#define _UI_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "card.h"
#include "auxiliaryFunc.h"
#include "vector.h"

#define NO_CARD -1
#define SPACE_SIZE 5

/* bold/not bold */
#define BOLD_ON "\x1b[1m"
#define BOLD_OFF "\x1b[21m"

/* colors */
#define NORMAL "\x1B[0m"
#define BLACK "\x1b[30m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define GRAY "\x1b[90m"

/* cards suites symbols */
#if defined(_WIN32) || defined(__MSDOS__)
#define HEART "\x03"
#define DIAMOND "\x04"
#define CLUB "\x05"
#define SPADE "\x06"
#else
#define SPADE "\xE2\x99\xA0"
#define CLUB "\xE2\x99\xA3"
#define HEART "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"
#define WINNER "\xF0\x9F\x8F\x86"
#define NO_1 "\xe2\x9d\xb6"
#define NO_2 "\xe2\x9d\xb7"
#define NO_3 "\xe2\x9d\xb8"
#define NO_4 "\xe2\x9d\xb9"
#endif
void WelcomeMessage();
void PrintCard(int _card);
void PrintHand(Vector *_hand);
void PrintScore(char *_name, int _score);
void PrintSeries(int _series[], int _size);
void UIChooseCard(int *_cardIndex, Suit _suitNumber);
void Choose2Club(int *_cardIndex);
void Rules();

#endif /* _UI_H_ */
