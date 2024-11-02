#ifndef SUDOKU_FUNCTIONS
#define SUDOKU_FUNCTIONS

#include "structs.h"
#include <stdbool.h>
#include <stdint.h>

void read_file(uint16_t sudoku[9][9], char *path);
bool in_row(uint16_t sudoku[9][9], const int row, const int num);
bool in_col(uint16_t sudoku[9][9], const int col, const int num);
bool in_box(uint16_t sudoku[9][9], const struct pos position, const int num);
bool is_safe(uint16_t sudoku[9][9], const struct pos position, const int num);
bool find_empty_cell(uint16_t sudoku[9][9], struct pos *position);
bool solve(uint16_t sudoku[9][9]);
void clear(uint16_t sudoku[9][9]);

void generate_sudoku(uint16_t sudoku[9][9], int removed_digits);
void generate_diagonal_matrices(uint16_t sudoku[9][9]);
void shuffle_nums(int nums[9]);
void add_nums_to_box(uint16_t sudoku[9][9], int box_x, int box_y, int nums[9]);
bool remove_n_digits(uint16_t sudoku[9][9], int n);

void swap(int *x, int *y);
void print_sudoku(uint16_t sudoku[9][9]);
void copy_sudoku(uint16_t const original_sudoku[9][9], uint16_t copy[9][9]);
bool number_of_solutions(uint16_t sudoku[9][9], int *solutions);

#endif // SUDOKU_FUNCTIONS
