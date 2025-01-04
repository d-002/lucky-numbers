#include "game.h"

#include <stdio.h>
#include <stdlib.h>

Game *init_game(int numPlayers, int aiMask) {
    /*
    * allocate and init a new game object
    *
    * :param:
    * numplayers (int): number of players
    * aiMask (int): mask to indicate which players are AI-controlled
    *   example:
    *     numplayers = 4
    *     aiMask = 0b1010
        -> players 1 and 3 are AI-controlled, players 2 and 4 are not
    *
    * :return:
    * Game *game. Must free using free_game
    */

    Game *game = malloc(sizeof(struct Game));

    return game;
}

void print_game(Game *game) {
}

void free_game(Game *game) {
    free(game);
}
