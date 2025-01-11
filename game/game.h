#ifndef GAME_H
#define GAME_H

typedef struct Tile {
    /*
    * value: from 1 to 20
    * isVisible: boolean value
    * isTaken: whether it is in someone's game
    */
    int value;
    int isVisible;
    int isTaken;
} Tile;

typedef struct Game {
    int numPlayers;
    int aiMask;

    Tile ****players;
    Tile *allTiles;
    int numTiles;
} Game;

#include "../cli/player.h"
#include "../ai/v1.h"

// general Game utils
Game *init_game(int, int);
void free_game(Game *);

// in-game utils
int get_start_pid();
Tile *flip_random(Game *);
Tile *choose_visible(Game *, int);
void place_tile_at(Game *, Tile *, int, int, int);
int play(Game *, int);

#endif /* GAME_H */
