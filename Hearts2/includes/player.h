#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "vector.h"
#include "card.h"

#define NUM_OF_PLAYERS 4

typedef struct Player Player;

typedef ADTErr (*funcPointer)(Player *, int, int *, Suit, int);

/***************************************************************************************
   Description:  The function creates a new player.
   Input:        int _index
                 int _isReal
   output:       returns NULL if allocation not succeed
                 OTHERWISE RETURNS pointer to new game.
   Error:        X
***************************************************************************************/
Player *CreatePlayer(int _index, int _isReal);

/***************************************************************************************
   Description:  The function free the player memory.
   Input:        Game *_game
   output:       X
   Error:        X
***************************************************************************************/
void DestroyPlayer(Player *_player);

/***************************************************************************************
   Description:  The function checks if the player is real player.
   Input:        Player *_player
   output:       returns 0 if _player == null.
   Error:        X
***************************************************************************************/
int IsReal(Player *_player);

void SortHand(Player *_player);

ADTErr ThrowCard(Player *_player, funcPointer _func, int *_card, Suit _seriesNumber, int _isHeartsAllowed);

ADTErr TakeCard(Player *_player, int _card);

int FindCard(Player *_player, int _card, int *_index);

ADTErr PlayerGetCardAtIndex(Player *_player, int _index, int *_card);

void PlayerAddToScore(Player *_player, int _score);

void PrintPlayerHand(Player *_player);

void PrintScore(Player *_player);

void PrintHandInStart(Player *_player, char *playerName);

/** getters and setters**/
int GetScore(Player *_player);

void SetScore(Player *_player, int _score);

char *GetName(Player *_player);

#endif /* _PLAYER_H_ */
