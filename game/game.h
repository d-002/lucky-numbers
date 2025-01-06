typedef struct Tile {
    /*
    * value: from 1 to 20
    * isVisible: boolean value
    * isTaken: whether it is in someone's game
    */
    int value;
    int isVisible;
    int isTaken;
} Tile;

typedef struct Game {
    int numPlayers;
    int aiMask;

    Tile ****players;
    Tile *allTiles;
} Game;

Game *init_game(int, int);
void free_game(Game *);
void print_game(Game *);
