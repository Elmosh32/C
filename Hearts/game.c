#include "includes/game.h"

struct Game
{
        Player **m_players;
        int m_magic;
};

static ADTErr CreatePlayers(Game *_game);
static void printAllHands(Game *_game);

Game *CreateGame()
{
        Game *game;

        if ((game = (Game *)malloc(sizeof(Game))) == NULL)
        {
                return NULL;
        }

        game->m_players = (Player **)malloc(NUM_OF_PLAYERS * sizeof(Player *));

        if (game->m_players == NULL)
        {
                free(game);
                return NULL;
        }

        game->m_magic = GAME_MAGIC_NUM;

        if (CreatePlayers(game) != ERR_OK)
        {
                return NULL;
        }

        return game;
}

void DestroyGame(Game *_game)
{
        int i;

        if (_game && _game->m_magic == GAME_MAGIC_NUM)
        {
                if (_game->m_players != NULL)
                {
                        for (i = 0; i < NUM_OF_PLAYERS; i++)
                        {
                                PlayerDestroy(_game->m_players[i]);
                        }
                        free(_game->m_players);
                }
                _game->m_magic = 0;
                free(_game);
        }
}

ADTErr StartGame(Game *_game)
{
        int roundNumber = 0, maxScore = 0;
        while (maxScore < MAX_SCORE)
        {
                if (CreateRound(_game->m_players) != ERR_OK)
                {
                        return ERR_GENERAL;
                }

                printAllHands(_game);

                StartRound(_game->m_players, &maxScore, roundNumber);
                roundNumber = (roundNumber + 1) % NUM_OF_PLAYERS;
        }

        return ERR_OK;
}

static ADTErr CreatePlayers(Game *_game)
{
        int i, j;

        for (i = 0; i < NUM_OF_PLAYERS; i++)
        {
                _game->m_players[i] = CreatePlayer(i);
                if (_game->m_players[i] == NULL)
                {
                        for (j = 0; j < i; j++)
                        {
                                PlayerDestroy(_game->m_players[j]);
                        }

                        free(_game->m_players);
                        free(_game);
                        return ERR_ALLOCATION_FAILED;
                }
        }

        return ERR_OK;
}

static void printAllHands(Game *_game)
{
        int i;

        for (i = 0; i < NUM_OF_PLAYERS; i++)
        {
                PlayerPrintHand(_game->m_players[i]);
        }
}