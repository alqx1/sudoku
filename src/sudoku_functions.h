#ifndef SUDOKU_FUNCTIONS
#define SUDOKU_FUNCTIONS

#include <stdbool.h>

int *read_file(char *path);
bool in_row(int *sudoku, const int row, const int num);
bool in_col(int *sudoku, const int col, const int num);
bool in_box(int *sudoku, const int x, const int y, const int num);
bool is_safe(int *sudoku, const int x, const int y, const int num);
bool find_empty_cell(int *sudoku, int *list);
bool solve(int *sudoku);

int *generate_sudoku(int removed_digits);
int *generate_diagonal_matrices();
void shuffle_nums(int *nums);
void add_nums_to_box(int *sudoku, int box_x, int box_y, int *nums);
void remove_n_digits(int *sudoku, int n);

void print_sudoku(int *sudoku);
void swap(int *x, int *y);

#endif // SUDOKU_FUNCTIONS
