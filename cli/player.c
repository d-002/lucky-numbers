#include "player.h"

#include <stdio.h>

typedef int (*check_func)(Game *, int);

int check_in_visible(Game *game, int value) {
    if (value < 1 || value > 20) return 0;

    for (int i = 0; i < game->numTiles; i++) {
        Tile *tile = game->allTiles+i;

        if (tile->value != value) continue;
        if (tile->isTaken) continue;
        if (!tile->isVisible) continue;

        return 1;
    }

    return 0;
}

int check_pos(Game *, int value) {
    return value >= 0 && value <= 3;
}

int check_bit(Game *, int value) {
    return value >= 0 && value <= 1;
}

int pick_number(char *msg, Game *game, check_func func) {
    int n;
    while (1) {
        printf("%s", msg);
        if (!scanf("%d", &n)) {
            printf("No input, setting value to 0\n");
            n = 0;
        }

        if (func(game, n)) return n;

        printf("Incorrect input.\n");
    }
}

void place(Game *game, Tile *tile, int pid) {
    int x = pick_number("Enter x pos (1->4): ", game, check_pos);
    int y = pick_number("Enter y pos (1->4): ", game, check_pos);

    place_tile_at(game, tile, pid, x, y);
}

void player_play(Game *game, int pid) {
    int available = 0; // if av&1, then hidden are available, same for av&2

    for (int i = 0; i < game->numTiles; i++) {
        Tile *tile = game->allTiles+i;

        if (tile->isTaken) continue;
        available |= 1 << tile->isVisible;
    }

    int choice;
    switch(available) {
        case 1:
            choice = 0;
            break;
        case 2:
            choice = 1;
            break;
        default: // 3
            choice = pick_number("Pick a visible tile? (0/1): ",
                                 game, check_bit);
    }

    if (choice) {
        // picked visible tile

        int value = pick_number("Choose a number: ", game, check_in_visible);
        Tile *tile = choose_visible(game, value);

        place(game, tile, pid);
    }

    else {
        // picked hidden tile
        Tile *tile = flip_random(game);
        printf("Your tile value is %d\n", tile->value);
        int use = pick_number("Use this card in your game? (0/1): ",
                              game, check_bit);

        if (use) place(game, tile, pid);
    }
}
