#include "includes/game.h"

int main()
{
        Game *game = NULL;
        game = CreateGame();

        if (game != NULL)
        {
                Rules();
                WelcomeMessage();
                StartGame(game);
                DestroyGame(game);
        }

        return 0;
}
