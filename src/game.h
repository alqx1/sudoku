#ifndef GAME
#define GAME

#include "pos.h"
#include <stdint.h>

enum Scene { s_sudoku, s_menu };

void run(short window_size, struct pos *selected, uint16_t sudoku[9][9]);

#endif // GAME
