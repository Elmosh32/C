#ifndef __DECK_H__
#define __DECK_H__

#include <time.h>

#include "round.h"
#include "card.h"
#include "vector.h"

#define NUM_OF_CARDS 52
#define NUM_OF_PLAYERS  4

Vector* DeckCreate();
void DeckDestroy(Vector* _deck);
ADTErr Shuffle(Vector* _deck);
ADTErr DealCard(Vector* _deck, int* _item);

#endif /* __DECK_H__ */
