#include "player.h"

#include <stdio.h>

typedef int (*check_func)(Game *, int);

int in_hidden(Game *game, int n) {
    if (n < 1 || n > 20) return 0;

    return 1;
}

int pick_number(char *msg, Game *game, check_func func) {

    int n;
    while (1) {
        printf("%s", msg);
        scanf("%d", &n);

        if (func(game, n)) return n;

        printf("Incorrect input.\n");
    }
}

void player_play(Game *game) {
    pick_number("Choose a number: ", game, in_hidden);
}
