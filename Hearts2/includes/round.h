#ifndef _ROUND_H_
#define _ROUND_H_

#include "player.h"

/***************************************************************************************
   Description:  The function creates a new game round.
                 creates a new deck, shuffles the cards and deals it to the players.
                 destroys deck at the end
   Input:        Player **_players => vector of all players
   output:       ADTErr
   Error:        ERR_NOT_INITIALIZED if deck or players array is NULL
***************************************************************************************/
ADTErr CreateRound(Player **_players);

/***************************************************************************************
   Description:  The function starts a new round.
                 creates a new deck, shuffles the cards, and deals the cards to the players.
                 destroys deck at the end.
   Input:        Player **_players => vector of all players
                 int _roundNumber
                 int *_maxScore
   output:       ADTErr
   Error:        ERR_NOT_INITIALIZED if max score or players array is NULL
                 ERR_OK if succeed
***************************************************************************************/
ADTErr StartRound(Player **_players, int _roundNumber, int *_maxScore);

/***************************************************************************************
   Description:  A valid card is obtained from the player by the function
   Input:        Player *_player
                 int _handSize
                 int *_cardIndex
                 Suit _seriesNumber
                 int _isHeartsAllowed
   output:       ADTErr
   Error:        ERR_NOT_INITIALIZED if _player == NULL  or _cardIndex == NULL
                 ERR_UNDERFLOW if _handSize == 0
                 ERR_OK if succeed
***************************************************************************************/
ADTErr ChooseCard(Player *_player, int _handSize, int *_cardIndex, Suit _seriesNumber, int _isHeartsAllowed);

/***************************************************************************************
   Description:   The function chooses a valid card for the automatic player by the strategy.
                  When passing cards at the beginning: first pass the hearts if you have them, then pass the others if you do not.
                  To choose a card to throw, follow these steps:
                  if there is no leading series =>
                     When heart cards are not allowed, choose the minimum card that is not a heart.
                     When hearts allowed / you only have hearts:
                     Whenever you do not have a heart card, choose a minimum card from another series
                     otherwise, choose the minimum heart card
                  else =>
                     choose the minimum card from the given series.
                     When series is set but you do not have a suitable card:
                     Whenever you do not have a heart card, choose a maximum card from another series
                     otherwise, choose the maximum heart card
   Input:        Player *_player
                 int _handSize
                 int *_cardIndex
                 Suit _seriesNumber
                 int _isHeartsAllowed
   output:       ADTErr
   Error:        ERR_NOT_INITIALIZED if _player == NULL  or _cardIndex == NULL
                 ERR_UNDERFLOW if _handSize == 0
                 ERR_OK if succeed
***************************************************************************************/
ADTErr AutoChooseCard(Player *_player, int _handSize, int *_cardIndex, Suit _seriesNumber, int _isHeartsAllowed);

/***************************************************************************************
   Description:  The function prints the players places and their scores after the game ends.
   Input:        Player **_players
   output:       X
   Error:        X
***************************************************************************************/
void PrintGameResults(Player **_players);

/***************************************************************************************
   Description:  The function prints all players cards.
   Input:        Player **_players
   output:       X
   Error:        X
***************************************************************************************/
void printAllHands(Player **_players);

#endif /* _ROUND_H_ */
