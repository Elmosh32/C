#include "includes/round.h"

static void Trick(Player **_players, int *_whoLost, int *_canUseHearts, int _trickNum);
static void PassCards(Player **_players, int toPass);
static void CalcScores(Player **_players, int series[], int *_whoLost, Suit _seriesSuit);
static ADTErr ChooseFrom(Player *_player, int _handSize, int _from, int _to, int _jump, int *_cardIndex);
static ADTErr GetCardByRule(Player *_player, int _from, int _to, int *_cardIndex, Suit _seriesNum);
static void GetMaxScore(Player **_players, int *_maxScore);
static int Search2Club(Player **_players);

ADTErr CreateRound(Player **_players)
{
        int card, i, j = 0;
        /**int item;
           size_t index=51;**/
        Vector *deck = DeckCreate();

        if (deck == NULL || _players == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        Shuffle(deck);

        for (i = 1; i <= NUM_OF_CARDS; i++)
        {
                DealCard(deck, &card);
                TakeCard(_players[j], card);
                if ((i % HAND_SIZE) == 0)
                {
                        j++;
                }
        }

        DeckDestroy(deck);
        return ERR_OK;
}

ADTErr StartRound(Player **_players, int *_maxScore, int _roundNum)
{
        int i, whoLost, canUseHeart = 0;
        int passes[] = {1, 3, 2, 0};
        int toPass = passes[_roundNum];

        if (_players == NULL || _maxScore == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        PassCards(_players, toPass);
        whoLost = Search2Club(_players);

        for (i = 0; i < HAND_SIZE; i++)
        {
                Trick(_players, &whoLost, &canUseHeart, i);
        }

        PlayerPrintScores(_players);
        GetMaxScore(_players, _maxScore);

        return ERR_OK;
}

static void Trick(Player **_players, int *_whoLost, int *_canUseHearts, int _trickNum)
{
        int i = 0, card;
        int currentPlayer = *_whoLost;
        int series[] = {-1, -1, -1, -1};
        Suit _seriesSuit = NONE;

        while (i < NUM_OF_PLAYERS)
        {
                if (_trickNum == 0 && currentPlayer == *_whoLost)
                {
                        _seriesSuit = ONLY_2CLUB;
                }

                ThrowCard(_players[currentPlayer], &card, _seriesSuit, *_canUseHearts);
                series[currentPlayer] = card;

                if (card < NUM_OF_CARDS)
                {
                        *_canUseHearts = 1;
                }

                if (i == 0)
                {
                        _seriesSuit = CALC_SUIT(card);
                }

                currentPlayer = (currentPlayer + 1) % NUM_OF_PLAYERS;

                i++;
        }

        PrintSeries(series, NUM_OF_PLAYERS);
        CalcScores(_players, series, _whoLost, _seriesSuit);
}

static void GetMaxScore(Player **_players, int *_maxScore)
{
        int i;

        for (i = 0; i < NUM_OF_PLAYERS; i++)
        {
                if (PlayerGetScore(_players[i]) > *_maxScore)
                {
                        *_maxScore = PlayerGetScore(_players[i]);
                }
        }
}

static void CalcScores(Player **_players, int series[], int *_whoLost, Suit _seriesSuit)
{
        int i, trickScore = 0, maxCard = 0;

        for (i = 0; i < NUM_OF_PLAYERS; i++)
        {
                if (series[i] == SPADE_VAL * NUM_OF_CARDS + QUEEN)
                {
                        trickScore += NUM_OF_CARDS;
                }
                else if (series[i] < NUM_OF_CARDS)
                {
                        trickScore++;
                }

                if (CALC_SUIT(series[i]) == _seriesSuit)
                {
                        if (series[i] > maxCard)
                        {
                                maxCard = series[i];
                                *_whoLost = i;
                        }
                }
        }

        PlayerAddToScore(_players[*_whoLost], trickScore);
}

static int Search2Club(Player **_players)
{
        int i = -1, index;

        for (i = 0; i < NUM_OF_PLAYERS; i++)
        {
                if (FindCard(_players[i], NUM_OF_CARDS * CLUB_VAL, &index))
                {
                        return i;
                }
        }

        return i;
}

static void PassCards(Player **_players, int _toPass)
{
        int i, k, tempCard, tempHeartsBroken = 1;
        int cardsToPass[NUM_OF_PLAYERS][CARDS_TO_PASS];

        if (_toPass == 0)
        {
                return;
        }

        for (i = 0; i < NUM_OF_PLAYERS; i++)
        {
                for (k = 0; k < CARDS_TO_PASS; k++)
                {
                        ThrowCard(_players[i], &tempCard, NONE, tempHeartsBroken);
                        cardsToPass[i][k] = tempCard;
                }
        }

        for (i = 0; i < NUM_OF_PLAYERS; i++)
        {
                for (k = 0; k < CARDS_TO_PASS; k++)
                {
                        tempCard = cardsToPass[i][k];
                        TakeCard(_players[(i + _toPass) % NUM_OF_PLAYERS], tempCard);
                }
        }
}

ADTErr ChooseCard(Player *_player, int _handSize, int *_cardIndex, Suit _seriesNum, int _isHeartsAllowed)
{
        ADTErr errorVal;
        int from, to, card;

        if (_player == NULL || _cardIndex == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        if (_handSize == 0)
        {
                return ERR_UNDERFLOW;
        }

        PlayerPrintHand(_player);
        if (_seriesNum == ONLY_2CLUB)
        {
                do
                {
                        Choose2Club(_cardIndex);
                        PlayerGetCardAtIndex(_player, *_cardIndex, &card);
                } while (card != NUM_OF_CARDS * CLUB_VAL);
                return ERR_OK;
        }

        if (_seriesNum == NONE)
        {
                if (_isHeartsAllowed == 0)
                {
                        if (GetCardByRule(_player, NUM_OF_CARDS, NUM_OF_CARDS * NUM_OF_PLAYERS, _cardIndex, _seriesNum) == ERR_OK)
                        {
                                return ERR_OK;
                        }
                }

                GetCardByRule(_player, 0, NUM_OF_CARDS * NUM_OF_PLAYERS, _cardIndex, _seriesNum);
                return ERR_OK;
        }

        from = _seriesNum * NUM_OF_CARDS;
        to = from + NUM_OF_CARDS;
        errorVal = GetCardByRule(_player, from, to, _cardIndex, _seriesNum);

        if (errorVal == ERR_OK)
        {
                return ERR_OK;
        }

        GetCardByRule(_player, 0, NUM_OF_CARDS * NUM_OF_PLAYERS, _cardIndex, _seriesNum);

        return ERR_OK;
}

static ADTErr GetCardByRule(Player *_player, int _from, int _to, int *_cardIndex, Suit _seriesNum)
{
        int i, card, index;

        for (i = _from; i < _to; i++)
        {
                if (FindCard(_player, i, &index))
                {
                        do
                        {
                                UIChooseCard(_cardIndex, _seriesNum);
                                PlayerGetCardAtIndex(_player, *_cardIndex, &card);
                        } while (card < _from || card >= _to);

                        return ERR_OK;
                }
        }

        return ERR_WRONG_INDEX;
}

ADTErr AutoChooseCard(Player *_player, int _handSize, int *_cardIndex, Suit _seriesNum, int _isHeartsAllowed)
{
        ADTErr errorVal;
        int from, to;

        if (_player == NULL || _cardIndex == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        if (_handSize == 0)
        {
                return ERR_UNDERFLOW;
        }

        if (_seriesNum == ONLY_2CLUB)
        {
                return ChooseFrom(_player, _handSize, NUM_OF_CARDS * CLUB_VAL, NUM_OF_CARDS * CLUB_VAL + 1, UP, _cardIndex);
        }

        if (_seriesNum == NONE)
        {
                if (!_isHeartsAllowed)
                {
                        if (ChooseFrom(_player, _handSize, NUM_OF_CARDS, NUM_OF_CARDS * NUM_OF_PLAYERS, UP, _cardIndex) == ERR_OK)
                        {
                                return ERR_OK;
                        }
                }

                if (ChooseFrom(_player, _handSize, 0, NUM_OF_CARDS * NUM_OF_PLAYERS, UP, _cardIndex) != ERR_OK)
                {
                        return ERR_OK;
                }
        }

        from = _seriesNum * NUM_OF_CARDS;
        to = from + NUM_OF_CARDS;

        errorVal = ChooseFrom(_player, _handSize, from, to, UP, _cardIndex);
        if (errorVal != ERR_OK)
        {
                if (ChooseFrom(_player, _handSize, NUM_OF_CARDS - 1, -1, DOWN, _cardIndex) != ERR_OK)
                {
                        ChooseFrom(_player, _handSize, NUM_OF_CARDS * NUM_OF_PLAYERS - 1, -1, DOWN, _cardIndex);
                }
        }

        return ERR_OK;
}

static ADTErr ChooseFrom(Player *_player, int _handSize, int _from, int _to, int _jump, int *_cardIndex)
{
        int i, index;

        for (i = _from; i != _to; i += _jump)
        {
                if (FindCard(_player, i, &index))
                {
                        *_cardIndex = index;
                        return ERR_OK;
                }
        }

        return ERR_WRONG_INDEX;
}