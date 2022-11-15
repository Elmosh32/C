#ifndef __ROUND_H__
#define __ROUND_H__

#include <stdio.h>

#include "player.h"
#include "card.h"
#include "deck.h"
#include "ui.h"
#include "vector.h"
#include "ADTDefs.h"

#define NUM_OF_CARDS 52
#define NUM_OF_PLAYERS 4
#define HAND_SIZE 13
#define CARDS_TO_PASS 3
#define DOWN -1
#define UP 1

typedef struct Round Round;

ADTErr CreateRound(Player **_players);
ADTErr StartRound(Player **_players, int *_maxScore, int _roundNum);
ADTErr ChooseCard(Player *_player, int _handSize, int *_cardIndex, Suit _seriesNum, int _isHeartsAllowed);
ADTErr AutoChooseCard(Player *_player, int _handSize, int *_cardIndex, Suit _seriesNum, int _isHeartsAllowed);

#endif /* __ROUND_H__ */
