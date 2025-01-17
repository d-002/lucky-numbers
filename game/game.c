#include "game.h"

#include <stdlib.h>

Game *make_game(int numPlayers, int aiMask) {
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
    game->numTiles = numPlayers * 20;
    game->allTiles = malloc(game->numTiles * sizeof(Tile));
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

void init_game(Game *game) {
    for (int pid = 1; pid <= game->numPlayers; pid++) {
        // choose 4 tiles
        Tile *tiles[4];
        for (int i = 0; i < 4; i++)
            tiles[i] = flip_random(game);

        // sort tiles and add them to the game
        for (int i = 0; i < 4; i++) {
            int min = 20;
            int minj = 0;

            for (int j = 0; j < 4; j++) {
                Tile *tile = tiles[j];
                if (!tile) continue; // already added to the game
                if (tile->value >= min) continue;

                min = tile->value;
                minj = j;
            }

            place_tile_at(game, tiles[minj], pid, i, i);
            tiles[minj] = NULL;
        }
    }
}

int get_start_pid() {
    return 1;
}

Tile *flip_random(Game *game) {
    // choose a random common tile, among those that are not flipped

    // first pass: check the number of hidden tiles
    int count = 0;
    int first_index = -1;
    for (int i = 0; i < game->numTiles; i++) {
        Tile *tile = game->allTiles+i;
        if (tile->isTaken) continue;

        if (first_index == -1) first_index = i;
        if (!tile->isVisible) count++;
    }

    // second pass: pick a random tile among them
    int rand_index = 0;
    int i = first_index;

    while (1) {
        Tile *tile = game->allTiles + i++;
        if (tile->isTaken) continue;

        if (!tile->isVisible)
            if (!rand_index--) {
                tile->isVisible = 1;
                return tile;
            }
    }
}

Tile *choose_visible(Game *game, int value) {
    // choose a common tile by value, among those that are flipped

    for (int i = 0; i < game->numTiles; i++) {
        Tile *tile = game->allTiles+i;
        if (tile->isTaken) continue;
        if (!tile->isVisible) continue;

        if (tile->value == value) return tile;
    }

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
    Tile ***player = game->players[pid-1];

    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
            if (!player[y][x]) return 0;

    return 1;
}

int play(Game *game, int pid) {
    if (game->aiMask & (1 << (pid-1)))
        ai_play(game, pid);
    else
        player_play(game, pid);

    if (has_won(game, pid)) return -1;

    return pid % game->numPlayers + 1;
}
