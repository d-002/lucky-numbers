#include <stdio.h>
#include <err.h>

#include "game/game.h"
#include "cli/print.h"

int main() {
    Game *game = init_game(2, 0);
    if (!game) err(1, "init_game");

    int pid = get_start_pid();
    while (1) {
        printf("Player %d's turn\n\n", pid);

        int prev = pid;
        pid = play(game, pid);

        print_game(game);

        // winner
        if (pid == -1) {
            printf("\n>>> Player %d won!\n\n", prev);
            break;
        }
    }

    free_game(game);
    return 0;
}
