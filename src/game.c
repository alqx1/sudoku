#include "game.h"
#include "sudoku_scene.h"
#include <stdint.h>

enum Scene scene = s_sudoku;

void run(short window_size, struct pos *selected, uint16_t sudoku[9][9]) {
    if (scene == s_sudoku) {
        run_sudoku(window_size, selected, sudoku);
    }
}
