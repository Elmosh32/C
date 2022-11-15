#ifndef _CARD_H_
#define _CARD_H_

#define CALC_SUIT(i) (i / NUM_OF_CARDS)
#define CALC_CARD_NUM(i) (i % NUM_OF_CARDS)

typedef enum
{
        NONE = -1,
        HEART_VAL = 0,
        SPADE_VAL,
        DIAMOND_VAL,
        CLUB_VAL,
        NUM_OF_SUITES,
        ONLY_2CLUB
} Suit;

typedef enum
{
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        ACE,
        NUM_OF_CARDS
} NumCard;

#endif /* _CARD_H_ */
