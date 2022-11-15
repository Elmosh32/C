#include <stdio.h>
#include <stdlib.h>

#include "../includes/game.h"

int main()
{
        Game *game = NULL;
        game = CreateGame();

        if (game != NULL)
        {
                StartGame(game);
                DestroyGame(game);
        }
        return 0;
}
