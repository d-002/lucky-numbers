#include "print.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void twoDigits(int value, char dest[2]) {
    if (!value) {
        dest[0] = dest[1] = '.';
        return;
    }

    dest[0] = value < 10 ? ' ' : '0' + value/10;
    dest[1] = '0' + value%10;
}

void addString(char *receiver, char *data, int *count) {
    int len = strlen(data);

    memcpy(receiver + *count, data, len);
    *count += len;
}

void print_tile_array(Tile **arr, int length) {
    char two[3];
    two[2] = '\0';

    int x = 0;
    int newline = 0;

    for (int i = 0; i < length; i++) {
        newline = ++x >= 20;
        if (newline) x = 0;
        char sep = newline ? '\n' : ' ';

        Tile *tile = arr[i];
        twoDigits(tile->isVisible ? tile->value : 0, two);

        printf("%s%c", two, sep);
    }

    // add a newline, but not if already just added one as a separator
    if (!newline) printf("\n");
}

void print_game(Game *game) {
    char two[3]; // buffer for twoDigits
    two[2] = '\0'; // end of string

    const int lineLen = 73, nLines = 7;
    char lines[nLines][lineLen];
    int indices[nLines];

    // players
    for (int n = 0; n < game->numPlayers;) {
        // reset lines
        for (int j = 0; j < nLines; j++)
            memset(lines[j], 0, lineLen);
        memset(indices, 0, nLines * sizeof(int));

        for (int i = 0; i < 4; i++) {
            int isLast = n == game->numPlayers-1;
            char *sep = (i == 3 || isLast) ? "\n" : "#";

            Tile ***player = game->players[n];

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
                    Tile *tile = player[y][x];

                    twoDigits(tile ? tile->value : 0, two);
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

    // common tiles
    printf("Common tiles:\n");
    Tile **hidden = malloc(game->numTiles * sizeof(Tile *));
    Tile **visible = malloc(game->numTiles * sizeof(Tile *));
    int count_h = 0, count_v = 0;

    for (int i = 0; i < game->numTiles; i++) {
        Tile *tile = game->allTiles+i;

        if (tile->isTaken) continue;

        if (tile->isVisible) visible[count_v++] = tile;
        else hidden[count_h++] = tile;
    }

    print_tile_array(hidden, count_h);
    print_tile_array(visible, count_v);
    free(hidden);
    free(visible);
}
