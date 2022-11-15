/**********************************************************************************
                             includes & defines
**********************************************************************************/
#include "../includes/round.h"
#include "../includes/player.h"
#include "../includes/deck.h"
#include "../includes/ui.h"
#include "../includes/card.h"
#include "../includes/vector.h"

#define CARDS_TO_PASS 3
#define DOWN -1
#define UP 1

/**********************************************************************************
                   Declaration of static Auxiliary functions
**********************************************************************************/
static void Trick(Player **_players, int *_whoLost, int *_canUseHearts, int _trickNumber);
static void PassCards(Player **_players, int toPass);
static void CalcScores(Player **_players, int series[], int *_whoLost, Suit _seriesSuit);
static int Search2Club(Player **_players);
static ADTErr ChooseFrom(Player *_player, int _handSize, int _from, int _to, int _jump, int *_cardIndex);
static ADTErr GetCardByRule(Player *_player, int _from, int _to, int *_cardIndex, Suit _seriesNumber);
static void GetMinScore(Player **_players, int *_minScore, int *index);
static void GetMaxScore(Player **_players, int *_maxScore);
static void PrintScores(Player **_players);

/**********************************************************************************
                                api functions
**********************************************************************************/
ADTErr CreateRound(Player **_players)
{
        int card, i, j;
        Vector *deck = CreateDeck(NUM_OF_PLAYERS);

        if (deck == NULL || _players == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        Shuffle(deck, NUM_OF_PLAYERS);

        for (i = 0; i < NUM_OF_PLAYERS; i++)
        {
                for (j = 0; j < NUM_OF_CARDS; j++)
                {
                        DealCard(deck, &card);
                        TakeCard(_players[i], card);
                }
        }

        DestroyDeck(deck);
        return ERR_OK;
}

ADTErr StartRound(Player **_players, int _roundNumber, int *_maxScore)
{
        int i, whoLost, canUseHeart = 0;
        int passes[] = {1, 3, 2, 0};
        int toPass = passes[_roundNumber];

        if (_players == NULL || _maxScore == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        PassCards(_players, toPass);
        whoLost = Search2Club(_players);

        for (i = 0; i < NUM_OF_CARDS; i++)
        {
                Trick(_players, &whoLost, &canUseHeart, i);
        }

        PrintScores(_players);
        GetMaxScore(_players, _maxScore);

        return ERR_OK;
}

ADTErr ChooseCard(Player *_player, int _handSize, int *_cardIndex, Suit _seriesNumber, int _isHeartsAllowed)
{
        int from, to, card;

        if (_player == NULL || _cardIndex == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        if (_handSize == 0)
        {
                return ERR_UNDERFLOW;
        }

        PrintPlayerHand(_player);

        if (_seriesNumber == ONLY_2CLUB)
        {
                do
                {
                        Choose2Club(_cardIndex);
                        PlayerGetCardAtIndex(_player, *_cardIndex, &card);
                } while (card != NUM_OF_CARDS * CLUB_VAL);
                return ERR_OK;
        }

        if (_seriesNumber == NONE)
        {
                if (_isHeartsAllowed == 0)
                {
                        if (GetCardByRule(_player, NUM_OF_CARDS, NUM_OF_CARDS * NUM_OF_SUITES, _cardIndex, _seriesNumber) == ERR_OK)
                        {
                                return ERR_OK;
                        }
                }
                GetCardByRule(_player, 0, NUM_OF_CARDS * NUM_OF_SUITES, _cardIndex, _seriesNumber);
                return ERR_OK;
        }

        from = _seriesNumber * NUM_OF_CARDS;
        to = from + NUM_OF_CARDS;

        if ((GetCardByRule(_player, from, to, _cardIndex, _seriesNumber)) == ERR_OK)
        {
                return ERR_OK;
        }

        GetCardByRule(_player, 0, NUM_OF_CARDS * NUM_OF_SUITES, _cardIndex, _seriesNumber);

        return ERR_OK;
}

ADTErr AutoChooseCard(Player *_player, int _handSize, int *_cardIndex, Suit _seriesNumber, int _isHeartsAllowed)
{
        int from, to;

        if (_player == NULL || _cardIndex == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        if (_handSize == 0)
        {
                return ERR_UNDERFLOW;
        }

        if (_seriesNumber == ONLY_2CLUB)
        {
                return ChooseFrom(_player, _handSize, NUM_OF_CARDS * CLUB_VAL, NUM_OF_CARDS * CLUB_VAL + 1, UP, _cardIndex);
        }

        if (_seriesNumber == NONE)
        {
                if (!_isHeartsAllowed)
                {
                        if (ChooseFrom(_player, _handSize, NUM_OF_CARDS, NUM_OF_CARDS * NUM_OF_SUITES, UP, _cardIndex) == ERR_OK)
                        {
                                return ERR_OK;
                        }
                }
                if (ChooseFrom(_player, _handSize, 0, NUM_OF_CARDS * NUM_OF_SUITES, UP, _cardIndex) != ERR_OK)
                {
                        return ERR_OK;
                }
        }

        from = _seriesNumber * NUM_OF_CARDS;
        to = from + NUM_OF_CARDS;

        if ((ChooseFrom(_player, _handSize, from, to, UP, _cardIndex)) != ERR_OK)
        {
                if (ChooseFrom(_player, _handSize, NUM_OF_CARDS - 1, -1, DOWN, _cardIndex) != ERR_OK)
                {
                        ChooseFrom(_player, _handSize, NUM_OF_CARDS * NUM_OF_SUITES - 1, -1, DOWN, _cardIndex);
                }
        }

        return ERR_OK;
}

void printAllHands(Player **_players)
{
        int i;

        if (_players)
        {
                for (i = 0; i < NUM_OF_PLAYERS; i++)
                {
                        if (_players[i] != NULL)
                        {
                                if (i == 0)
                                {
                                        PrintHandInStart(_players[i], "yours");
                                }
                                else
                                {
                                        PrintHandInStart(_players[i], NULL);
                                }
                        }
                }
        }
}

void PrintGameResults(Player **_players)
{
        int i, index, minScore, place = 1;

        if (_players)
        {
                for (i = 0; i < NUM_OF_PLAYERS; i++)
                {
                        minScore = 127;
                        GetMinScore(_players, &minScore, &index);
                        UIPrintScore(GetName(_players[index]), minScore, place);
                        place++;
                        SetScore(_players[index], 127);
                }
        }
}

/**********************************************************************************
                             Auxiliary functions
**********************************************************************************/
static void Trick(Player **_players, int *_whoLost, int *_canUseHearts, int _trickNumber)
{
        int i = 0, card, currentPlayer = *_whoLost;
        int series[] = {-1, -1, -1, -1};
        funcPointer func = NULL;
        Suit _seriesSuit = NONE;

        while (i < NUM_OF_PLAYERS)
        {
                if (_trickNumber == 0 && currentPlayer == *_whoLost)
                {
                        _seriesSuit = ONLY_2CLUB;
                }

                func = IsReal(_players[currentPlayer]) ? ChooseCard : AutoChooseCard;

                ThrowCard(_players[currentPlayer], func, &card, _seriesSuit, *_canUseHearts);
                series[currentPlayer] = card;

                if (card < NUM_OF_CARDS)
                {
                        *_canUseHearts = 1;
                }

                if (i == 0)
                {
                        _seriesSuit = CALC_SUIT(card);
                }

                PrintSeries(series, NUM_OF_PLAYERS);
                currentPlayer = (currentPlayer + 1) % NUM_OF_PLAYERS;
                i++;
        }

        CalcScores(_players, series, _whoLost, _seriesSuit);
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

static ADTErr GetCardByRule(Player *_player, int _from, int _to, int *_cardIndex, Suit _seriesNumber)
{
        int i, card, index;

        for (i = _from; i < _to; i++)
        {
                if (FindCard(_player, i, &index))
                {
                        do
                        {
                                UIChooseCard(_cardIndex, _seriesNumber);
                                PlayerGetCardAtIndex(_player, *_cardIndex, &card);
                        } while (card < _from || card >= _to);

                        return ERR_OK;
                }
        }

        return ERR_WRONG_INDEX;
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
        int i, j, tempCard, tempHeartsBroken = 1;
        int cardsToPass[NUM_OF_PLAYERS][CARDS_TO_PASS];
        funcPointer func = NULL;

        if (_toPass == 0)
        {
                return;
        }

        for (i = 0; i < NUM_OF_PLAYERS; i++)
        {
                func = IsReal(_players[i]) ? ChooseCard : AutoChooseCard;

                for (j = 0; j < CARDS_TO_PASS; j++)
                {
                        ThrowCard(_players[i], func, &tempCard, NONE, tempHeartsBroken);
                        cardsToPass[i][j] = tempCard;
                }
        }

        for (i = 0; i < NUM_OF_PLAYERS; i++)
        {
                for (j = 0; j < CARDS_TO_PASS; j++)
                {
                        tempCard = cardsToPass[i][j];
                        TakeCard(_players[(i + _toPass) % NUM_OF_PLAYERS], tempCard);
                }
        }
}

static void GetMaxScore(Player **_players, int *_maxScore)
{
        int i;

        for (i = 0; i < NUM_OF_PLAYERS; i++)
        {
                if (GetScore(_players[i]) > *_maxScore)
                {
                        *_maxScore = GetScore(_players[i]);
                }
        }
}

static void GetMinScore(Player **_players, int *_minScore, int *index)
{
        int i;

        for (i = 0; i < NUM_OF_PLAYERS; i++)
        {
                if (GetScore(_players[i]) < *_minScore)
                {
                        *_minScore = GetScore(_players[i]);
                        *index = i;
                }
        }
}

static void PrintScores(Player **_players)
{
        int i;

        if (_players)
        {
                for (i = 0; i < NUM_OF_PLAYERS; i++)
                {
                        PrintScore(_players[i]);
                }
        }
}