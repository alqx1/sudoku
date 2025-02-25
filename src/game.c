#include "game.h"
#include "sudoku_scene.h"
#include <stdint.h>

enum Scene scene = s_sudoku;

// Zažene funkcijo za trenutno sceno
void run(struct config config, struct pos *selected, uint16_t sudoku[9][9]) {
    if (scene == s_sudoku) {
        run_sudoku(config, selected, sudoku);
    }
}
