#ifndef _GAME_H_
#define _GAME_H_

typedef struct Game Game;

/***************************************************************************************
   Description:  The function creates a new game, a new array of players.
   Input:        X
   output:       returns NULL if allocation not succeed
                 OTHERWISE RETURNS pointer to new game.
   Error:        X
***************************************************************************************/
Game *CreateGame();

/***************************************************************************************
   Description:  The function free the game and players memory.
   Input:        Game *_game
   output:       X
   Error:        X
***************************************************************************************/
void DestroyGame(Game *_game);

/***************************************************************************************
   Description:  The function starts a new game.
   Input:        Game *_game
   output:       X
   Error:        X
***************************************************************************************/
void StartGame(Game *_game);

#endif /* _GAME_H_ */
