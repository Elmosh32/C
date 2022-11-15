#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "card.h"
#include "ui.h"
#include "vector.h"
#include "ADTDefs.h"

#define PLAYER_MAGIC_NUM 999
#define NAME_LENGTH 12
#define HAND_SIZE 13
#define BLOCK_SIZE 4

typedef struct Player Player;

typedef ADTErr (*funcPointer)(Player *, int, int *, Suit, int);

Player *CreatePlayer(int _index);
void PlayerDestroy(Player *_player);

ADTErr TakeCard(Player *_player, int _card);
ADTErr ThrowCard(Player *_player, int *_card, Suit _seriesNumber, int _isHeartsAllowed);
ADTErr PlayerGetCardAtIndex(Player *_player, int _index, int *_card);

int FindCard(Player *_player, int _card, int *_index);
int PlayerGetScore(Player *_player);

void PlayerAddToScore(Player *_player, int _score);
void PlayerPrintHand(Player *_player);
void PlayerPrintScores(Player **_playerArr);
void SortHand(Player *_player);

#endif /* __PLAYER_H__ */