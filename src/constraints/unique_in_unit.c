#include "../cell_functions.h"
#include "../pos.h"
#include "../sudoku_functions/sudoku_functions.h"
#include "constraints.h"

bool unique_in_units(uint16_t sudoku[9][9], uint16_t possible[9][9]) {
    bool changed = false;
    unique_in_columns(sudoku, possible, &changed);
    unique_in_rows(sudoku, possible, &changed);
    unique_in_boxes(sudoku, possible, &changed);

    return changed;
}

void unique_in_rows(
    uint16_t sudoku[9][9], uint16_t possible[9][9], bool *changed
) {
    struct pos last;

    for (int row = 0; row < 9; row++) {
        for (int num = 1; num < 10; num++) {
            int num_occurance = 0;
            for (int x = 0; x < 9; x++) {
                if (get_changable(possible[row][x])) {
                    continue;
                }

                if (get_note(possible[row][x], num)) {
                    last = (struct pos){.y = row, .x = x};
                    num_occurance++;
                }
            }

            if (num_occurance == 1 && is_safe(sudoku, last, num)) {
                set_value(&sudoku[last.y][last.x], num);
                set_changable(&possible[last.y][last.x], true);
                *changed = true;
            }
        }
    }
}

void unique_in_columns(
    uint16_t sudoku[9][9], uint16_t possible[9][9], bool *changed
) {
    struct pos last;

    for (int column = 0; column < 9; column++) {
        for (int num = 1; num < 10; num++) {
            int num_occurance = 0;
            for (int y = 0; y < 9; y++) {
                if (get_changable(possible[y][column])) {
                    continue;
                }

                if (get_note(possible[y][column], num)) {
                    last = (struct pos){.y = y, .x = column};
                    num_occurance++;
                }
            }

            if (num_occurance == 1 && is_safe(sudoku, last, num)) {
                set_value(&sudoku[last.y][last.x], num);
                set_changable(&possible[last.y][last.x], true);
                *changed = true;
            }
        }
    }
}

void unique_in_box(
    uint16_t sudoku[9][9], uint16_t possible[9][9], int box_x, int box_y,
    bool *changed
) {
    struct pos last;

    for (int num = 1; num < 10; num++) {
        int num_occurance = 0;
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (get_changable(possible[y + box_y][x + box_x])) {
                    continue;
                }

                if (get_note(possible[y + box_y][x + box_x], num)) {
                    last = (struct pos){.y = y + box_y, .x = x + box_x};
                    num_occurance++;
                }
            }
        }

        if (num_occurance == 1 && is_safe(sudoku, last, num)) {
            set_value(&sudoku[last.y][last.x], num);
            set_changable(&possible[last.y][last.x], true);
            *changed = true;
        }
    }
}

void unique_in_boxes(
    uint16_t sudoku[9][9], uint16_t possible[9][9], bool *changed
) {
    for (int box_y = 0; box_y < 9; box_y += 3) {
        for (int box_x = 0; box_x < 9; box_x += 3) {
            unique_in_box(sudoku, possible, box_x, box_y, changed);
        }
    }
}
