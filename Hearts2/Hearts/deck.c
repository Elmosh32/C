/**********************************************************************************
                             includes & defines
**********************************************************************************/
#include <time.h>
#include <stdlib.h>

#include "../includes/deck.h"
#include "../includes/card.h"
#include "../includes/vector.h"

/**********************************************************************************
                   Declaration of static Auxiliary function
**********************************************************************************/
static ADTErr FillDeck(Vector *_deck, int _numOfPlayers);

/**********************************************************************************
                                api functions
**********************************************************************************/
Vector *CreateDeck(int _numOfPlayers)
{
        Vector *deck;

        if ((deck = VectorCreate((NUM_OF_CARDS * _numOfPlayers), _numOfPlayers)) == NULL)
        {
                return NULL;
        }

        FillDeck(deck, _numOfPlayers);

        return deck;
}

void DestroyDeck(Vector *_dec)
{
        if (_dec)
        {
                VectorDestroy(_dec);
        }
}

ADTErr Shuffle(Vector *_deck, int _numOfPlayers)
{
        int i, j, item1, item2;

        if (_deck == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        srand(time(NULL));
        for (i = 0; i < NUM_OF_CARDS * _numOfPlayers; i++)
        {
                j = rand() % NUM_OF_CARDS * _numOfPlayers;
                getVector(_deck, j, &item1);
                getVector(_deck, i, &item2);

                setVector(_deck, j, item2);
                setVector(_deck, i, item1);
        }

        return ERR_OK;
}

ADTErr DealCard(Vector *_deck, int *_temp)
{
        if (_deck == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        return VectorDelete(_deck, _temp);
}

/**********************************************************************************
                             Auxiliary function
**********************************************************************************/
static ADTErr FillDeck(Vector *_deck, int _numOfPlayers)
{
        ADTErr errorVal;
        int i;

        if (_deck == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        for (i = 0; i < NUM_OF_CARDS * _numOfPlayers; i++)
        {
                if ((errorVal = VectorAdd(_deck, i)) != ERR_OK)
                {
                        return errorVal;
                }
        }

        return ERR_OK;
}