#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    game->numPlayers = numPlayers;
    game->aiMask = aiMask;

    return game;
}

void twoDigits(int value, char dest[2]) {
    dest[0] = value < 10 ? ' ' : '0' + value/10;
    dest[1] = '0' + value%10;
}

void addString(char *receiver, char *data, int *count) {
    int len = strlen(data);

    memcpy(receiver + *count, data, len);
    *count += len;
}

void print_game(Game *game) {
    char two[3]; // buffer for twoDigits
    two[2] = '\0'; // end of string

    const int lineLen = 73, nLines = 7;
    char lines[nLines][lineLen];
    int indices[nLines];

    for (int n = 0; n < game->numPlayers;) {
        // reset lines
        for (int j = 0; j < nLines; j++)
            memset(lines[j], 0, lineLen);
        memset(indices, 0, nLines * sizeof(int));

        for (int i = 0; i < 4; i++) {
            int isLast = n == game->numPlayers-1;
            char *sep = (i == 3 || isLast) ? "\n" : "#";

            // add data to the lines
            twoDigits(n+1, two);
            addString(lines[0], "    Player ", indices);
            addString(lines[0], two, indices);
            addString(lines[0], "    ", indices);
            addString(lines[0], sep, indices);
            addString(lines[1], "  -------------  ", indices+1);
            addString(lines[1], sep, indices+1);

            for (int y = 0; y < 4; y++) {
                char *line = lines[2+y];
                int *index = indices+2+y;

                addString(line, " | ", index);
                for (int x = 0; x < 4; x++) {
                    twoDigits(y*4+x+1, two);
                    addString(line, two, index);
                    addString(line, " ", index);
                }
                addString(line, "| ", index);
                addString(line, sep, index);
            }

            addString(lines[6], "  -------------  ", indices+6);
            addString(lines[6], sep, indices+6);

            n++;
            if (isLast) break;
        }

        for (int j = 0; j < nLines; j++) printf("%s", lines[j]);
        printf("\n");
    }
}

void free_game(Game *game) {
    free(game);
}
