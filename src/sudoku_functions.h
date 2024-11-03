#ifndef SUDOKU_FUNCTIONS
#define SUDOKU_FUNCTIONS

#include "pos.h"
#include <stdbool.h>
#include <stdint.h>

// reads from file and stores into array
void read_file(uint16_t sudoku[9][9], char *path);
// checks if num is in row, column, box
bool in_row(uint16_t sudoku[9][9], const int row, const int num);
bool in_col(uint16_t sudoku[9][9], const int col, const int num);
bool in_box(uint16_t sudoku[9][9], const struct pos position, const int num);
bool is_safe(uint16_t sudoku[9][9], const struct pos position, const int num);
// finds cell and writes it into position variable
bool find_empty_cell(uint16_t sudoku[9][9], struct pos *position);
bool solve(uint16_t sudoku[9][9]);
void clear(uint16_t sudoku[9][9]);

void generate_sudoku(uint16_t sudoku[9][9], int removed_digits);
// generates numbers for boxes along one diagonal
void generate_diagonal_matrices(uint16_t sudoku[9][9]);
void shuffle_nums(int nums[9]);
void add_nums_to_box(uint16_t sudoku[9][9], int box_x, int box_y, int nums[9]);
bool remove_n_digits(uint16_t sudoku[9][9], int n);

void swap(int *x, int *y); // swaps 2 numbers
void print_sudoku(uint16_t sudoku[9][9]);
// copies original sudoku into copy
void copy_sudoku(uint16_t const original_sudoku[9][9], uint16_t copy[9][9]);
// same as solve function, but also writes the
// number of solutions into solutions variable
bool number_of_solutions(uint16_t sudoku[9][9], int *solutions);

#endif // SUDOKU_FUNCTIONS
