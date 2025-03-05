#ifndef GAME
#define GAME

#include "config.h"
#include "pos.h"
#include <stdint.h>

typedef struct game {
    struct config config;
    struct pos cursor;
    uint16_t sudoku[9][9];
} game_t;

/*
 * Inicializira vse, kar je potrebno
 */
void init(game_t *game, int argc, char **argv);

/*
 * Izvede delovanje programa
 * (premikanje kazalca, vstavljanje vrednosti...)
 */
void run(game_t *game);

/*
 * Po končanem delovanju ugasne in pospravi vse kar je potrebno
 */
void clean(game_t *game);

#endif // GAME
