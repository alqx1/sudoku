#include "constraints.h"
#include "../cell_functions.h"
#include <stddef.h>
#include <stdio.h>

void init_possibilities(uint16_t possible[9][9], uint16_t sudoku[9][9]) {
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            init_possibility(&possible[i][j]);
            if (get_value(sudoku[i][j]) != 0) {
                set_changable(&possible[i][j], true);
            }
        }
    }
}

void printall(uint16_t possible[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%b ", possible[i][j]);
        }
        printf("\n");
    }
}

void constrain(uint16_t sudoku[9][9]) {
    uint16_t possible[9][9];
    init_possibilities(possible, sudoku);

    printall(possible);
    printf("\n");
    bool has_changed;
    do {
        has_changed = false;

        rule_constraints(sudoku, possible);
        has_changed =
            check_naked_singles(sudoku, possible) ? true : has_changed;

        has_changed = unique_in_units(sudoku, possible) ? true : has_changed;
    } while (has_changed);
    printall(possible);
}

void init_possibility(uint16_t *n) {
    *n = ~0;
    *n <<= 6;
    *n >>= 6;
    *n &= ~1;
}
