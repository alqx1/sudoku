#include "../cell_functions.h"
#include "constraints.h"
#include <stddef.h>

void rule_constraints(uint16_t sudoku[9][9], uint16_t possible[9][9]) {
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (get_value(sudoku[i][j]) == 0) {
                continue;
            }

            row_constraint(sudoku, possible, (struct pos){.y = i, .x = j});
            column_constraint(sudoku, possible, (struct pos){.y = i, .x = j});
            box_constraint(sudoku, possible, (struct pos){.y = i, .x = j});
        }
    }
}

void row_constraint(
    uint16_t sudoku[9][9], uint16_t possible[9][9], struct pos selected
) {
    for (int x = 0; x < 9; x++) {
        if (get_changable(possible[selected.y][x])) {
            continue;
        }

        if (get_note(
                possible[selected.y][x],
                get_value(sudoku[selected.y][selected.x])
            )) {
            set_note(
                &possible[selected.y][x],
                get_value(sudoku[selected.y][selected.x]), false
            );
        }
    }
}

void column_constraint(
    uint16_t sudoku[9][9], uint16_t possible[9][9], struct pos selected
) {
    for (int y = 0; y < 9; y++) {
        if (get_changable(possible[y][selected.x])) {
            continue;
        }

        if (get_note(
                possible[y][selected.x],
                get_value(sudoku[selected.y][selected.x])
            )) {
            set_note(
                &possible[y][selected.x],
                get_value(sudoku[selected.y][selected.x]), false
            );
        }
    }
}

void box_constraint(
    uint16_t sudoku[9][9], uint16_t possible[9][9], struct pos selected
) {
    int box_x = selected.x - (selected.x % 3);
    int box_y = selected.y - (selected.y % 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (get_changable(possible[box_y + i][box_x + j])) {
                continue;
            }

            if (get_note(
                    possible[box_y + i][box_x + j],
                    get_value(sudoku[selected.y][selected.x])
                )) {
                set_note(
                    &possible[box_y + i][box_x + j],
                    get_value(sudoku[selected.y][selected.x]), false
                );
            }
        }
    }
}
