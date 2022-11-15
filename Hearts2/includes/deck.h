#ifndef _DECK_H_
#define _DECK_H_

#include "vector.h"

/***************************************************************************************
   Description:  The function creates a new deck of cards and set up its values fills uo the deck and shuffles it
   Input:        int _numOfPlayers
   output:       returns NULL if allocation does not succeed
                 otherwise returns a pointer to the new deck
   Error:        X
***************************************************************************************/
Vector *CreateDeck(int _numOfPlayers);

/***************************************************************************************
   Description:  The function free the deck structure memory.
   Input:        int _numOfPlayers
   output:       X
   Error:        X
***************************************************************************************/
void DestroyDeck(Vector *_deck);

/***************************************************************************************
   Description:  The function shuffles the deck.
   Input:        Vector *_deck
                 int _numOfPlayers
   output:       ADTErr
   Error:        ERR_NOT_INITIALIZED if deck == NULL
                 ERR_OK if succeed
***************************************************************************************/
ADTErr Shuffle(Vector *_deck, int _numOfPlayers);

/***************************************************************************************
   Description:  The function removes a card from the deck and puts its value to a variable.
   Input:        Vector *_deck
                 int *_temp
   output:       ADTErr
   Error:        ERR_NOT_INITIALIZED if deck == NULL
                 ERR_OK if succeed
***************************************************************************************/
ADTErr DealCard(Vector *_deck, int *_temp);

#endif /* _DECK_H_ */
