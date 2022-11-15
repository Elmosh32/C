/**********************************************************************************
                             includes & defines
**********************************************************************************/
#include <stdlib.h>

#include "../includes/game.h"
#include "../includes/round.h"
#include "../includes/player.h"
#include "../includes/ui.h"
#include "../includes/vector.h"

#define GAME_MAGIC_NUM 91912
#define MAX_SCORE 100

/**********************************************************************************
                                game struct
**********************************************************************************/
struct Game
{
        Player **m_players;
        int m_maxScore;
        int m_magicNum;
};

/**********************************************************************************
                   Declaration of static Auxiliary function
**********************************************************************************/
static ADTErr CreatePlayers(Game *_game);

/**********************************************************************************
                                api functions
**********************************************************************************/
Game *CreateGame()
{
        Game *game;

        if ((game = (Game *)malloc(sizeof(Game))) == NULL)
        {
                return NULL;
        }

        if ((game->m_players = (Player **)malloc(NUM_OF_PLAYERS * sizeof(Player *))) == NULL)
        {
                free(game);
                return NULL;
        }

        game->m_maxScore = MAX_SCORE;
        game->m_magicNum = GAME_MAGIC_NUM;

        if (CreatePlayers(game) != ERR_OK)
        {
                return NULL;
        }

        return game;
}

void DestroyGame(Game *_game)
{
        int i;

        if (_game != NULL && _game->m_magicNum == GAME_MAGIC_NUM)
        {
                if (_game->m_players != NULL)
                {
                        for (i = 0; i < NUM_OF_PLAYERS; i++)
                        {
                                DestroyPlayer(_game->m_players[i]);
                        }

                        free(_game->m_players);
                }

                _game->m_magicNum = 0;
                free(_game);
        }
}

void StartGame(Game *_game)
{
        int roundNumber = 0, maxScore = 0, exit = 0;

        Rules();
        while (maxScore < _game->m_maxScore && exit != 1)
        {
                if (CreateRound(_game->m_players) != ERR_OK)
                {
                        return;
                }

                printAllHands(_game->m_players);

                StartRound(_game->m_players, roundNumber, &maxScore);
                roundNumber = (roundNumber + 1) % NUM_OF_PLAYERS;

                if (maxScore >= _game->m_maxScore)
                {

                        PrintGameResults(_game->m_players);
                        return;
                }
                else
                {
                        WannaExit(&exit);
                }
        }
}

/**********************************************************************************
                             Auxiliary function
**********************************************************************************/
static ADTErr CreatePlayers(Game *_game)
{
        int i, j;
        int isReal = 1;

        for (i = 0; i < NUM_OF_PLAYERS; i++)
        {
                _game->m_players[i] = CreatePlayer(i, isReal);
                isReal = 0;

                if (_game->m_players[i] == NULL)
                {
                        for (j = 0; j < i; j++)
                        {
                                DestroyPlayer(_game->m_players[j]);
                        }

                        free(_game->m_players);
                        free(_game);
                        return ERR_ALLOCATION_FAILED;
                }
        }

        return ERR_OK;
}