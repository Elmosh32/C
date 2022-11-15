#include "includes/deck.h"

static ADTErr FillDeck(Vector *_deck);

Vector *DeckCreate()
{
        Vector *deck = VectorCreate(NUM_OF_CARDS, NUM_OF_PLAYERS);

        if (deck == NULL)
        {
                return NULL;
        }

        FillDeck(deck);

        return deck;
}

void DeckDestroy(Vector *_deck)
{
        if (_deck != NULL)
        {
                VectorDestroy(_deck);
        }
}

ADTErr Shuffle(Vector *_deck)
{
        int i, j, item1, item2;
        if (_deck == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        srand(time(NULL));
        for (i = 0; i < NUM_OF_CARDS; i++)
        {
                j = rand() % NUM_OF_CARDS;
                getVector(_deck, j, &item1);
                getVector(_deck, i, &item2);

                setVector(_deck, j, item2);
                setVector(_deck, i, item1);
        }

        return ERR_OK;
}

ADTErr DealCard(Vector *_deck, int *_item)
{
        if (_deck == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        return VectorDelete(_deck, _item);
}

static ADTErr FillDeck(Vector *_deck)
{
        ADTErr errorVal;
        int i;

        if (_deck == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }
        for (i = 0; i < NUM_OF_CARDS; i++)
        {
                errorVal = VectorAdd(_deck, i);
                if (errorVal != ERR_OK)
                {
                        return errorVal;
                }
        }

        return ERR_OK;
}