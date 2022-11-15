#ifndef __GAME_H__
#define __GAME_H__

#include <stdlib.h>
#include <stdio.h>

#include "player.h"
#include "round.h"
#include "ui.h"
#include "player.h"
#include "vector.h"

#define GAME_MAGIC_NUM 999
#define MAX_SCORE 100
#define NUM_OF_PLAYERS  4

typedef struct Game Game;

Game* CreateGame();
void DestroyGame(Game* _game);
ADTErr StartGame(Game* _game);

#endif /* __GAME_H__ */
