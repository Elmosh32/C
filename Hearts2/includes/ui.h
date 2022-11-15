#ifndef _UI_H_
#define _UI_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "vector.h"
#include "card.h"
#include "auxiliaryFunc.h"

/* colors */
#define NORMAL "\x1B[0m"
#define BLACK "\x1b[30m"
#define RED "\x1B[31m"

/* cards suites symbols */
#define SPADE "\xE2\x99\xA0"
#define CLUB "\xE2\x99\xA3"
#define HEART "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"
#define WINNER "\xF0\x9F\x8F\x86"
#define NO_1 "\xe2\x9d\xb6"
#define NO_2 "\xe2\x9d\xb7"
#define NO_3 "\xe2\x9d\xb8"
#define NO_4 "\xe2\x9d\xb9"

#define NO_CARD -1
#define SPACE_SIZE 5

/***************************************************************************************
   Description:  prints the game rules
   Input:        X
   output:       X
   Error:        X
***************************************************************************************/
void Rules();

/***************************************************************************************
   Description:  prints players cards
   Input:        Vector *_hand => player cards
   output:       x
   Error:        x
***************************************************************************************/
void PrintHand(Vector *_hand);

/***************************************************************************************
   Description:  prints all players cards
   Input:        Vector *_hand
                 char *_playerName
   output:       x
   Error:        x
***************************************************************************************/
void UIPrintAllHands(Vector *_hand, char *_playerName);

/***************************************************************************************
   Description:  checks if the player wants to play one more hand
   Input:        int *_exit => the user choice
   output:       x
   Error:        x
***************************************************************************************/
void WannaExit(int *_exit);

/***************************************************************************************
   Description:  prints player score
   Input:        char *_playerName
                 int _playerScore
                 int _playerPlace
   output:       x
   Error:        x
***************************************************************************************/
void UIPrintScore(char *_playerName, int _playerScore, int _playerPlace);

void PrintSeries(int _series[], int _size);

void Choose2Club(int *_cardIndex);

void UIChooseCard(int *_cardIndex, Suit _suitNumber);

#endif /* _UI_H_ */
