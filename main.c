#include <stdio.h>
#include <err.h>

#include "game/game.h"
#include "ai/v1.h"

int main() {
    Game *game = init_game(6, 1);
    if (!game) err(1, "init_game");

    print_game(game);

    free_game(game);

    return 0;
}
