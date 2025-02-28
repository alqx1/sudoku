#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include "../pos.h"
#include <stdint.h>

void init_possibilities(uint16_t possible[9][9], uint16_t sudoku[9][9]);

void init_possibility(uint16_t *n);

void constrain(uint16_t sudoku[9][9]);

bool check_naked_singles(uint16_t sudoku[9][9], uint16_t possible[9][9]);
void naked_single(
    uint16_t sudoku[9][9], uint16_t possible[9][9], struct pos selected
);
void rule_constraints(uint16_t sudoku[9][9], uint16_t possible[9][9]);
void rule_constraint(
    uint16_t sudoku[9][9], uint16_t possible[9][9], struct pos selected
);
void row_constraint(
    uint16_t sudoku[9][9], uint16_t possible[9][9], struct pos selected
);
void column_constraint(
    uint16_t sudoku[9][9], uint16_t possible[9][9], struct pos selected
);
void box_constraint(
    uint16_t sudoku[9][9], uint16_t possible[9][9], struct pos selected
);

bool check_hidden_singles(uint16_t sudoku[9][9], uint16_t possible[9][9]);
void unique_in_rows(
    uint16_t sudoku[9][9], uint16_t possible[9][9], bool *changed
);
void unique_in_columns(
    uint16_t sudoku[9][9], uint16_t possible[9][9], bool *changed
);
void unique_in_boxes(
    uint16_t sudoku[9][9], uint16_t possible[9][9], bool *changed
);

#endif // CONSTRAINTS_H
