#include "includes/player.h"

struct Player
{
        Vector *m_hand;
        char m_name[NAME_LENGTH];
        int m_score;
        int m_magic;
};

Player *CreatePlayer(int _index)
{
        char name[NAME_LENGTH];
        char s[] = "player ";
        Player *player;

        if ((player = (Player *)malloc(sizeof(Player))) == NULL)
        {
                return NULL;
        }

        player->m_hand = VectorCreate(HAND_SIZE, BLOCK_SIZE);

        if (player->m_hand == NULL)
        {
                free(player);
                return NULL;
        }

        player->m_magic = PLAYER_MAGIC_NUM;

        MyItoa(_index + 1, name);
        strcpy(player->m_name, s);
        strcat(player->m_name, name);
        return player;
}

void PlayerDestroy(Player *_player)
{
        if (_player && _player->m_magic == PLAYER_MAGIC_NUM)
        {
                if (_player->m_hand)
                {
                        VectorDestroy(_player->m_hand);
                }
                _player->m_magic = 0;
                free(_player);
        }
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
        ADTErr err;
        if (_player == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }
        err = VectorAdd(_player->m_hand, _card);
        SortHand(_player);

        return err;
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

int PlayerGetScore(Player *_player)
{
        if (_player)
        {
                return _player->m_score;
        }
        return -1;
}

void PlayerAddToScore(Player *_player, int _score)
{
        if (_player)
        {
                _player->m_score += _score;
        }
}

ADTErr ThrowCard(Player *_player, int *_card, Suit _seriesNumber, int _isHeartsAllowed)
{
        ADTErr err;
        int temp1, temp2;
        size_t handSize;
        int cardIndex;
        if (_player == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }

        getNumOfItems(_player->m_hand, &handSize);
        err = AutoChooseCard(_player, handSize, &cardIndex, _seriesNumber, _isHeartsAllowed);
        if (err != ERR_OK)
        {
                return err;
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

void PlayerPrintHand(Player *_player)
{
        PrintHand(_player->m_hand);
}

void PlayerPrintScores(Player **_players)
{
        int i;
        if (_players)
        {
                for (i = 0; i < BLOCK_SIZE; i++)
                {
                        if (_players[i] != NULL)
                        {
                                PrintScore(_players[i]->m_name, _players[i]->m_score);
                        }
                }
        }
        puts("\n");
}

ADTErr PlayerGetCardAtIndex(Player *_player, int _index, int *_card)
{
        if (_player == NULL || _card == NULL)
        {
                return ERR_NOT_INITIALIZED;
        }
        return getVector(_player->m_hand, _index, _card);
}