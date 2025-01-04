#include <stdio.h>

#include "game/game.h"
#include "ai/v1.h"

int main() {
    Game *game = init_game(2, 1);
    print_game(game);

    free_game(game);

    return 0;
}
