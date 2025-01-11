#include "player.h"

#include <stdio.h>

typedef int (*check_func)(Game *, int);

int get_card_with_condition(Game *game, int value, int isVisible) {
    // intern function, used for check functions
    if (value < 1 || value > 20) return 0;

    for (int i = 0; i < game->numTiles; i++) {
        Tile *tile = game->allTiles+i;

        if (tile->value != value) continue;
        if (tile->isTaken) continue;
        if (tile->isVisible == isVisible) return 1;
    }

    return 0;
}

int check_in_hidden(Game *game, int value) {
    return get_card_with_condition(game, value, 0);
}

int check_in_visible(Game *game, int value) {
    return get_card_with_condition(game, value, 1);
}

int check_correct_pos(Game *, int value) {
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

void player_play(Game *game) {
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
            choice = pick_number("Pick a visible tile? (0/1): ", game, check_bit);
    }

    check_func func = choice ? check_in_visible : check_in_hidden;
    int chosen = pick_number("Choose a number: ", game, func);
}
