#include "game.h"

#include <stdlib.h>

Game *init_game(int numPlayers, int aiMask) {
    /*
    * allocate and init a new game object
    *
    * :param:
    * numplayers (int): number of players (0 to 99)
    * aiMask (int): mask to indicate which players are AI-controlled
    *   example:
    *     numplayers = 4
    *     aiMask = 0b1010
        -> players 1 and 3 are AI-controlled, players 2 and 4 are not
    *
    * :return:
    * Game *game. Must free using free_game
    */

    if (numPlayers < 0 || numPlayers > 99) return NULL;

    Game *game = malloc(sizeof(struct Game));

    // init basic info
    game->numPlayers = numPlayers;
    game->aiMask = aiMask;

    // init players
    game->players = malloc(numPlayers * sizeof(Tile ***));

    for (int n = 0; n < numPlayers; n++) {
        Tile ***player = malloc(4 * sizeof(Tile **));
        game->players[n] = player;

        for (int y = 0; y < 4; y++)
            player[y] = calloc(4, sizeof(Tile *));
    }

    // init tiles bank
    game->allTiles = malloc(numPlayers * 20 * sizeof(Tile));
    for (int i = 0, n = 0; n < numPlayers; n++)
        for (int value = 1; value <= 20; value++, i++) {
            Tile *tile = game->allTiles+i;
            tile->value = value;
            tile->isVisible = 0;
            tile->isTaken = 0;
        }

    return game;
}

void free_game(Game *game) {
    // free tiles
    free(game->allTiles);

    // free players
    for (int n = 0; n < game->numPlayers; n++) {
        Tile ***player = game->players[n];

        for (int y = 0; y < 4; y++) free(player[y]);
        free(player);
    }
    free(game->players);

    free(game);
}

int get_start_pid() {
    return 1;
}

Tile *flip_random(Game *game) {
    // choose a random common tile, among those that are not flipped

    return NULL;
}

Tile *choose_flipped(Game *game, int value) {
    // choose a common tile by value, among those that are flipped

    return NULL;
}

void place_tile_at(Game *game, Tile *tile, int pid, int x, int y) {
    Tile **p = game->players[pid-1][y]+x;

    Tile *replaced = *p;
    *p = tile;

    tile->isTaken = 1;

    if (!replaced) return;
    replaced->isTaken = 0;
}

int has_won(Game *game, int pid) {
    return 0;
}

int play(Game *game, int pid) {
    if (game->aiMask & (1 << (pid-1)))
        player_play(game);
    else
        ai_play(game);

    if (has_won(game, pid)) return -1;

    return pid % game->numPlayers + 1;
}
