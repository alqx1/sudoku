#include "../cell_functions.h"
#include "constraints.h"
#include <stddef.h>

bool check_naked_singles(uint16_t sudoku[9][9], uint16_t possible[9][9]) {
    bool changed = false;
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (get_changable(possible[i][j])) {
                continue;
            }

            int possibilities = 0;
            for (int num = 1; num < 10; num++) {
                if (get_note(possible[i][j], num)) {
                   possibilities++;
                }
            }

            if (possibilities == 1) {
                naked_single(sudoku, possible, (struct pos){.y = i, .x = j});
                changed = true;
            }
        }
    }

    return changed;
}

void naked_single(
    uint16_t sudoku[9][9], uint16_t possible[9][9], struct pos selected
) {
    int possiblity = -1;
    for (int num = 1; num < 10; num++) {
        if (get_note(possible[selected.y][selected.x], num)) {
            possiblity = num;
            break;
        }
    }

    set_value(&sudoku[selected.y][selected.x], possiblity);
    set_changable(&possible[selected.y][selected.x], true);
}
