/**********************************************************************************
                             includes & defines
**********************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../includes/player.h"
#include "../includes/round.h"
#include "../includes/card.h"
#include "../includes/ui.h"
#include "../includes/vector.h"

#define PLAYER_MAGIC_NUM 1204
#define NAME_LENGTH 12

/**********************************************************************************
                                player struct
**********************************************************************************/
struct Player
{
        Vector *m_hand;
        char m_name[NAME_LENGTH];
        int m_score;
        int m_isReal;
        int m_magicNum;
};

/**********************************************************************************
                                api functions
**********************************************************************************/
Player *CreatePlayer(int _index, int _isReal)
{

        Player *newPlayer;

        if ((newPlayer = (Player *)calloc(1, sizeof(Player))) == NULL)
        {
                return NULL;
        }

        if ((newPlayer->m_hand = VectorCreate(NUM_OF_CARDS, NUM_OF_PLAYERS)) == NULL)
        {
                free(newPlayer);
                return NULL;
        }

        newPlayer->m_magicNum = PLAYER_MAGIC_NUM;
        switch (_index)
        {
        case 0:
                strcpy(newPlayer->m_name, "You");
                break;
        case 1:
                strcpy(newPlayer->m_name, "Mike");
                break;
        case 2:
                strcpy(newPlayer->m_name, "Bill");
                break;
        case 3:
                strcpy(newPlayer->m_name, "Lisa");
                break;
        }

        newPlayer->m_isReal = _isReal;

        return newPlayer;
}

void DestroyPlayer(Player *_player)
{
        if (_player && _player->m_magicNum == PLAYER_MAGIC_NUM)
        {
                if (_player->m_hand)
                {
                        VectorDestroy(_player->m_hand);
                }

                _player->m_magicNum = 0;
                free(_player);
        }
}

int IsReal(Player *_player)
{
        if (_player == NULL)
        {
                return 0;
        }

        return _player->m_isReal;
}

int FindCard(Player *_player, int _card, int *_index)
{
        int i, temp;
        size_t size;
        *_index = -1;

        if (_player != NULL && _player->m_hand != NULL)
        {
                getNumOfItems(_player->m_hand, &size);
                for (i = 0; i < size; i++)
                {
                        getVector(_player->m_hand, i, &temp);
                        if (temp == _card)
                        {
                                *_index = i;
                                return 1;
                        }
                }
        }

        return 0;
}

ADTErr TakeCard(Player *_player, int _card)
{
        ADTErr errorVal;

        if (_player == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        errorVal = VectorAdd(_player->m_hand, _card);
        SortHand(_player);

        return errorVal;
}

void SortHand(Player *_player)
{
        size_t handSize;

        if (_player == NULL)
        {
                return;
        }

        getNumOfItems(_player->m_hand, &handSize);

        if (handSize > 1)
        {
                QuickRec(_player->m_hand, 0, handSize - 1);
        }
}

int GetScore(Player *_player)
{
        if (_player)
        {
                return _player->m_score;
        }

        return -1;
}

void SetScore(Player *_player, int _score)
{
        if (_player)
        {
                _player->m_score = _score;
        }
}

char *GetName(Player *_player)
{
        if (_player)
        {
                return _player->m_name;
        }

        return NULL;
}

void PlayerAddToScore(Player *_player, int _score)
{
        if (_player)
        {
                _player->m_score += _score;
        }
}

ADTErr ThrowCard(Player *_player, funcPointer _func, int *_card, Suit _seriesNumber, int _isHeartsAllowed)
{
        ADTErr errorVal;
        int temp1, temp2, cardIndex;
        size_t handSize;

        if (_player == NULL || _func == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        getNumOfItems(_player->m_hand, &handSize);
        errorVal = (_func)(_player, handSize, &cardIndex, _seriesNumber, _isHeartsAllowed);
        if (errorVal != ERR_OK)
        {
                return errorVal;
        }

        getVector(_player->m_hand, cardIndex, _card);
        if (handSize > 1)
        {
                getVector(_player->m_hand, handSize - 1, &temp2);
                setVector(_player->m_hand, cardIndex, temp2);
        }

        VectorDelete(_player->m_hand, &temp1);
        SortHand(_player);

        return ERR_OK;
}

void PrintPlayerHand(Player *_player)
{
        PrintHand(_player->m_hand);
}

void PrintHandInStart(Player *_player, char *playerName)
{
        if (playerName != NULL)
        {
                UIPrintAllHands(_player->m_hand, playerName);
        }
        else
        {
                UIPrintAllHands(_player->m_hand, _player->m_name);
        }
}

void PrintScore(Player *_player)
{
        if (_player != NULL)
        {
                UIPrintScore(_player->m_name, _player->m_score, 0);
        }
}

ADTErr PlayerGetCardAtIndex(Player *_player, int _index, int *_card)
{
        if (_player == NULL || _card == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        return getVector(_player->m_hand, _index, _card);
}
