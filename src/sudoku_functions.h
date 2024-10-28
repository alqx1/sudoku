#ifndef SUDOKU_FUNCTIONS
#define SUDOKU_FUNCTIONS

#include "structs.h"
#include <stdbool.h>

struct cell *read_file(char *path);
bool in_row(struct cell *sudoku, const int row, const int num);
bool in_col(struct cell *sudoku, const int col, const int num);
bool in_box(struct cell *sudoku, const int x, const int y, const int num);
bool is_safe(struct cell *sudoku, const int x, const int y, const int num);
bool find_empty_cell(struct cell *sudoku, int *list);
bool solve(struct cell *sudoku);
void clear(struct cell *sudoku);

struct cell *generate_sudoku(int removed_digits);
struct cell *generate_diagonal_matrices();
void shuffle_nums(int *nums);
void add_nums_to_box(struct cell *sudoku, int box_x, int box_y, int *nums);
void remove_n_digits(struct cell *sudoku, int n);

void print_sudoku(struct cell *sudoku);
void swap(int *x, int *y);

#endif // SUDOKU_FUNCTIONS
