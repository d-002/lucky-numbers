#include <stdio.h>
#include <err.h>

#include "game/game.h"
#include "game/print.h"
#include "ai/v1.h"

int main() {
    Game *game = init_game(2, 1);
    if (!game) err(1, "init_game");

    print_game(game);

    int pid = get_start_pid();
    while (1) {
        int prev = pid;
        pid = play(game, pid);

        // winner
        if (pid == -1) {
            printf("\n>>> Player %d won!\n\n", prev);
            break;
        }
    }

    free_game(game);
    return 0;
}
